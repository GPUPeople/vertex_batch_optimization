
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS 1

#include <cassert>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include <boost/heap/fibonacci_heap.hpp>
#include <boost/circular_buffer.hpp>

#include "VertexReuseStats.h"

#include "GBatchOptimizer.h"
#include "BatchSimulator.h"

namespace
{
	template<class T>
	using PriorityQueue = boost::heap::fibonacci_heap<T>;

	struct ScoreFactors
	{
		
		int32_t ValenceMultiplier = -2;
		int32_t CacheMultiplier = (1u << 16);
		int32_t DistanceMultiplier = 1;
		int32_t NeighborMultiplier = -1;
		int32_t FinPointMultiplier = 2;

		ScoreFactors() = default;

		ScoreFactors(uint32_t ValenceMultiplier, int32_t CacheMultiplier, int32_t DistanceMultiplier, int32_t NeighborMultiplier, int32_t FinPointMultiplier) :
			ValenceMultiplier(ValenceMultiplier), CacheMultiplier(CacheMultiplier),DistanceMultiplier(DistanceMultiplier), NeighborMultiplier(NeighborMultiplier), FinPointMultiplier(FinPointMultiplier)
		{
		}
	};

	struct TrianglePriority
	{
		uint32_t first_vertex;
		int32_t score;

		TrianglePriority(uint32_t first_vertex, int32_t score) :
			first_vertex(first_vertex), score(score)
		{
		}
		bool operator < (const TrianglePriority& other) const
		{
			return score < other.score;
		}

		static int32_t computeScore(const ScoreFactors& scores, uint32_t valence_sum, uint32_t cachedVertices = 0)
		{
			return cachedVertices*scores.CacheMultiplier + scores.ValenceMultiplier*valence_sum;
		}

		bool setScore(const ScoreFactors& scores, uint32_t valence_sum, uint32_t cachedVertices = 0)
		{
			int32_t prev_score = score;
			score = computeScore(scores, valence_sum, cachedVertices);
			return score > prev_score;
		}
		
		
	};

	template<class Queue>
	class TrianglePriorityUpdate
	{
		typename Queue::handle_type handle;
		TrianglePriority newentry;
		int32_t old_score;
		Queue& q;
		const ScoreFactors& scores;
	public:
		TrianglePriorityUpdate(Queue& q, const ScoreFactors& scores, typename Queue::handle_type handle) : handle(handle), newentry(*handle), old_score(newentry.score), q(q), scores(scores)
		{

		}
		void update()
		{
			if (newentry.score < old_score)
			{
				q.decrease(handle, newentry);
			}
			else if (newentry.score > old_score)
			{
				q.increase(handle, newentry);
			}
			old_score = newentry.score;
		}
		void addValence(uint32_t valence_sum = 1)
		{
			newentry.score += scores.ValenceMultiplier*valence_sum;
		}

		void reduceValence(uint32_t valence_sum = 1)
		{
			newentry.score -= scores.ValenceMultiplier*valence_sum;
		}

		void addCache(uint32_t cachedVertices = 1)
		{
			newentry.score += cachedVertices*scores.CacheMultiplier;
		}

		void reduceCache(uint32_t cachedVertices = 1)
		{
			newentry.score -= cachedVertices*scores.CacheMultiplier;
		}
		void addNeighbor(uint32_t numNeighborVertices = 1)
		{
			newentry.score += numNeighborVertices*scores.NeighborMultiplier;
		}
		void addFinpoint(uint32_t numNeighborVertices = 1)
		{
			newentry.score += numNeighborVertices*scores.FinPointMultiplier;
		}
		void addDistance(uint32_t distances)
		{
			newentry.score += distances*scores.DistanceMultiplier;
		}
		void reduceDistance(uint32_t distances)
		{
			newentry.score -= distances*scores.DistanceMultiplier;
		}

		~TrianglePriorityUpdate()
		{
			update();
		}
	};
	


	struct VertexData
	{
		uint32_t valence;
		uint32_t activeFaceListStart;
		uint32_t activeFaceListEnd;
		VertexData(uint32_t activeFaceListStart = 0, uint32_t activeFaceListEnd = 0, uint32_t valence = 0) :
			valence(valence), activeFaceListStart(activeFaceListStart), activeFaceListEnd(activeFaceListEnd) { }
	};

	template<class QIterator>
	struct FaceEntry
	{
		uint32_t face_start;
		QIterator qentry;
	};

	struct DistanceInformation
	{
		std::unordered_map<uint32_t, uint32_t> distances_from;
		std::vector<uint32_t> direct_neighbors;
		uint32_t accumulated_distances;
	};



	void OptimizeFaces(VertexReuseSimType Type,
		std::uint32_t* out_indices, std::uint32_t num_vertices, const std::uint32_t* in_indices, const std::uint32_t num_indices,
		const std::int32_t cacheWeight, const std::int32_t valenceWeight, const std::int32_t distanceWeight, const std::int32_t batchNeighborWeight, const std::int32_t finPointMultiplier)
	{
		ScoreFactors weights(valenceWeight, cacheWeight, distanceWeight, batchNeighborWeight, finPointMultiplier);
		//assert(maxIndices / 3 * 3 == maxIndices);

		using Queue = PriorityQueue<TrianglePriority>;
		using PriorityUpdate = TrianglePriorityUpdate<Queue>;

		Queue priorityQueue;
		// to go from vertices to neighboring faces (offsets in activeFaceList)
		std::vector<VertexData> vertexData(num_vertices);
		// pointer to the queue entry for every face referencable by vertices
		std::vector<FaceEntry<Queue::handle_type>> activeFaceList;
		//pointer to the queue entry for every individual face
		std::vector<Queue::handle_type> face_lookup(num_indices/3);


		// compute valence/face count per vertex
		for (uint32_t i = 0; i < num_indices; ++i)
		{
			assert(in_indices[i] < num_vertices);
			++vertexData[in_indices[i]].valence;
		}

		//reserve face list anc compute offsets in face list
		uint32_t faceListOffset = 0;
		for (auto& v : vertexData)
		{
			v.activeFaceListStart = faceListOffset;
			v.activeFaceListEnd = faceListOffset;
			faceListOffset += v.valence;
		}
		activeFaceList.resize(faceListOffset);


		//compute triangle score and create initial priority heap
		for (uint32_t i = 0; i < num_indices; i += 3)
		{
			uint32_t vsum = 0;
			for(uint32_t j = 0; j < 3; ++j)
				vsum += vertexData[in_indices[i + j]].valence;

			auto handle = priorityQueue.push({ i , TrianglePriority::computeScore(weights, vsum) });
			face_lookup[i / 3] = handle;

			for (uint32_t j = 0; j < 3; ++j)
			{
				VertexData& v = vertexData[in_indices[i + j]];
				activeFaceList[v.activeFaceListEnd++] = { i, handle };
			}
		}


		//run the greedy optimization
		uint32_t writtenIndices = 0;
		uint32_t batchIndices = 0;

		std::unordered_map<uint32_t, uint32_t> activeBatchEntries;
		std::unordered_map<uint32_t, DistanceInformation> activeDistances;
		std::unordered_set<uint32_t> cachedIds;
		//std::unordered_set<uint32_t> currentSubgroupIds;

		//boost::circular_buffer<uint32_t> fifo(fifoSize+3);

		auto batchSim = createBatchSim(Type);

		while (!priorityQueue.empty())
		{
			//TrianglePriority best = priorityQueue.top();
			//see if we can add the vertices to the batch still

			auto it = priorityQueue.ordered_begin();
			int score = it->score + 64;
			uint32_t best_start = it->first_vertex;
			uint32_t best_rot = 0;
			int32_t best_state = 10;
			//priorityQueue.erase();
			uint32_t t = 0;
			while (it != priorityQueue.ordered_end() && it->score <= score &&  ++t < 2)
			{
				uint32_t first_vertex = it->first_vertex;
				uint32_t triIds[] = { in_indices[first_vertex],
					in_indices[first_vertex + 1],
					in_indices[first_vertex + 2],
					in_indices[first_vertex] ,
					in_indices[first_vertex + 1] };
				
				uint32_t rotation = 0;
				int32_t addState = batchSim->canAddTriangle(triIds, 0);
				if (addState != -3)
				{
					rotation = 1;
					int32_t addState1 = batchSim->canAddTriangle(triIds, 1);
					int32_t addState2 = batchSim->canAddTriangle(triIds, 2);
					if (addState2 < addState1)
					{
						addState1 = addState2;
						rotation = 2;
					}
					if (addState1 < addState)
						addState = addState1;
					else
						rotation = 0;
				}

				if (addState < best_state)
				{
					best_start = it->first_vertex;
					best_state = addState;
					best_rot = rotation;
				}
				if (addState == -3)
					break;
				++it;
			}
	
			uint32_t first_vertex = best_start;
			uint32_t triIds[] = { in_indices[first_vertex],
				in_indices[first_vertex + 1],
				in_indices[first_vertex + 2],
				in_indices[first_vertex] ,
				in_indices[first_vertex + 1] };

			bool endofbatch = best_state > 1;
			
			

			if (!endofbatch)
			{
				batchSim->addTriangle(triIds, best_rot);

				bool incache[3];
				for (uint32_t i = 0; i < 3; ++i)
				{
					incache[i] = cachedIds.find(in_indices[best_start + i]) != end(cachedIds);
					if(!incache[i])
						cachedIds.insert(in_indices[best_start + i]);
				}

				//dont want to update data that has been removed
				activeBatchEntries.erase(best_start);
				//priorityQueue.pop();
				auto handle = face_lookup[best_start / 3];
				priorityQueue.erase(handle);
				face_lookup[best_start /3].node_ = nullptr;

				// distance updates
				uint32_t myDistance = 0;
				auto myDistEntry = activeDistances.find(best_start);
				if (myDistEntry != std::end(activeDistances))
					myDistance = myDistEntry->second.accumulated_distances;

				//TODO: consider reodering of the three vertices for better cache hits!

				//add vertices to cache scores and update valences
				for (uint32_t t = 0; t < 3; ++t)
				{
					//write the id out
					uint32_t vid = in_indices[best_start + t];
					out_indices[writtenIndices] = triIds[best_rot+t];
					++writtenIndices;

					VertexData& v = vertexData[vid];
					v.valence -= 1;
					// update all adjacent triangles
					for (uint32_t j = v.activeFaceListStart; j < v.activeFaceListEnd; ++j)
					{
						uint32_t face_vertex = activeFaceList[j].face_start;
						// already done
						if (face_vertex == 0xFFFFFFFF)
							continue;
						// remove current from others neighbor list
						if (face_vertex == best_start)
						{
							activeFaceList[j].face_start = 0xFFFFFFFF;
							continue;
						}
						PriorityUpdate updated(priorityQueue, weights, activeFaceList[j].qentry);
						updated.reduceValence();
						// vertex added to cache
						if (!incache[t])
						{
							updated.addCache();
							auto fentry = activeBatchEntries.find(face_vertex);
							if(fentry != end(activeBatchEntries))
							{
								++fentry->second;
							}
							else
							{
								activeBatchEntries[face_vertex] = 1;
							}
						}

						// update distance
						if (weights.DistanceMultiplier != 0)
						{
							auto existingDistEntry = activeDistances.find(face_vertex);
							if(existingDistEntry != std::end(activeDistances))
							{
								// update distances for already existing distance entry - only if we did not already do that for this face
								if(existingDistEntry->second.distances_from.find(best_start) == std::end(existingDistEntry->second.distances_from))
								{
									existingDistEntry->second.direct_neighbors.emplace_back(best_start);
									existingDistEntry->second.distances_from.emplace(std::make_pair(best_start, 1));
									existingDistEntry->second.accumulated_distances += 1;
									updated.addDistance(1);
								}
							}
							else
							{
								// add distance for newly found
								DistanceInformation newDistinfo;
								if (myDistEntry != std::end(activeDistances))
								{
									newDistinfo.accumulated_distances = myDistance + batchIndices / 3;
									newDistinfo.distances_from = myDistEntry->second.distances_from;
									for (auto& d : newDistinfo.distances_from)
										++d.second;
								}
								else
								{
									newDistinfo.accumulated_distances = 1;
								}
								newDistinfo.direct_neighbors.emplace_back(best_start);
								newDistinfo.distances_from.emplace(std::make_pair(best_start, 1));
								activeDistances.insert(std::make_pair(face_vertex, newDistinfo));
								updated.addDistance(newDistinfo.accumulated_distances);
							}
						}
					}
				}

				if (myDistEntry != std::end(activeDistances))
				{
					// update all non updated distances
					for (auto& d : activeDistances)
					{
						// dont update ourself or if we already updated it as direct neighbor
						if (d.first != best_start && d.second.distances_from.find(best_start) == std::end(d.second.distances_from))
						{
							uint32_t mindist = 0xFFFFFFFF;
							for (auto & dn : myDistEntry->second.direct_neighbors)
							{
								auto f = d.second.distances_from.find(dn);
								if (f != std::end(d.second.distances_from))
								{
									uint32_t ndist = f->second + 1;
									if (ndist < mindist)
										mindist = ndist;
								}
							}
							if (mindist != 0xFFFFFFFF)
							{
								PriorityUpdate updated(priorityQueue, weights, face_lookup[d.first/3]);
								updated.addDistance(mindist);
								d.second.distances_from.emplace(std::make_pair(best_start, mindist));
								d.second.accumulated_distances += mindist;
							}
						}
					}

					// remove my dist entry
					activeDistances.erase(myDistEntry);
				}

				batchIndices += 3;
			}
			else
			{
				batchSim->endBatch(true);
			}


			

			//remove mentions from fifo and determine for which we have to update weights
			std::unordered_set<uint32_t> removedVertices;
			if (!endofbatch)
			{
				for (auto & entry : cachedIds)
					if (!batchSim->isInCache(entry))
						removedVertices.insert(entry);

				for (auto & entry : removedVertices)
					cachedIds.erase(entry);
			}
			else
			{
				// remove all
				removedVertices.swap(cachedIds);
			}


			for (auto rid : removedVertices)
			{
				VertexData& v = vertexData[rid];

				//if (v.valence != 0)
				{
					for (uint32_t j = v.activeFaceListStart; j < v.activeFaceListEnd; ++j)
					{
						// already done
						uint32_t up_face_start = activeFaceList[j].face_start;
						if (up_face_start == 0xFFFFFFFF)
							continue;

						PriorityUpdate updated(priorityQueue, weights, activeFaceList[j].qentry);
						//add neighbor score
						updated.addNeighbor();

						auto fbatchEntry = activeBatchEntries.find(up_face_start);
						if (fbatchEntry != end(activeBatchEntries))
						{
							updated.reduceCache(1);
							//reduce refernces
							if (--fbatchEntry->second == 0)
							{
								// remove triangle completely
								activeBatchEntries.erase(fbatchEntry);
								auto distEntry = activeDistances.find(up_face_start);
								if (distEntry != end(activeDistances))
								{
									updated.reduceDistance(distEntry->second.accumulated_distances);
									activeDistances.erase(distEntry);
								}

							}
						}

					}
				}
			}

			// batch completed?
			if (endofbatch)
			{
				std::cout << "\r" << priorityQueue.size();
				// clear "cache" => remove "cache" score
				assert(activeBatchEntries.size() == 0);
				assert(activeDistances.size() == 0);

				batchIndices = 0;

				//add finpoint score
				if(weights.FinPointMultiplier != 0)
					for (uint32_t i = best_start; i < best_start + 3; ++i)
					{
						uint32_t vid = in_indices[i];
						VertexData& v = vertexData[vid];
						if (v.valence != 0)
						{
							for (uint32_t j = v.activeFaceListStart; j < v.activeFaceListEnd; ++j)
							{
								// already done
								if (activeFaceList[j].face_start == 0xFFFFFFFF)
									continue;
								PriorityUpdate updated(priorityQueue, weights, activeFaceList[j].qentry);
								updated.addFinpoint();
							}
						}
					}
			}
		}
	}

}

GBatchOptimizer::GBatchOptimizer(SceneSink& next, VertexReuseSimType SimType, std::int32_t CacheWeight, std::int32_t ValenceWeight, std::int32_t DistanceWeight, std::int32_t BatchNeighborWeight, const std::int32_t FinPointMultiplier, bool RemapVertices)
	: ProcessingLayer(next),
	cacheWeight(CacheWeight),
	valenceWeight(ValenceWeight),
	distanceWeight(DistanceWeight),
	batchNeighborWeight(BatchNeighborWeight),
	finPointMultiplier(FinPointMultiplier),
	remapVertices(RemapVertices),
	sim_type(SimType)
{
}

void GBatchOptimizer::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ gbatch optimizer "<< VertexReuseName(sim_type) << " w_c=" << cacheWeight << " w_v=" << valenceWeight << " w_d=" << distanceWeight << " w_n=" << batchNeighborWeight << " w_f=" << finPointMultiplier << "  ------------------\n";


	std::vector<std::uint32_t> new_indices(num_indices);
	std::uint32_t* newIndexList = &new_indices[0];

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type == PrimitiveType::TRIANGLES)
		{
			OptimizeFaces(sim_type, newIndexList, static_cast<uint32_t>(num_vertices), indices + surface->start, surface->num_indices, cacheWeight, valenceWeight, distanceWeight, batchNeighborWeight, finPointMultiplier);
			newIndexList += surface->num_indices;
		}
		else
			throw std::runtime_error("batch optimzer only supports triangles");
	}

	if (remapVertices)
	{
		//resort vertices/indices according to occurence
		std::vector<uint32_t> vertexmapping(num_vertices, 0xFFFFFFFF);
		std::vector<uint32_t> tempvertexmapping(num_vertices, 0xFFFFFFFF);

		std::vector<vertex> remapped_vertices;
		remapped_vertices.reserve(num_vertices);
		uint32_t next_vertex = 0;
		std::vector<uint32_t> remapped_indices(new_indices.size());

		uint32_t maxAllowedDistance = 4 * 1024;
		uint32_t boundary = 0xFFFF + 1;

		for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
		{
			uint32_t invocations = simulateBatch(sim_type, &new_indices[0] + surface->start, num_indices,
				[&](uint32_t bstart, uint32_t bend, auto)
			//simulateBatch(maxIndices, maxUniqueVertices, fifoSize, &new_indices[0] + surface->start, num_indices, [&](uint32_t bstart, uint32_t bend)
			{

				//check for bounded mapping
				uint32_t temp_next_vertex = next_vertex;
				uint32_t minid = 0xFFFFFFFF, maxid = 0;
				uint32_t minvi = 0xFFFFFFFF, maxvi = 0;
				for (uint32_t i = bstart; i < bend; ++i)
				{
					uint32_t vi = new_indices[i + surface->start];
					minvi = std::min(minvi, vi);
					maxvi = std::max(maxvi, vi);
					uint32_t vm = vertexmapping[vi];

					if (vm == 0xFFFFFFFF)
						vm = tempvertexmapping[vi];

					if (vm == 0xFFFFFFFF)
						tempvertexmapping[vi] = vm = temp_next_vertex++;
					minid = std::min(minid, vm);
					maxid = std::max(maxid, vm);
				}

				if (maxid - minid > maxAllowedDistance)
					maxid = temp_next_vertex;


				//simulate with max id
				std::fill(begin(tempvertexmapping) + minvi, begin(tempvertexmapping) + maxvi + 1, 0xFFFFFFFF);
				temp_next_vertex = next_vertex;
				for (uint32_t i = bstart; i < bend; ++i)
				{
					uint32_t vi = new_indices[i + surface->start];
					uint32_t vm = vertexmapping[vi];
					if (vm == 0xFFFFFFFF)
						vm = tempvertexmapping[vi];
					if (vm == 0xFFFFFFFF || vm + maxAllowedDistance < maxid)
						tempvertexmapping[vi] = vm = temp_next_vertex++;
					maxid = std::max(maxid, vm);
				}

				if (next_vertex / boundary != temp_next_vertex / boundary ||
					minid / boundary != (maxid + 1) / boundary)
				{
					//clear mapping and fill up
					std::fill(begin(vertexmapping), end(vertexmapping), 0xFFFFFFFF);
					std::fill(begin(tempvertexmapping), end(tempvertexmapping), 0xFFFFFFFF);
					next_vertex = (next_vertex + boundary - 1) / boundary * boundary;
					remapped_vertices.resize(next_vertex);
				}

				//actual remapping
				for (uint32_t i = bstart; i < bend; ++i)
				{
					uint32_t vi = new_indices[i + surface->start];
					uint32_t vm = vertexmapping[vi];

					if (vm == 0xFFFFFFFF || vm + maxAllowedDistance < maxid)
					{
						vertexmapping[vi] = vm = next_vertex++;
						remapped_vertices.push_back(vertices[vi]);
					}
					remapped_indices[i] = vm;
				}
			});
		}


		/*for (std::size_t i = 0; i < new_indices.size(); ++i)
		{
			uint32_t vi = new_indices[i];
			uint32_t vm = vertexmapping[vi];

			if (vm == 0xFFFFFFFF)
			{
				vertexmapping[vi] = vm = next_vertex++;
				remapped_vertices[vm] = vertices[vi];
			}
			remapped_indices.push_back = vm;
		}*/

		std::cout << "gbatch remapped indices and created " << remapped_vertices.size() - num_vertices << " new vertices\n";

		ProcessingLayer::process(&remapped_vertices[0], remapped_vertices.size(), &remapped_indices[0], remapped_indices.size(), surfaces, num_surfaces, materials, num_materials, textures, num_textures);
	}
	else
		ProcessingLayer::process(vertices, num_vertices, &new_indices[0], new_indices.size(), surfaces, num_surfaces, materials, num_materials, textures, num_textures);

}

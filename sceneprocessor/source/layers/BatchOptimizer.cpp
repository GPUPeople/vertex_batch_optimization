


#include <cassert>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <boost/heap/fibonacci_heap.hpp>

#include "BatchOptimizer.h"


namespace
{
	template<class T>
	using PriorityQueue = boost::heap::fibonacci_heap<T>;

	struct TrianglePriority
	{
		static constexpr uint32_t BaseScore = (1u << 16) - 1;
		static constexpr uint32_t ValenceMultiplier = 1;
		static constexpr uint32_t CacheMultiplier = (1u << 16);

		uint32_t first_vertex;
		uint32_t score;


		TrianglePriority(uint32_t first_vertex, uint32_t score) :
			first_vertex(first_vertex), score(score)
		{
		}
		bool operator < (const TrianglePriority& other) const
		{
			return score < other.score;
		}

		static uint32_t computeScore(uint32_t valence_sum, uint32_t cachedVertices = 0)
		{
			return BaseScore + cachedVertices*CacheMultiplier - ValenceMultiplier*valence_sum;
		}

		bool setScore(uint32_t valence_sum, uint32_t cachedVertices = 0)
		{
			uint32_t prev_score = score;
			score = computeScore(valence_sum, cachedVertices);
			return score > prev_score;
		}
		
		//reduces score
		void addValence(uint32_t valence_sum = 1)
		{
			score -= ValenceMultiplier*valence_sum;
		}

		//increases score
		void reduceValence(uint32_t valence_sum = 1)
		{
			score += ValenceMultiplier*valence_sum;
		}

		//increases score
		void addCache(uint32_t cachedVertices = 1)
		{
			score += cachedVertices*CacheMultiplier;
		}

		//reduces score
		void reduceCache(uint32_t cachedVertices = 1)
		{
			score -= cachedVertices*CacheMultiplier;
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


	void OptimizeFaces(std::uint32_t* out_indices, std::uint32_t num_vertices, const std::uint32_t* in_indices, std::uint32_t num_indices, int max_vertices, int max_indices, int sub_group_vertices)
	{
		assert(max_indices / 3 * 3 == max_indices);

		using Queue = PriorityQueue<TrianglePriority>;

		Queue priorityQueue;
		std::vector<FaceEntry<Queue::handle_type>> activeFaceList;
		std::vector<VertexData> vertexData(num_vertices);
		std::vector<Queue::handle_type> face_lookup(num_indices/3);


		// compute valence/face count per vertex
		for (uint32_t i = 0; i < num_indices; ++i)
		{
			assert(in_indices[i] < num_vertices);
			++vertexData[in_indices[i]].valence;
		}

		//reserve face list
		uint32_t faceListOffset = 0;
		for (auto& v : vertexData)
		{
			v.activeFaceListStart = faceListOffset;
			v.activeFaceListEnd = faceListOffset;
			faceListOffset += v.valence;
		}
		activeFaceList.resize(faceListOffset);


		//compute triangle score and create priority heap
		for (uint32_t i = 0; i < num_indices; i+=3)
		{
			uint32_t vsum = 0;
			for(uint32_t j = 0; j < 3; ++j)
				vsum += vertexData[in_indices[i + j]].valence;

			auto handle = priorityQueue.push({ i , TrianglePriority::computeScore(vsum) });
			face_lookup[i / 3] = handle;

			for (uint32_t j = 0; j < 3; ++j)
			{
				VertexData& v = vertexData[in_indices[i + j]];
				activeFaceList[v.activeFaceListEnd++] = { i, handle };
			}
		}


		//run the greedy optimization
		uint32_t writtenIndices = 0;

		int batchIndices = 0;

		std::unordered_map<uint32_t, uint32_t> activeBatchEntries;
		std::unordered_set<uint32_t> currentBatchIds;
		std::unordered_set<uint32_t> currentSubgroupIds;

		while (!priorityQueue.empty())
		{
			TrianglePriority best = priorityQueue.top();
			//see if we can add the vertices to the batch still
			bool canAdd = true;
	
			uint32_t newvs = 0;
			for (uint32_t i = best.first_vertex; i < best.first_vertex + 3; ++i)
			{
				uint32_t vid = in_indices[i];
				if (currentBatchIds.find(vid) == std::end(currentBatchIds))
					++newvs;
				currentSubgroupIds.insert(vid);
			}

			if (max_vertices > 0 && currentBatchIds.size() + newvs > max_vertices)
				canAdd = false;
			
			if(sub_group_vertices > 0 && currentSubgroupIds.size() > sub_group_vertices)
				canAdd = false;

			if (canAdd)
			{
				//dont want to update data that has been removed
				activeBatchEntries.erase(best.first_vertex);
				priorityQueue.pop();

				//add vertices to cache scores and update valences
				for (uint32_t i = best.first_vertex; i < best.first_vertex + 3; ++i)
				{
					uint32_t vid = in_indices[i];
					out_indices[writtenIndices] = vid;
					++writtenIndices;


					VertexData& v = vertexData[vid];
					v.valence -= 1;
					bool vin = currentBatchIds.find(vid) != std::end(currentBatchIds);
					if(!vin)
						currentBatchIds.insert(vid);
					for (uint32_t j = v.activeFaceListStart; j < v.activeFaceListEnd; ++j)
					{
						if (activeFaceList[j].face_start == 0xFFFFFFFF)
							continue;
						if (activeFaceList[j].face_start == best.first_vertex)
						{
							activeFaceList[j].face_start = 0xFFFFFFFF;
							continue;
						}
						TrianglePriority updated = *activeFaceList[j].qentry;
						updated.reduceValence();
						if (!vin)
						{
							updated.addCache();
							++activeBatchEntries[activeFaceList[j].face_start];
						}
						priorityQueue.increase(activeFaceList[j].qentry, updated);
					}
				}

				batchIndices += 3;
			}
			bool outofSubGroup = sub_group_vertices > 0 && currentSubgroupIds.size() >= sub_group_vertices;
			bool outofVertices = max_vertices > 0 && currentBatchIds.size() + (canAdd ? 0 : newvs) >= max_vertices;
			bool outofIndices = batchIndices >= max_indices;

			if (outofSubGroup || outofVertices || outofIndices)
			{
				//std::cout << "\r" << priorityQueue.size();
				// clear "cache"
				for (auto& it : activeBatchEntries)
				{
					auto& handle = face_lookup[it.first/3];
					TrianglePriority updated = *handle;
					updated.reduceCache(it.second);
					priorityQueue.decrease(handle, updated);
				}
				activeBatchEntries.clear();

				//and reset counters
				if (outofVertices || outofIndices)
				{
					batchIndices = 0;
					currentBatchIds.clear();
					currentSubgroupIds.clear();
				}
				if (outofSubGroup)
					currentSubgroupIds.clear();
			}
		}
	}

}

BatchOptimizer::BatchOptimizer(SceneSink& next, int BatchMaxInidices, int BatchMaxVertices, int SubGroupVertices)
	: ProcessingLayer(next),
	maxIndices(BatchMaxInidices),
	maxVertices(BatchMaxVertices),
	subGroupVertices(SubGroupVertices)
{
}

void BatchOptimizer::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ batch optimizer ind="<< maxIndices << " vert=" << maxVertices << " sub=" << subGroupVertices << "  ------------------\n";


	std::vector<std::uint32_t> new_indices(num_indices);
	std::uint32_t* newIndexList = &new_indices[0];

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type == PrimitiveType::TRIANGLES)
		{
			OptimizeFaces(newIndexList, static_cast<uint32_t>(num_vertices), indices + surface->start, surface->num_indices, maxVertices, maxIndices, subGroupVertices);
			newIndexList += surface->num_indices;
		}
		else
			throw std::runtime_error("batch optimzer only supports triangles");
	}

	ProcessingLayer::process(vertices, num_vertices, &new_indices[0], new_indices.size(), surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}




#include <cassert>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <random>
#include <algorithm>

#include "BatchEnumerator.h"


namespace
{

	struct VertexData
	{
		uint32_t valence;
		uint32_t activeFaceListStart;
		uint32_t activeFaceListEnd;
		VertexData(uint32_t activeFaceListStart = 0, uint32_t activeFaceListEnd = 0, uint32_t valence = 0) :
			valence(valence), activeFaceListStart(activeFaceListStart), activeFaceListEnd(activeFaceListEnd) { }
	};

	template<class T = std::uint32_t>
	class Batch
	{
		std::vector<T> _faces;
	public:
		template<class It>
		Batch(It b, It e)
		{
			while (b != e)
				_faces.push_back(*b++);
			std::sort(std::begin(_faces), std::end(_faces));
		}
		bool operator == (const Batch& other) const
		{
			if (_faces.size() != other._faces.size())
				return false;
			for (auto a = std::begin(_faces), b = std::begin(other._faces); a != std::end(_faces); ++a, ++b)
				if (*a != *b)
					return false;
			return true;
		}
		const std::vector<T>& faces() const
		{
			return _faces;
		}
	};
}
namespace std
{
	template<class T>
	struct hash<Batch<T>>
	{
		std::size_t operator()(Batch<T> const& s) const noexcept
		{
			std::size_t h = 0;
			for (auto& e : s.faces())
				h = h ^ std::hash<T>{}(e);
			return h;
		}
	};
}

namespace
{
	template<class Dist>
	bool randFace(Dist& dist, std::vector<std::uint32_t>& toProcess, std::uint32_t& f)
	{
		std::uniform_int_distribution<std::size_t> d(0, toProcess.size() - 1);
		std::size_t entry = d(dist);
		for (std::size_t t = entry; t < toProcess.size(); ++t)
		{
			if (toProcess[t] == 1)
			{
				//toProcess[t] = 0;
				f = static_cast<uint32_t>(3 * t);
				return true;
			}
		}
		for (std::size_t t = 0; t < entry; ++t)
		{
			if (toProcess[t] == 1)
			{
				//toProcess[t] = 0;
				f = static_cast<uint32_t>(3*t);
				return true;
			}
		}
		return false;
	}
	uint32_t addFace(std::vector<std::uint32_t>& batches, std::uint32_t f, const std::uint32_t* in_indices, std::map<uint32_t, uint32_t>& candidate_front, const std::vector<VertexData>& vertexData, const std::vector<std::uint32_t>& activeFaceList, std::vector<std::uint32_t>& toProcess)
	{
		auto found = candidate_front.find(f);
		uint32_t c = 0;
		if (found != std::end(candidate_front))
		{
			c = found->second;
			candidate_front.erase(found);
		}

		batches.push_back(f);
		//batches.push_back(in_indices[f]);
		//batches.push_back(in_indices[f + 1]);
		//batches.push_back(in_indices[f + 2]);

		//remove from toProcess
		toProcess[f / 3] = 0;

		//add neighbors to candidates
		for (std::uint32_t v = 0; v < 3; ++v)
		{
			std::uint32_t i = in_indices[f + v];
			for (uint32_t oF = vertexData[i].activeFaceListStart; oF < vertexData[i].activeFaceListEnd; ++oF)
			{
				std::uint32_t f = activeFaceList[oF];
				if (toProcess[f / 3] == 1)
				{
					auto found = candidate_front.find(f);
					if (found != std::end(candidate_front))
					{
						++found->second;
					}
					else
						candidate_front.insert(std::make_pair(f, 1));
				}
					
			}
		}
		return c;
	}
	void removeFace(std::vector<std::uint32_t>& batches, std::uint32_t f, std::uint32_t n, const std::uint32_t* in_indices, std::map<uint32_t, uint32_t>& candidate_front, const std::vector<VertexData>& vertexData, const std::vector<std::uint32_t>& activeFaceList, std::vector<std::uint32_t>& toProcess)
	{
		batches.pop_back();
		//batches.pop_back();
		//batches.pop_back();
		//batches.pop_back();

		//remove neighbors from candidates
		for (std::uint32_t v = 0; v < 3; ++v)
		{
			std::uint32_t i = in_indices[f + v];
			for (uint32_t oF = vertexData[i].activeFaceListStart; oF < vertexData[i].activeFaceListEnd; ++oF)
			{
				if (toProcess[oF / 3] == 1)
				{
					auto found = candidate_front.find(oF);
					if (found != std::end(candidate_front))
					{
						if (--found->second == 0)
							candidate_front.erase(found);
					}
				}

			}
		}

		//add to toProcess
		toProcess[f / 3] = 1;

		//add to candidates
		candidate_front.insert(std::make_pair(f, n));
	}

	template<class It>
	It moveIt(It it, std::size_t t)
	{
		while (t > 0)
		{
			++it;
			--t;
		}
		return it;
	}

	std::size_t computeScore(const Batch<std::uint32_t>& b, const std::uint32_t* in_indices)
	{
		std::size_t cost = 0;
		std::unordered_set<std::uint32_t> uniques;
		for (const auto& f : b.faces())
		{
			for (uint32_t v = 0; v < 3; ++v)
			{
				uint32_t i = in_indices[f + v];
				if (uniques.find(i) == std::end(uniques))
				{
					++cost;
					uniques.insert(i);
				}
			}
		}
		return cost;
	}

	void OptimizeFaces(std::uint32_t* out_indices, std::uint32_t num_vertices, const std::uint32_t* in_indices, std::uint32_t num_indices, int max_vertices, int max_indices)
	{
		assert(max_indices / 3 * 3 == max_indices);

		std::vector<VertexData> vertexData(num_vertices);
		std::vector<std::uint32_t> activeFaceList;

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

		//setup active face list
		activeFaceList.resize(faceListOffset);
		for (uint32_t i = 0; i < num_indices; i += 3)
		{
			for (uint32_t j = 0; j < 3; ++j)
			{
				VertexData& v = vertexData[in_indices[i + j]];
				activeFaceList[v.activeFaceListEnd++] = i;
			}
		}
		std::vector<std::uint32_t> toProcess(num_indices / 3, 1);

		std::size_t best_score = num_indices + 1;
		std::vector<std::uint32_t> best_batches;

		std::vector<std::uint32_t> batches;
		std::unordered_map<Batch<uint32_t>, std::pair<std::size_t, std::size_t>> batch_scores;
		std::unordered_set<Batch<std::size_t>> visited_traces;

		//stupid all enum algorithm
		//TODO: only works properly for connected mesh
		//TODO: better start
		
		std::uint_fast64_t seed = 12345;
		std::mt19937_64 rnd(seed);
		
		std::uint32_t f;
		randFace(rnd, toProcess, f);

		
		std::map<uint32_t, uint32_t> candidate_front;
		addFace(batches, f, in_indices, candidate_front, vertexData, activeFaceList, toProcess);

		std::vector<std::pair<uint32_t, std::pair<uint32_t, uint32_t>>> state;
		std::vector<std::size_t> score_states;
		std::vector<std::size_t> batch_trace;
		std::size_t batch_counter = 0;
		score_states.push_back(0);
		state.push_back(std::make_pair(0xFFFFFFFF, std::make_pair(0,0)));

		std::size_t batchIds = 3;
		while (state.size() > 0)
		{
			uint32_t f;
			bool done = false;
			if (candidate_front.size() == 0)
			{
				// non connected mesh case or done
				if (randFace(rnd, toProcess, f))
					candidate_front.insert(std::make_pair(f,1));
				else
				{
					//done
					done = true;
					//compute score for the remaining and update best!
					std::size_t rem = batchIds % max_indices;
					Batch<uint32_t> b(batches.rbegin(), batches.rbegin() + rem / 3);
					std::size_t score = computeScore(b, in_indices);
					for (const auto& s : score_states)
						score += s;
					if (score < best_score)
					{ 
						best_batches = batches;
						best_score = score;
						std::cout << "overall new best score: " << score << std::endl;
					}
					state.pop_back();
					batchIds -= 3;
					//for (auto it = batches.rbegin(); it != batches.rbegin() + rem / 3; ++it)
					//	std::cout << *it << " ";
					std::cout << "overall score: " << score << std::endl;
				}
			}

			// are coming out?
			if (state.back().first != 0xFFFFFFFF)
			{
				//take the last face off
				removeFace(batches, state.back().second.first, state.back().second.second, in_indices, candidate_front, vertexData, activeFaceList, toProcess);
				++state.back().first;
			}
			else if (state.back().first == 0xFFFFFFFF)
				state.back().first = 0;


			if (state.back().first == candidate_front.size())
			{
				//go one out
				state.pop_back();
				
				if (batchIds % max_indices == 0)
				{
					score_states.pop_back();
				}
				batchIds -= 3;
				continue;
			}

			// find the triangle to add
			f = moveIt(candidate_front.begin(), state.back().first)->first;


			uint32_t n = addFace(batches, f, in_indices, candidate_front, vertexData, activeFaceList, toProcess);
			//store information about the face we just used
			state.back().second = std::make_pair(f, n);
			
			batchIds += 3;
			if (batchIds % max_indices == 0)
			{
				// check if that batch already exists
				Batch<uint32_t> b(batches.rbegin(), batches.rbegin() + max_indices / 3);
				auto found = batch_scores.find(b);
				
				std::size_t unique_id, score;
				if (found == std::end(batch_scores))
				{
					// if not compute batch score and get unique identificer for batch
					score = computeScore(b, in_indices);
					unique_id = batch_counter++;
					batch_scores.insert(std::make_pair(b, std::make_pair(score, unique_id)));
					batch_trace.push_back(unique_id);
					visited_traces.emplace(std::begin(batch_trace), std::end(batch_trace));
						
					std::cout << "new batch " << unique_id  << "  @ " << state.size() << " with score " << score << std::endl;
				}
				else
				{
					// otherwise check if we have been at that configuration before using the unique id
					score = found->second.first;
					unique_id = found->second.second;
					batch_trace.push_back(unique_id);

					std::cout << "known batch " << unique_id << "  @ " << state.size() << " with score " << score << std::endl;

					Batch<std::size_t> this_trace(std::begin(batch_trace), std::end(batch_trace));
					if (visited_traces.find(this_trace) != std::end(visited_traces))
					{
						// if so -> continue with other
						std::cout << "known state @ " << state.size() << std::endl;

						removeFace(batches, f, n, in_indices, candidate_front, vertexData, activeFaceList, toProcess);
						batchIds -= 3;
						continue;
					}
					visited_traces.insert(this_trace);
				}
				//update score
				score_states.push_back(score);
			}
			//go in
			state.push_back(std::make_pair(0xFFFFFFFF, std::make_pair(0, 0)));
		}

		uint32_t * oi = out_indices;
		for (auto& i : best_batches)
		{
			*oi++ = in_indices[i+0];
			*oi++ = in_indices[i+1];
			*oi++ = in_indices[i+2];
		}
	}

}

BatchEnumerator::BatchEnumerator(SceneSink& next, int BatchMaxInidices, int BatchMaxVertices)
	: ProcessingLayer(next),
	 maxIndices(BatchMaxInidices),
	 maxVertices(BatchMaxVertices)
{
}

void BatchEnumerator::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ batch enumerator ind="<< maxIndices << " vert=" << maxVertices  << "  ------------------\n";


	std::vector<std::uint32_t> new_indices(num_indices);
	std::uint32_t* newIndexList = &new_indices[0];

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type == PrimitiveType::TRIANGLES)
		{
			OptimizeFaces(newIndexList, static_cast<uint32_t>(num_vertices), indices + surface->start, surface->num_indices, maxVertices, maxIndices);
			newIndexList += surface->num_indices;
		}
		else
			throw std::runtime_error("batch enumerator only supports triangles");
	}

	ProcessingLayer::process(vertices, num_vertices, &new_indices[0], new_indices.size(), surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

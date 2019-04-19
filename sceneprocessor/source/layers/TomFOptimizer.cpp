//-----------------------------------------------------------------------------
//  Original: https://github.com/bkaradzic/bgfx/blob/master/3rdparty/forsyth-too/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  This is an implementation of Tom Forsyth's "Linear-Speed Vertex Cache 
//  Optimization" algorithm as described here:
//  http://home.comcast.net/~tom_forsyth/papers/fast_vert_cache_opt.html
//
//  This code was authored and released into the public domain by
//  Adrian Stone (stone@gameangst.com).
//
//  THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//  SHALL ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
//  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <vector>
#include <limits>
#include <algorithm>
#include <memory>
#include <iostream>

#include "TomFOptimizer.h"


namespace
{
	// code for computing vertex score was taken, as much as possible
	// directly from the original publication.
	float ComputeVertexCacheScore(int cachePosition, int vertexCacheSize)
	{
		const float FindVertexScore_CacheDecayPower = 1.5f;
		const float FindVertexScore_LastTriScore = 0.75f;

		float score = 0.0f;
		if (cachePosition < 0)
		{
			// Vertex is not in FIFO cache - no score.
		}
		else
		{
			if (cachePosition < 3)
			{
				// This vertex was used in the last triangle,
				// so it has a fixed score, whichever of the three
				// it's in. Otherwise, you can get very different
				// answers depending on whether you add
				// the triangle 1,2,3 or 3,1,2 - which is silly.
				score = FindVertexScore_LastTriScore;
			}
			else
			{
				assert(cachePosition < vertexCacheSize);
				// Points for being high in the cache.
				const float scaler = 1.0f / (vertexCacheSize - 3);
				score = 1.0f - (cachePosition - 3) * scaler;
				score = powf(score, FindVertexScore_CacheDecayPower);
			}
		}

		return score;
	}

	float ComputeVertexValenceScore(uint32_t numActiveFaces)
	{
		const float FindVertexScore_ValenceBoostScale = 2.0f;
		const float FindVertexScore_ValenceBoostPower = 0.5f;

		float score = 0.f;

		// Bonus points for having a low number of tris still to
		// use the vert, so we get rid of lone verts quickly.
		float valenceBoost = powf(static_cast<float>(numActiveFaces),
			-FindVertexScore_ValenceBoostPower);
		score += FindVertexScore_ValenceBoostScale * valenceBoost;

		return score;
	}


	const int kMaxVertexCacheSize = 256;
	const uint32_t kMaxPrecomputedVertexValenceScores = 256;
	float s_vertexCacheScores[kMaxVertexCacheSize + 1][kMaxVertexCacheSize];
	float s_vertexValenceScores[kMaxPrecomputedVertexValenceScores];

	bool ComputeVertexScores()
	{
		for (int cacheSize = 0; cacheSize <= kMaxVertexCacheSize; ++cacheSize)
		{
			for (int cachePos = 0; cachePos<cacheSize; ++cachePos)
			{
				s_vertexCacheScores[cacheSize][cachePos] = ComputeVertexCacheScore(cachePos, cacheSize);
			}
		}

		for (uint32_t valence = 0; valence<kMaxPrecomputedVertexValenceScores; ++valence)
		{
			s_vertexValenceScores[valence] = ComputeVertexValenceScore(valence);
		}

		return true;
	}
	bool s_vertexScoresComputed = ComputeVertexScores();

	//        inline float FindVertexCacheScore(uint cachePosition, uint maxSizeVertexCache)
	//        {
	//            return s_vertexCacheScores[maxSizeVertexCache][cachePosition];
	//        }

	//        inline float FindVertexValenceScore(uint numActiveTris)
	//        {
	//            return s_vertexValenceScores[numActiveTris];
	//        }

	float FindVertexScore(uint32_t numActiveFaces, uint32_t cachePosition, uint32_t vertexCacheSize)
	{
		assert(s_vertexScoresComputed); (void)s_vertexScoresComputed;

		if (numActiveFaces == 0)
		{
			// No tri needs this vertex!
			return -1.0f;
		}

		float score = 0.f;
		if (cachePosition < vertexCacheSize)
		{
			score += s_vertexCacheScores[vertexCacheSize][cachePosition];
		}

		if (numActiveFaces < kMaxPrecomputedVertexValenceScores)
		{
			score += s_vertexValenceScores[numActiveFaces];
		}
		else
		{
			score += ComputeVertexValenceScore(numActiveFaces);
		}

		return score;
	}

	struct OptimizeVertexData
	{
		float   score;
		uint32_t    activeFaceListStart;
		uint32_t    activeFaceListSize;
		uint32_t  cachePos0;
		uint32_t  cachePos1;
		OptimizeVertexData() : score(0.f), activeFaceListStart(0), activeFaceListSize(0), cachePos0(0), cachePos1(0) { }
	};

	void OptimizeFaces(std::uint32_t* newIndexList, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, uint32_t lruCacheSize)
	{
		std::vector<OptimizeVertexData> vertexDataList;
		vertexDataList.resize(num_vertices);

		// compute face count per vertex
		for (uint32_t i = 0; i < num_indices; ++i)
		{
			uint32_t index = indices[i];
			assert(index < num_vertices);
			OptimizeVertexData& vertexData = vertexDataList[index];
			vertexData.activeFaceListSize++;
		}

		std::vector<uint32_t> activeFaceList;

		const uint32_t kEvictedCacheIndex = std::numeric_limits<uint32_t>::max();

		{
			// allocate face list per vertex
			uint32_t curActiveFaceListPos = 0;
			for (uint32_t i = 0; i < num_vertices; ++i)
			{
				OptimizeVertexData& vertexData = vertexDataList[i];
				vertexData.cachePos0 = kEvictedCacheIndex;
				vertexData.cachePos1 = kEvictedCacheIndex;
				vertexData.activeFaceListStart = curActiveFaceListPos;
				curActiveFaceListPos += vertexData.activeFaceListSize;
				vertexData.score = FindVertexScore(vertexData.activeFaceListSize, vertexData.cachePos0, lruCacheSize);
				vertexData.activeFaceListSize = 0;
			}
			activeFaceList.resize(curActiveFaceListPos);
		}

		// fill out face list per vertex
		for (uint32_t i = 0; i < num_indices; i += 3)
		{
			for (uint32_t j = 0; j<3; ++j)
			{
				uint32_t index = indices[i + j];
				OptimizeVertexData& vertexData = vertexDataList[index];
				activeFaceList[vertexData.activeFaceListStart + vertexData.activeFaceListSize] = i;
				vertexData.activeFaceListSize++;
			}
		}

		std::vector<uint8_t> processedFaceList;
		processedFaceList.resize(num_indices);

		//uint32_t vertexCacheBuffer[(kMaxVertexCacheSize + 3) * 2];
		//uint32_t* cache0 = vertexCacheBuffer;
		//uint32_t* cache1 = vertexCacheBuffer + (kMaxVertexCacheSize + 3);

		std::vector<uint32_t> cache0(kMaxVertexCacheSize + 3);
		std::vector<uint32_t> cache1(kMaxVertexCacheSize + 3);
		uint32_t entriesInCache0 = 0;

		uint32_t bestFace = 0;
		float bestScore = -1.f;

		const float maxValenceScore = FindVertexScore(1, kEvictedCacheIndex, lruCacheSize) * 3.f;

		for (uint32_t i = 0; i < num_indices; i += 3)
		{
			if (bestScore < 0.f)
			{
				// no verts in the cache are used by any unprocessed faces so
				// search all unprocessed faces for a new starting point
				for (uint32_t j = 0; j < num_indices; j += 3)
				{
					if (processedFaceList[j] == 0)
					{
						uint32_t face = j;
						float faceScore = 0.f;
						for (uint32_t k = 0; k<3; ++k)
						{
							uint32_t index = indices[face + k];
							OptimizeVertexData& vertexData = vertexDataList[index];
							assert(vertexData.activeFaceListSize > 0);
							assert(vertexData.cachePos0 >= lruCacheSize);
							faceScore += vertexData.score;
						}

						if (faceScore > bestScore)
						{
							bestScore = faceScore;
							bestFace = face;

							assert(bestScore <= maxValenceScore);
							if (bestScore >= maxValenceScore)
							{
								break;
							}
						}
					}
				}
				assert(bestScore >= 0.f);
			}

			processedFaceList[bestFace] = 1;
			uint32_t entriesInCache1 = 0;

			// add bestFace to LRU cache and to newIndexList
			for (uint32_t v = 0; v < 3; ++v)
			{
				uint32_t index = indices[bestFace + v];
				newIndexList[i + v] = index;

				OptimizeVertexData& vertexData = vertexDataList[index];

				if (vertexData.cachePos1 >= entriesInCache1)
				{
					vertexData.cachePos1 = entriesInCache1;
					cache1[entriesInCache1++] = index;

					if (vertexData.activeFaceListSize == 1)
					{
						--vertexData.activeFaceListSize;
						continue;
					}
				}

				assert(vertexData.activeFaceListSize > 0);
				uint32_t* begin = &activeFaceList[vertexData.activeFaceListStart];
				uint32_t* end = &(activeFaceList[vertexData.activeFaceListStart + vertexData.activeFaceListSize - 1]) + 1;
				uint32_t* it = std::find(begin, end, bestFace);
				assert(it != end);
				std::swap(*it, *(end - 1));
				--vertexData.activeFaceListSize;
				vertexData.score = FindVertexScore(vertexData.activeFaceListSize, vertexData.cachePos1, lruCacheSize);

			}

			// move the rest of the old verts in the cache down and compute their new scores
			for (uint32_t c0 = 0; c0 < entriesInCache0; ++c0)
			{
				uint32_t index = cache0[c0];
				OptimizeVertexData& vertexData = vertexDataList[index];

				if (vertexData.cachePos1 >= entriesInCache1)
				{
					vertexData.cachePos1 = entriesInCache1;
					cache1[entriesInCache1++] = index;
					vertexData.score = FindVertexScore(vertexData.activeFaceListSize, vertexData.cachePos1, lruCacheSize);
				}
			}

			// find the best scoring triangle in the current cache (including up to 3 that were just evicted)
			bestScore = -1.f;
			for (uint32_t c1 = 0; c1 < entriesInCache1; ++c1)
			{
				uint32_t index = cache1[c1];
				OptimizeVertexData& vertexData = vertexDataList[index];
				vertexData.cachePos0 = vertexData.cachePos1;
				vertexData.cachePos1 = kEvictedCacheIndex;
				for (uint32_t j = 0; j<vertexData.activeFaceListSize; ++j)
				{
					uint32_t face = activeFaceList[vertexData.activeFaceListStart + j];
					float faceScore = 0.f;
					for (uint32_t v = 0; v<3; v++)
					{
						uint32_t faceIndex = indices[face + v];
						OptimizeVertexData& faceVertexData = vertexDataList[faceIndex];
						faceScore += faceVertexData.score;
					}
					if (faceScore > bestScore)
					{
						bestScore = faceScore;
						bestFace = face;
					}
				}
			}

			std::swap(cache0, cache1);
			entriesInCache0 = std::min(entriesInCache1, lruCacheSize);
		}
	}
}

TomFOptimizer::TomFOptimizer(SceneSink& next)
	: ProcessingLayer(next)
{
}

void TomFOptimizer::optimize(std::uint32_t* newIndexList, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, uint32_t lruCacheSize)
{
	OptimizeFaces(newIndexList, num_vertices, indices, num_indices, lruCacheSize);
}

void TomFOptimizer::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ tomf optimizer ------------------\n";

	uint32_t lruCacheSize = 96;
	lruCacheSize = std::min<uint32_t>(lruCacheSize, kMaxVertexCacheSize);

	std::vector<std::uint32_t> new_indices(num_indices);
	uint32_t* newIndexList = &new_indices[0];

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type == PrimitiveType::TRIANGLES)
		{
			OptimizeFaces(newIndexList, num_vertices, indices + surface->start, surface->num_indices, lruCacheSize);
			newIndexList += surface->num_indices;
		}
		else
			throw std::runtime_error("tomF only supports triangles");
	}

	ProcessingLayer::process(vertices, num_vertices, &new_indices[0], new_indices.size(), surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}
 
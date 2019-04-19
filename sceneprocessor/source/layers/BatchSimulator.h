#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdint.h>
#include <algorithm>


#if 0

template<typename BatchEnd>
uint32_t simulateBatch(uint32_t batchIndices, uint32_t batchVertices, uint32_t fifoLength, const std::uint32_t* indices, std::size_t num_indices,
	BatchEnd batchend)
{
	uint32_t invocations = 0;
	uint32_t cbatch = 0;
	uint32_t cuniques = 0;

	std::unordered_set<std::uint32_t> batchcachev;
	//std::unordered_map<std::uint32_t,std::uint32_t> batchvid;
	std::vector<std::uint32_t> keepalive(batchIndices, 0xFFFFFFFF);
	std::vector<uint32_t> lasts(3, 0xFFFFFFFF);

	//std::vector < std::tuple<std::size_t, uint32_t, uint32_t, uint32_t>> boundadries;
	for (uint32_t i = 0; i < num_indices; )
	{
		std::uint32_t id = indices[i];
		if (batchcachev.find(id) == end(batchcachev))
		{
			batchcachev.insert(id);
			++invocations;
			++cuniques;

			lasts[2] = id;
		}

		//auto knownvid = batchvid.find(id);
		//if (knownvid != end(batchvid))
		//	++knownvid->second;
		//else
		//	batchvid[id] = 1;

		for (std::size_t j = cbatch; j < std::min(batchIndices, cbatch + fifoLength); ++j)
		{
			if (keepalive[j] == id)
				keepalive[j] = 0xFFFFFFFF;
		}
		if (cbatch + fifoLength < batchIndices)
			keepalive[cbatch + fifoLength] = id;

		if (keepalive[cbatch] != 0xFFFFFFFF)
			batchcachev.erase(keepalive[cbatch]);

		++i;
		++cbatch;
		bool reset = false;
		if (cuniques > batchVertices)
		{
			reset = true;
			uint32_t putback = 1 + ((i - 1) % 3);
			i = i - putback;
			cbatch = cbatch - putback;
			for (uint32_t j = 3 - putback; j < 3; ++j)
			{
				if (lasts[j] != 0xFFFFFFFF)
				{
					--invocations;
					//if (--batchvid[lasts[j]] == 0)
					//	batchvid.erase(lasts[j]);
				}
			}
			//boundadries.push_back(std::make_tuple(i, 1, cbatch - putback, putback));
		}
		else if (cbatch == batchIndices)
		{
			reset = true;
			//boundadries.push_back(std::make_tuple(i, 0, cuniques, cbatch));
		}
		if (reset)
		{
			batchend(i - cbatch, i);
			std::fill(begin(keepalive), end(keepalive), 0xFFFFFFFF);
			batchcachev.clear();
			//batchvid.clear();
			cbatch = 0;
			cuniques = 0;
		}

		// move lasts
		lasts[0] = lasts[1];
		lasts[1] = lasts[2];
		lasts[2] = 0xFFFFFFFF;
	}
	batchend(static_cast<uint32_t>(num_indices - cbatch), static_cast<uint32_t>(num_indices));
	return invocations;
}

#else


class ForeverCacheEntry
{
public:
	ForeverCacheEntry(uint32_t index)
	{
	}
	bool cached(uint32_t current) const
	{
		return true;
	}
	void update(uint32_t index)
	{
	}
};


class NVGLCacheEntry
{
	uint32_t last;
public:
	NVGLCacheEntry(uint32_t index) : last(index)
	{
	}
	bool cached(uint32_t current) const
	{
		return current - last <= 42;
	}
	void update(uint32_t index)
	{
		last = index;
	}
};
class NVDxCacheEntry
{
	uint32_t last;
public:
	NVDxCacheEntry(uint32_t index) : last(index)
	{
	}
	bool cached(uint32_t current) const
	{
		uint32_t d = current - last;
		uint32_t type = last % 3;
		if (type == 0)
			return d < 45;
		if (type == 1)
			return d <= 40 || d == 42;
		//if (type == 2)
		return d <= 39 || d == 41 || d == 42;
	}
	void update(uint32_t index)
	{
		last = index;
	}
};

template<class CacheEntry>
class FIFOCacheSim
{
	std::unordered_map<std::uint32_t, CacheEntry> alive;
public:
	bool cached(uint32_t vertex_index, uint32_t index_location)  const
	{
		auto found = alive.find(vertex_index);
		if (found == end(alive))
			return false;
		else
			return found->second.cached(index_location);
	}
	void insert(uint32_t vertex_index, uint32_t index_location)
	{
		//already done at lookup
		auto found = alive.find(vertex_index);
		if (found == end(alive))
			alive.insert(std::make_pair(vertex_index, CacheEntry(index_location)));
		else
			found->second.update(index_location);
	}
	void reset(bool hard)
	{
		alive.clear();
	}
};

using NVDxCacheSim = FIFOCacheSim<NVDxCacheEntry>;
using NVGLCacheSim = FIFOCacheSim<NVGLCacheEntry>;

template<uint32_t Size>
class LRUCacheSim
{
	std::uint32_t buffer[Size];
	uint32_t front, size;
public:
	LRUCacheSim() : front(0), size(0) { }

	bool cached(uint32_t vertex_index, uint32_t index_location) const
	{
		for (uint32_t i = 0; i < size; ++i)
		{
			if (buffer[(front + i) % Size] == vertex_index)
				return true;
		}
		return false;
	}
	void insert(uint32_t vertex_index, uint32_t index_location)
	{
		uint32_t loc = 0xFFFFFFFF;
		for (uint32_t i = 0; i < size; ++i)
		{
			if (buffer[(front + i) % Size] == vertex_index)
			{
				loc = i;
				break;
			}
		}

		if (loc == 0xFFFFFFFF)
		{
			// insert or overwrite
			if (size == Size)
				front = (front + 1) % Size;
			else
				++size;
		}
		else
		{
			// update -> move to front
			for (uint32_t i = loc + 1; i < size; ++i)
				buffer[(front + i - 1) % Size] = buffer[(front + i) % Size];
		}
		buffer[(front + size - 1) % Size] = vertex_index;
	}
	void reset(bool hard)
	{
		if (hard)
			front = size = 0;
	}
};


template<typename CacheSim>
class BatchState
{
	uint32_t invocations;
	uint32_t cbatch;
	uint32_t cuniques;
	uint32_t progress;
	uint32_t last_hard_reset;

	CacheSim cache;
	std::vector<uint32_t> calls;

	uint32_t batchIndices, batchVertices, hard_reset;
	bool triangle_bounds;

	template<typename BatchEnd>
	void pendBatch(CacheSim& c, bool hard, BatchEnd batchEnd = [](uint32_t, uint32_t, auto) {})
	{
		batchEnd(progress - cbatch - 1, progress + 1, calls);
		c.reset(hard);
		calls.clear();
		cbatch = 0;
		cuniques = 0;
		last_hard_reset = progress;

	}
public:
	BatchState(uint32_t batchIndices, uint32_t batchVertices, uint32_t hard_reset, bool triangle_bounds) :
		invocations(0), cbatch(0), cuniques(0), progress(0), last_hard_reset(0),
		batchIndices(batchIndices), 
		batchVertices(batchVertices),
		hard_reset(hard_reset),
		triangle_bounds(triangle_bounds)
	{ }

	bool isInCache(uint32_t id) const
	{
		return cache.cached(id, progress);
	}
	int32_t canAddTriangle(const uint32_t indices[3])
	{
		if (progress % hard_reset == 0 && last_hard_reset != progress)
		{
			//hard reset
			return 2;
		}
		if (cbatch + 3 > batchIndices)
			return 2;

		uint32_t adds = 0;
		CacheSim ccopy = cache;
		for(uint32_t i = 0; i < 3; ++i)
		{
			if (!ccopy.cached(indices[i], progress + i))
				++adds;
			ccopy.insert(indices[i], progress + i);
		}
		if (cuniques + adds > batchVertices)
			return hard_reset != 0xFFFFFFFF ? 1 : 2;

		return -3+static_cast<int>(adds);
		
	}
	int32_t canAddTriangle(const uint32_t* indices, uint32_t offset)
	{
		uint32_t ind[3] = { indices[offset + 0], indices[offset + 1], indices[offset + 2] };
		return canAddTriangle(ind);
	}
	template<typename BatchEnd>
	void addTriangle(const uint32_t indices[3], BatchEnd batchEnd = [](uint32_t, uint32_t, auto) {})
	{
		if (progress % hard_reset == 0 && last_hard_reset != progress)
		{
			//hard reset
			pendBatch(cache, true, batchEnd);
		}

		CacheSim ccopy = cache;
		uint32_t adds = 0;
		uint32_t move = 3;
		std::vector<uint32_t> tempCalls;
		for (uint32_t i = 0; i < 3; ++i)
		{
			if (!ccopy.cached(indices[i], progress + i))
			{ 
				++adds;
				tempCalls.push_back(indices[i]);
			}
			
			bool reset_state = false;
			if (cuniques + adds > batchVertices)
				reset_state = true;
			if (cbatch + i + 1 > batchIndices)
				reset_state = true;

			if (reset_state == false)
				ccopy.insert(indices[i], progress + i);
			else if(triangle_bounds)
			{
				// reset to triangle
				pendBatch(cache, false, batchEnd);
				ccopy = cache;
				adds = 0;
				tempCalls.clear();
				for (uint32_t j = 0; j <= i; ++j)
				{
					if (!ccopy.cached(indices[j], progress + j))
					{
						++adds;
						calls.push_back(indices[j]);
					}
					ccopy.insert(indices[j], progress + j);
				}
			}
			else
			{
				cuniques += adds - 1;
				invocations += adds - 1;
				cbatch += i;
				progress += i;
				calls.insert(end(calls), begin(tempCalls), end(tempCalls));

				pendBatch(ccopy, false, batchEnd);

				tempCalls.clear();
				adds = 1;
				move -= i;
				ccopy.insert(indices[i], progress + i);
			}
		}

		//for (uint32_t i = 0; i < 3; ++i)
		//	std::cout << indices[i] << " ";
		//std::cout << " - " << adds << "\n";
		cache = ccopy;
		cuniques += adds;
		invocations += adds;
		cbatch += move;
		progress += move;
		calls.insert(end(calls), begin(tempCalls), end(tempCalls));
	}
	template<typename BatchEnd>
	void addTriangle(const uint32_t* indices, uint32_t offset, BatchEnd batchEnd = [](uint32_t, uint32_t, auto) {})
	{
		uint32_t ind[3] = { indices[offset + 0], indices[offset + 1], indices[offset + 2] };
		return addTriangle(ind, batchEnd);
	}

	
	template<typename BatchEnd>
	void endBatch(bool hard, BatchEnd batchEnd = [](uint32_t, uint32_t, auto) {})
	{
		pendBatch(cache, hard, batchEnd);
	}
	void reset()
	{
		progress = 0;
		pendBatch(cache, true, [](uint32_t, uint32_t, auto) {});
	}
	uint32_t getInvocations() const
	{
		return invocations;
	}
};

template<typename CacheSim, typename BatchEnd>
uint32_t simulateBatch(uint32_t batchIndices, uint32_t batchVertices,
	const std::uint32_t* indices, std::size_t num_indices,
	bool triangle_bounds, uint32_t hard_reset,
	BatchEnd batchend)
{
	BatchState<CacheSim> cs(batchIndices, batchVertices, hard_reset, triangle_bounds);

	for (uint32_t i = 0; i < num_indices; i+=3)
		cs.addTriangle(indices, i, batchend);

	cs.endBatch(true, batchend);

	return cs.getInvocations();

	uint32_t invocations = 0;
	uint32_t cbatch = 0;
	uint32_t cuniques = 0;

	//std::unordered_set<std::uint32_t> batchcachev;
	//std::unordered_map<std::uint32_t,std::uint32_t> batchvid;
	//std::vector<std::uint32_t> keepalive(batchIndices, 0xFFFFFFFF);

	CacheSim cache;
	std::vector<uint32_t> lasts(3, 0xFFFFFFFF);
	std::vector<uint32_t> calls;

	//std::vector < std::tuple<std::size_t, uint32_t, uint32_t, uint32_t>> boundadries;
	for (uint32_t i = 0; i < num_indices; )
	{
		std::uint32_t id = indices[i];
		if (!cache.cached(id, i))
		{
			calls.emplace_back(id);
			++invocations;
			++cuniques;

			lasts[2] = id;
		}

		//auto knownvid = batchvid.find(id);
		//if (knownvid != end(batchvid))
		//	++knownvid->second;
		//else
		//	batchvid[id] = 1;

		//for (std::size_t j = cbatch; j < std::min(batchIndices, cbatch + fifoLength); ++j)
		//{
		//	if (keepalive[j] == id)
		//		keepalive[j] = 0xFFFFFFFF;
		//}
		//if (cbatch + fifoLength < batchIndices)
		//	keepalive[cbatch + fifoLength] = id;

		//if (keepalive[cbatch] != 0xFFFFFFFF)
		//	batchcachev.erase(keepalive[cbatch]);

		++i;
		++cbatch;
		bool reset = false;
		if (cuniques > batchVertices)
		{
			reset = true;
			uint32_t putback = triangle_bounds ? 1 + ((i - 1) % 3) : 1;
			i = i - putback;
			cbatch = cbatch - putback;
			for (uint32_t j = 3 - putback; j < 3; ++j)
			{
				if (lasts[j] != 0xFFFFFFFF)
				{
					--invocations;
					//if (--batchvid[lasts[j]] == 0)
					//	batchvid.erase(lasts[j]);
					calls.pop_back();
				}
			}
			//boundadries.push_back(std::make_tuple(i, 1, cbatch - putback, putback));
		}
		else if (cbatch == batchIndices || i % hard_reset == 0)
		{
			reset = true;
			cache.insert(id, i - 1);
			//boundadries.push_back(std::make_tuple(i, 0, cuniques, cbatch));
		}
		if (reset)
		{
			batchend(i - cbatch, i, calls);
			//std::fill(begin(keepalive), end(keepalive), 0xFFFFFFFF);
			//batchcachev.clear();
			cache.reset(i % hard_reset == 0);
			calls.clear();
			//batchvid.clear();
			cbatch = 0;
			cuniques = 0;
		}
		else
			cache.insert(id, i - 1);

		// move lasts
		lasts[0] = lasts[1];
		lasts[1] = lasts[2];
		lasts[2] = 0xFFFFFFFF;
	}
	if (cbatch != 0)
		batchend(static_cast<uint32_t>(num_indices - cbatch), static_cast<uint32_t>(num_indices), calls);
	return invocations;
}
#endif
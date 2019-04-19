


#include <memory>
#include <algorithm>
#include <numeric>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <functional>

#include <core/utils/io>

#include "VertexReuseStats.h"
#include "BatchSimulator.h"


namespace
{
	std::ostream& printMaximumReuse(std::ostream& out, const std::uint32_t* indices, std::size_t num_indices)
	{
		std::vector<std::uint32_t> unique_indices(indices, indices + num_indices);
		std::sort(begin(unique_indices), end(unique_indices));
		unique_indices.erase(std::unique(begin(unique_indices), end(unique_indices)), end(unique_indices));
		auto num_unique_indices = size(unique_indices);

		//auto ref_counter = std::make_unique<std::uint32_t[]>(num_unique_indices);

		//for (auto i = indices; i < indices + num_indices; ++i)
		//	++ref_counter[*i];

		//auto mean = std::accumulate(&ref_counter[0], &ref_counter[0] + num_unique_indices, 0.0f, [N = 0](float mean, auto value) mutable
		//{
		//	return mean + (value - old) * (1.0f / N);
		//});

		//{
		//	i = (i + 1) % N;

		//	auto old = std::get<T>(values[i]);

		//	auto old_mean = mean;
		//	mean += (value - old) * (1.0f / N);
		//	stddev += (value - old) * (value - mean + old - old_mean) * (1.0f / (N - 1));
		//}

		out << "\tnumber of unique indices: " << num_unique_indices << '\n'
		    << "\taverage number of references: " << static_cast<double>(num_indices) / num_unique_indices << '\n'
		    << "\t  minimum shading rate: " << 3.0 * num_unique_indices / num_indices << '\n';
		out << 1.0f - (static_cast<double>(num_unique_indices) / num_indices) << "\n";
		return out;
	}

	double computeDynamicBatchReuse(const std::uint32_t* indices, std::size_t num_indices, unsigned int batch_size, unsigned int max_batch_vertices)
	{
		std::size_t overall_batch_unique_indices = 0;

		std::unordered_set<std::uint32_t> indices_seen;

		std::uint32_t current_batch_indices = 0U;
		std::uint32_t i;
		for (i = 0U; i + 3U <= num_indices; i += 3U, current_batch_indices += 3U)
		{
			bool restart_batch = false;

			// if the current triangle goes beyond the max index size -> finish batch
			if (current_batch_indices + 3 > batch_size)
				restart_batch = true;
			else
			{
				// can we add the triangle while staying within the limit?
				auto to_add = std::accumulate(indices + i, indices + i + 3, 0, [&](auto a, auto id)
				{
					if (indices_seen.find(id) == std::end(indices_seen))
						return a + 1;
					return a;
				});

				if (indices_seen.size() + to_add >= max_batch_vertices)
					restart_batch = true;
			}

			if (restart_batch)
			{
				overall_batch_unique_indices += indices_seen.size();
				current_batch_indices = 0;
				indices_seen.clear();
			}

			indices_seen.insert(indices + i, indices + i + 3);
		}
		overall_batch_unique_indices += indices_seen.size();

		return 3.0 * overall_batch_unique_indices / num_indices;
	}

	double computeStaticBatchReuse(const std::uint32_t* indices, std::size_t num_indices, unsigned int batch_size, unsigned int max_consume_indices, unsigned int max_consume_vertices)
	{
		std::size_t overall_batch_unique_indices = 0;

		std::unordered_set<std::uint32_t> indices_seen;
		for (uint32_t i = 0U; i < num_indices; i += batch_size)
		{
			indices_seen.clear();
			unsigned int consume_indices = 0;
			unsigned int consume_vertices = 0;

			for (uint32_t j = i; j < i + batch_size && j < num_indices; )
			{
				auto to_add = std::accumulate(indices + j, indices + j + 3, 0, [&](auto a, auto id)
				{
					if (indices_seen.find(id) == std::end(indices_seen))
						return a + 1;
					return a;
				});

				if (consume_indices + 3 > max_consume_indices || indices_seen.size() + to_add >= max_consume_vertices)
				{
					overall_batch_unique_indices += indices_seen.size();
					indices_seen.clear();
					consume_indices = 0;
					consume_vertices = 0;
				}
				else
				{
					indices_seen.insert(indices + +j, indices + j + 3);
					consume_indices += 3;
					j += 3;
				}

			}
			overall_batch_unique_indices += indices_seen.size();
		}

		return 3.0 * overall_batch_unique_indices / num_indices;
	}

	std::ostream& printCacheReuse(std::ostream& out, const std::uint32_t* indices, std::size_t num_indices, unsigned int num_processors, unsigned int num_cached, unsigned int parallel_process, unsigned int rounds = 3)
	{
		std::vector<std::unordered_map<std::uint32_t, std::uint32_t>> caches(num_processors);
		std::size_t hits = 0;
		std::size_t misses = 0;
		for (uint32_t i = 0U; i < num_indices; )
		{
			uint32_t mp = (i / parallel_process / rounds) % num_processors;
			auto & cache = caches[mp];

			uint32_t j = i;
			while (j < i + parallel_process*rounds && j < num_indices)
			{
				std::unordered_map<std::uint32_t, std::uint32_t> current;
				for (; j < i + parallel_process && j < num_indices; ++j)
				{
					auto found = cache.find(indices[j]);
					if (found != std::end(cache))
					{
						++hits;
						found->second = j;
					}
					else
					{
						++misses;
						current.insert(std::make_pair(indices[j], j));
					}
				}
				if (cache.size() + current.size() > num_cached)
				{
					std::vector<std::pair<std::uint32_t, std::uint32_t>> entries;
					entries.insert(entries.begin(), cache.begin(), cache.end());
					std::sort(entries.begin(), entries.end());
					std::size_t rem = cache.size() + current.size() - num_cached;
					std::for_each(entries.begin(), entries.begin() + rem, [&](auto& a) {
						cache.erase(a.first);
					});
				}
				cache.insert(current.begin(), current.end());
				i += parallel_process;
			}

		}

		out << "\tcaching with " << num_processors << " processors, cache size " << num_cached << " (elements), and parallel_process " << parallel_process << " with " << rounds << "rounds\n";
		//out << "  vertices: " << num_vertices << " triangels: " << num_indices / 3 << "\n";
		out << "\t  cache reuse: " << std::setprecision(3) << static_cast<double>(hits) / (hits + misses) << " = " << (hits + misses) / static_cast<double>(misses) << "\n";
		out << "\t  hits/misses/overall: " << hits << " " << misses << " " << hits + misses << "\n";
		return out;
	}
}

VertexReuseStats::VertexReuseStats(SceneSink& next, int sim_type, bool output)
	: ProcessingLayer(next), sim_type(sim_type), output(output)
{
}

double VertexReuseStats::compute(VertexReuseSimType type, const std::uint32_t* indices, std::size_t num_indices)
{
	struct B
	{
		std::vector<uint32_t> indices;
	};

	std::vector<B> bs;
	std::uint32_t max_id = 0;

	std::function<void(uint32_t, uint32_t, std::vector<uint32_t>)> f = [&](uint32_t a, uint32_t b, auto vec) 
	{
		bs.push_back(B());
		//for (uint32_t i = a+1; i < b-1; i++)
		{
			bs.back().indices = vec;
		}
	};

	uint32_t invocations = 0;
	switch (type)
	{
	case VRS_NV_DX:
		invocations = simulateInvocations(type, indices, num_indices);
		invocations = simulateBatch<NVDxCacheSim>(96, 32, indices, num_indices, true, 0xFFFFFFFF, f);// [](uint32_t, uint32_t, auto) {});
		break;
	case VRS_NV_GL:
		invocations = simulateBatch<NVGLCacheSim>(96, 32, indices, num_indices, true, 0xFFFFFFFF, [](uint32_t, uint32_t, auto) {});
		break;
	case VRS_ATI:
		invocations = simulateBatch<LRUCacheSim<15>>(384, 64, indices, num_indices, false, 384, f);
		break;
	case VRS_INTEL_EXPERIMENTAL:
		invocations = simulateBatch<FIFOCacheSim<ForeverCacheEntry>>(1791, 128, indices, num_indices, true, 0xFFFFFFFF, [](uint32_t, uint32_t, auto) {});
		break;
	case VRS_STATIC_WARP:
		invocations = simulateBatch<FIFOCacheSim<ForeverCacheEntry>>(96, 32, indices, num_indices, true, 96, [](uint32_t, uint32_t, auto) {});
		break;
	case VRS_DYNAMIC_BLOCK:
		invocations = simulateBatch<FIFOCacheSim<ForeverCacheEntry>>(1023, 256, indices, num_indices, true, 0xFFFFFFFF, [](uint32_t, uint32_t, auto) {});
		break;
	}

	uint32_t nump_verts = 0;
	for (int i = 0; i < bs.size(); i++)
	{
		nump_verts += (uint32_t)(bs[i].indices.size());
	}

	auto file = std::ofstream("out.vsi", std::ios::binary);
	if (!file)
		throw std::runtime_error("unable to open invocation counters file");

	uint32_t num_batch_info_elements = (uint32_t)(4 * bs.size() + nump_verts);

	uint8_t gpu_desc_length = 3;
	uint32_t nump_indices = uint32_t(nump_verts);

	uint64_t clock_ticks = 0;
	uint64_t clock_frequency = 0;
	uint64_t vertex_shader_invoc = 0;
	uint32_t num = 0x80000000 | num_batch_info_elements;

	write(file, gpu_desc_length);
	write(file, "nv");

	uint8_t magic[8];
	write(file, magic);
	write(file, nump_indices);
	write(file, clock_ticks);
	write(file, clock_frequency);
	write(file, vertex_shader_invoc);
	write(file, num);

	{
		int batch = 0;		
		while (num_batch_info_elements)
		{
			B& curr = bs[batch];

			std::uint32_t mask[4] = { 0, 0, 0, 0};

			for (int i = 0; i < curr.indices.size(); i++)
			{	mask[i / 32] |= (1 << (i % 32));	}

			write(file, mask);
			
			for (int i = 0; i < curr.indices.size(); ++i)
			{
				write(file, curr.indices[i]);
			}

			num_batch_info_elements -= (uint32_t)(4 + curr.indices.size());

			batch++;
		}
	}

	return 3.0*static_cast<double>(invocations) / num_indices;
}

namespace {
	void print(double sr, std::size_t num_indices, VertexReuseSimType type)
	{
		std::size_t num = static_cast<std::size_t>(std::round(sr / 3 * num_indices));
		std::cout << "\t" << VertexReuseName(type) << ": " << num << " / " << num_indices << "\n\t  average shading rate: " << sr << "\n";
		std::cout <<  1.0f - (sr / 3.0f) << "\n";
	}
}
void VertexReuseStats::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ vertex reuse statistics ------------------\n";

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type == PrimitiveType::TRIANGLES)
		{
			double shadingrate;
			//uint32_t batchsize = maxIndices;
			//uint32_t max_vertices = maxIndices/3;


			//uint32_t fifolength = fifo ? 42 : maxIndices;

			std::cout << "surface: " << num_vertices << " vertices, " << num_indices / 3 << " triangles\n";
			printMaximumReuse(std::cout, indices + surface->start, surface->num_indices);
			////shadingrate = computeStaticBatchReuse(indices + surface->start, surface->num_indices, batchsize, max_indices, max_vertices);
			//shadingrate = compute(batchsize, max_vertices, fifolength, indices + surface->start, surface->num_indices);
			//std::cout << "\tstatic batching (bs=" << batchsize << ",mcv=" << max_vertices << ",fifo=" << fifolength << "):\n\t  average shading rate: " << shadingrate << "\n";

			if (sim_type == -1)
			{
				for (int i = 0; i <= 5; ++i)
				{
					shadingrate = compute(static_cast<VertexReuseSimType>(i), indices + surface->start, surface->num_indices);
					print(shadingrate, surface->num_indices, static_cast<VertexReuseSimType>(i));
				}
			}
			else
			{ 
				shadingrate = compute(static_cast<VertexReuseSimType>(sim_type), indices + surface->start, surface->num_indices);
				print(shadingrate, surface->num_indices, static_cast<VertexReuseSimType>(sim_type));
			}

			if(output)
			{
				std::ofstream off("simmering.txt", std::ios_base::app);
				off << shadingrate << std::endl;
			}

			//std::cout << "\tdynamic batching (bs=" << batchsize << ",mcv=" << batchsize << ",fifo=" << batchsize << "):\n\t  average shading rate: " << shadingrate << "\n";
			//printCacheReuse(num_vertices, indices, num_indices, 20, 2 * 1024, 1024, 3);
		}
		else
			throw std::runtime_error("vertex reuse stats only support triangles");
	}

	//std::cout << "-------------------------------------------------------------\n";

	ProcessingLayer::process(vertices, num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

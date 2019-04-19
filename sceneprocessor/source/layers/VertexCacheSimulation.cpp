


#include <algorithm>
#include <numeric>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <iomanip>

#include "VertexCacheSimulation.h"


namespace
{
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
		out << ">>>>> "  << static_cast<double>(hits) / (hits + misses) << std::endl;
		out << "caching with " << num_processors << " processors, cache size " << num_cached << " (elements), and parallel_process " << parallel_process << " with " << rounds << " rounds\n";
		//out << "  vertices: " << num_vertices << " triangels: " << num_indices / 3 << "\n";
		out << "  cache reuse: " << std::setprecision(3) << static_cast<double>(hits) / (hits + misses) << " = " << (hits + misses) / static_cast<double>(misses) << "\n";
		out << "  hits/misses/overall: " << hits << " " << misses << " " << hits + misses << "\n";
		return out;
	}
}

VertexCacheSimulation::VertexCacheSimulation(SceneSink& next)
	: ProcessingLayer(next)
{
}

void VertexCacheSimulation::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ vertex cache simulation ------------------\n";

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type == PrimitiveType::TRIANGLES)
		{
			std::cout << "surface: " << num_vertices << " vertices, " << num_indices / 3 << " triangles\n";
			printCacheReuse(std::cout, indices + surface->start, surface->num_indices, 28, 4*1024, 1024, 3);
		}
		else
			throw std::runtime_error("vertex cache simulation only supports triangles");
	}

	//std::cout << "-------------------------------------------------------------\n";

	ProcessingLayer::process(vertices, num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

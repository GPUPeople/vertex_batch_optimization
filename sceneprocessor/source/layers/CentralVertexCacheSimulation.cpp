


#include <algorithm>
#include <numeric>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "CentralVertexCacheSimulation.h"


namespace
{
	std::ostream& printCacheReuse(std::ostream& out, bool output, const std::uint32_t* indices, std::size_t num_indices, std::size_t num_cached)
	{
		std::list<std::uint32_t> cache_list;
		std::unordered_set<std::uint32_t> cache_set;

		std::size_t hits = 0;
		std::size_t misses = 0;

		for (uint32_t i = 0U; i < num_indices; i++ )
		{
			uint32_t id = indices[i];

			auto found = cache_set.find(id);
			if (found != std::end(cache_set))
			{
				++hits;
			}
			else
			{
				++misses;
				cache_set.insert(id);
				cache_list.push_back(id);
			}

			if (cache_set.size() > num_cached)
			{
				uint32_t to_kill = cache_list.front();
				cache_set.erase(to_kill);
				cache_list.pop_front();
			}
		}

		if (output)
		{
			std::ofstream off("garnet.txt", std::ios_base::app);
			off << num_cached << " " << (static_cast<double>(misses) / (hits + misses)) << std::endl;
		}

		out << "caching with cache size " << num_cached << " (elements)\n";
		out << "  cache reuse: " << std::setprecision(3) << static_cast<double>(hits) / (hits + misses) << " = " << (hits + misses) / static_cast<double>(misses) << "\n";
		out << "  ACMR: " << 3 * (static_cast<double>(misses) / (hits + misses)) << std::endl;
		return out;
	}
}

CentralVertexCacheSimulation::CentralVertexCacheSimulation(SceneSink& next, bool output, const std::size_t size)
	: ProcessingLayer(next), size(size), output(output)
{
}

void CentralVertexCacheSimulation::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ central vertex cache simulation ------------------\n";

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type == PrimitiveType::TRIANGLES)
		{
			std::cout << "surface: " << num_vertices << " vertices, " << num_indices / 3 << " triangles\n";
			printCacheReuse(std::cout, output, indices + surface->start, surface->num_indices, size);
		}
		else
			throw std::runtime_error("vertex cache simulation only supports triangles");
	}

	//std::cout << "-------------------------------------------------------------\n";

	ProcessingLayer::process(vertices, num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

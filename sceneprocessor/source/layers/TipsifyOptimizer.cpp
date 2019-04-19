
#include <map>

#include <iostream>

#include "tootlelib.h"
#include "TipsifyOptimizer.h"
#include <list>
#include <set>

#define SHOW_REORDERED_FACES false
#define SHOW_PROGRESS false

TipsifyOptimizer::TipsifyOptimizer(SceneSink& next, int cache_size)
	: ProcessingLayer(next), K(cache_size)
{
}

void TipsifyOptimizer::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ Tipsify optimizer ------------------\n";

	std::vector<uint32_t> new_indices(num_indices);

	TootleResult res;

	res = TootleInit();

	if (res != TOOTLE_OK)
	{
		throw std::exception("Failed to init Tootle");
	}

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type != PrimitiveType::TRIANGLES)
		{
			throw std::exception("Unsupported shape!");
		}

		res = TootleOptimizeVCache(indices + surface->start, surface->num_indices / 3, (unsigned int) num_vertices, K, new_indices.data() + surface->start, nullptr, TOOTLE_VCACHE_TIPSY);

		if (res != TOOTLE_OK)
		{
			throw std::exception("Failed to convert model!");
		}
	}	

	TootleCleanup();

	ProcessingLayer::process(vertices, num_vertices, &new_indices[0], new_indices.size(), surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

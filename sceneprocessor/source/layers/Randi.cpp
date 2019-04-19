


#include <stdexcept>
#include <algorithm>
#include <iostream>

#include "Randi.h"


namespace
{
	template <int PrimitiveSize, typename InputIterator, typename OutputIterator, typename URBG>
	void shuffle_primitives(InputIterator begin, InputIterator end, OutputIterator dest, URBG&& urbg)
	{
		std::vector<InputIterator> primitives;

		for (auto it = begin; it != end; it += PrimitiveSize)
			primitives.push_back(it);

		std::shuffle(std::begin(primitives), std::end(primitives), urbg);

		for (auto p : primitives)
		{
			for (int i = 0; i < PrimitiveSize; ++i)
				*dest++ = *p++;
		}
	}
}

Randi::Randi(SceneSink& next, std::uint_fast64_t seed)
	: ProcessingLayer(next),
	  rnd(seed)
{
}

void Randi::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ mesh randomizer ------------------\n";

	std::vector<std::uint32_t> new_indices(indices, indices + num_indices);


	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type == PrimitiveType::TRIANGLES)
			shuffle_primitives<3>(indices + surface->start, indices + surface->start + surface->num_indices, std::begin(new_indices) + surface->start, rnd);
		else
			throw std::runtime_error("randi only supports triangles");
	}

	ProcessingLayer::process(vertices, num_vertices, &new_indices[0], new_indices.size(), surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

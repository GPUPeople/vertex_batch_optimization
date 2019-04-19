


#include <algorithm>
#include <iostream>

#include <core/utils/memory>

#include "ZFlip.h"


namespace
{
	vertex flip(vertex v)
	{
		v.p.z *= -1.0f;
		return v;
	}

	template <typename InputIterator, typename OutputIterator>
	void flip(OutputIterator dest, InputIterator begin, InputIterator end)
	{
		for (auto it = begin; it != end; ++it)
			*dest++ = flip(*it);
	}
}

ZFlip::ZFlip(SceneSink& next)
	: ProcessingLayer(next)
{
}

void ZFlip::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ z flip ------------------\n";

	auto flipped_vertices = core::make_unique_default<vertex[]>(num_vertices);

	flip(&flipped_vertices[0], vertices, vertices + num_vertices);

	//ProcessingLayer::process(vertices, num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
	ProcessingLayer::process(&flipped_vertices[0], num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

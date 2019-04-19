


#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>

#include <core/utils/memory>

#include "UnweldVertices.h"


UnweldVertices::UnweldVertices(SceneSink& next)
	: ProcessingLayer(next)
{
}


void UnweldVertices::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ unweld vertices ------------------\n";

	auto new_indices = core::make_unique_default<std::uint32_t[]>(num_indices);
	auto new_vertices = core::make_unique_default<vertex[]>(num_indices);

	for (int i = 0; i < num_indices; i++)
	{
		auto v = vertices[indices[i]];
		new_vertices[i] = v;
		new_indices[i] = i;
	}

	ProcessingLayer::process(new_vertices.get(), num_indices, new_indices.get(), num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

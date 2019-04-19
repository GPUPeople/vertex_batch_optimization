


#include <algorithm>
#include <iostream>

#include <core/utils/memory>

#include "WindingOrderFlip.h"


namespace
{
	template <int N, typename InputIterator, typename OutputIterator>
	void flip(OutputIterator dest, InputIterator begin, InputIterator end)
	{
		for (auto it = begin; it != end;)
		{

		}
	}
}

WindingOrderFlip::WindingOrderFlip(SceneSink& next)
	: ProcessingLayer(next)
{
}

void WindingOrderFlip::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ winding order flip ------------------\n";

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		if (surface->primitive_type == PrimitiveType::QUADS)
			;
		else
			;
	}

	ProcessingLayer::process(vertices, num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

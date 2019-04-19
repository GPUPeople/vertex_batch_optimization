


#include <algorithm>
#include <iostream>
#include <chrono>

#include <core/utils/memory>

#include "Timing.h"



Timing::Timing(SceneSink & next, stack_t& timings)
	: ProcessingLayer(next)
	, timings(timings)
{
}

void Timing::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ record time ------------------\n";
	auto now = std::chrono::steady_clock::now();
	if (!timings.empty())
	{
		std::cout << "difference to the last recorded time: "
		          << std::chrono::duration_cast<std::chrono::microseconds>(now - timings.top()).count()
		          << "us.\n";
	}
	timings.push(now);

	ProcessingLayer::process(vertices, num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}

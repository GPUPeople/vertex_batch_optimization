


#ifndef INCLUDED_TIMING
#define INCLUDED_TIMING

#pragma once

#include <stack>
#include <chrono>

#include "../ProcessingLayer.h"


class Timing : public virtual ProcessingLayer
{
	using clock_t = std::chrono::steady_clock;
	using time_t = std::chrono::time_point<clock_t>;
	using stack_t = std::stack<time_t, std::deque<time_t>>;
	stack_t& timings;

public:
	Timing(SceneSink& next, stack_t& timings);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_TIMING

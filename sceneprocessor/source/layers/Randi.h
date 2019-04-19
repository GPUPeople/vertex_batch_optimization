


#ifndef INCLUDED_RANDI
#define INCLUDED_RANDI

#pragma once

#include <random>

#include "../ProcessingLayer.h"


class Randi : public virtual ProcessingLayer
{
	std::mt19937_64 rnd;

public:
	Randi(SceneSink& next, std::uint_fast64_t seed = 42);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_RANDI

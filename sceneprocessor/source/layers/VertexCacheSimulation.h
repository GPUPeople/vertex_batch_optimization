


#ifndef INCLUDED_VERTEX_CACHE_SIMULATION
#define INCLUDED_VERTEX_CACHE_SIMULATION

#pragma once

#include "../ProcessingLayer.h"


class VertexCacheSimulation : public virtual ProcessingLayer
{
public:
	VertexCacheSimulation(SceneSink& next);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_VERTEX_CACHE_SIMULATION

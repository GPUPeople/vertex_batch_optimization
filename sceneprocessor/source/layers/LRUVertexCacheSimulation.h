


#ifndef INCLUDED_LRU_VERTEX_CACHE_SIMULATION
#define INCLUDED_LRU_VERTEX_CACHE_SIMULATION

#pragma once

#include "../ProcessingLayer.h"


class LRUVertexCacheSimulation : public virtual ProcessingLayer
{
private: 
	std::size_t size;
	bool output;
public:
	LRUVertexCacheSimulation(SceneSink& next, bool output, const std::size_t size);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_VERTEX_CACHE_SIMULATION

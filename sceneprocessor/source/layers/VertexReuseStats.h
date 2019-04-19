


#ifndef INCLUDED_VERTEX_REUSE_STATS
#define INCLUDED_VERTEX_REUSE_STATS

#pragma once

#include "../ProcessingLayer.h"
#include "BatchSimulationParameters.h"


class VertexReuseStats : public virtual ProcessingLayer
{
private:

	bool output;

	int sim_type;

public:
	VertexReuseStats(SceneSink& next, int type = -1, bool output = false); //VertexReuseSimType .. -1 = all

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;

	static double compute(VertexReuseSimType type, const std::uint32_t* indices, std::size_t num_indices);
};

#endif  // INCLUDED_VERTEX_REUSE_STATS

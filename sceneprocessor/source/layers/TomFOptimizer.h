


#ifndef INCLUDED_TOM_FORSYTH_OPTIMIZER
#define INCLUDED_TOM_FORSYTH_OPTIMIZER

#pragma once

#include "../ProcessingLayer.h"


class TomFOptimizer : public virtual ProcessingLayer
{
public:
	TomFOptimizer(SceneSink& next);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;

	static void optimize(std::uint32_t* newIndexList, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, uint32_t lruCacheSize);
};

#endif  // INCLUDED_TOM_FORSYTH_OPTIMIZER

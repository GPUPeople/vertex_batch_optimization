
#ifndef INCLUDED_TIPSIFY_OPTIMIZER
#define INCLUDED_TIPSIFY_OPTIMIZER

#pragma once

#include <queue>
#include <set>
#include <vector>
#include <list>
#include "../ProcessingLayer.h"


class TipsifyOptimizer : public virtual ProcessingLayer
{
private:

	unsigned int K;

public:
	
	TipsifyOptimizer(SceneSink& next, int cache_size);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_HOPPE_OPTIMIZER

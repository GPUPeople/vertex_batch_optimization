


#ifndef INCLUDED_GBATCH_OPTIMIZER
#define INCLUDED_GBATCH_OPTIMIZER

#pragma once

#include "../ProcessingLayer.h"

#include "BatchSimulationParameters.h"


class GBatchOptimizer : public virtual ProcessingLayer
{
	const std::int32_t
		cacheWeight,
		valenceWeight,
		distanceWeight,
		batchNeighborWeight,
		finPointMultiplier;
	const VertexReuseSimType sim_type;
	bool remapVertices;
public:
	//opt: 64, -16, -1, -16, -1
	//default: 1024, -4, 3. -4. -4

	GBatchOptimizer(SceneSink& next, VertexReuseSimType SimType, std::int32_t CacheWeight = 64, std::int32_t ValenceWeight = -16, std::int32_t DistanceWeight = -1, std::int32_t BatchNeighborWeight = -16, const std::int32_t FinPointMultiplier = -1, bool RemapVertices = true);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_BATCH_OPTIMIZER

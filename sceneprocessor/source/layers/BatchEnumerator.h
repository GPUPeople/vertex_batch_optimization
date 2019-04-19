


#ifndef INCLUDED_BATCH_ENUMERATOR
#define INCLUDED_BATCH_ENUMERATOR

#pragma once

#include "../ProcessingLayer.h"


class BatchEnumerator : public virtual ProcessingLayer
{
	int maxIndices, maxVertices;
public:
	BatchEnumerator(SceneSink& next, int BatchMaxInidices = 96, int BatchMaxVertices = -1);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_BATCH_ENUMERATOR

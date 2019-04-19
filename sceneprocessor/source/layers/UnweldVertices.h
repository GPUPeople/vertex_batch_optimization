


#ifndef INCLUDED_UNWELD_VERTICES
#define INCLUDED_UNWELD_VERTICES

#pragma once

#include "../ProcessingLayer.h"


class UnweldVertices : public virtual ProcessingLayer
{
public:
	UnweldVertices(SceneSink& next);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_UNWELD_VERTICES

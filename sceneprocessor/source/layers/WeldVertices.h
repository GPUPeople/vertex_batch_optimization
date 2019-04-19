


#ifndef INCLUDED_WELD_VERTICES
#define INCLUDED_WELD_VERTICES

#pragma once

#include "../ProcessingLayer.h"


class WeldVertices : public virtual ProcessingLayer
{
public:
	WeldVertices(SceneSink& next);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_WELD_VERTICES

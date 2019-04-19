


#ifndef INCLUDED_PROCESSING_LAYER
#define INCLUDED_PROCESSING_LAYER

#pragma once

#include "SceneBuilder.h"


struct SceneSink
{
	virtual void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) = 0;

protected:
	SceneSink() = default;
	SceneSink(const SceneSink&) = default;
	~SceneSink() = default;
	SceneSink& operator =(const SceneSink&) = default;
};

class ProcessingLayer : public virtual SceneSink
{
	SceneSink& next;

public:
	ProcessingLayer(SceneSink& next)
		: next(next)
	{
	}

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override
	{
		next.process(vertices, num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
	}
};

#endif  // INCLUDED_PROCESSING_LAYER

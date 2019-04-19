


#ifndef INCLUDED_BATCH_SILHOUETTE
#define INCLUDED_BATCH_SILHOUETTE

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include <GL/gl.h>
#include <GL/shader.h>
#include <GL/buffer.h>
#include <GL/vertex_array.h>

#include "Geometry.h"


class BatchSilhouette
{
	GL::Program prog;

	GL::VertexArray vao;

	GL::Buffer vertex_buffer;

	GLsizei num_vertices;

	static constexpr int BATCH_SIZE = 32;

public:
	BatchSilhouette(const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices);

	void draw() const;
};

#endif  // INCLUDED_BATCH_SILHOUETTE

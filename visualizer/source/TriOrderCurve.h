


#ifndef INCLUDED_TRI_ORDER_CURVE
#define INCLUDED_TRI_ORDER_CURVE

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include <GL/gl.h>
#include <GL/shader.h>
#include <GL/buffer.h>
#include <GL/vertex_array.h>

#include "Geometry.h"


class TriOrderCurve
{
	GL::Program prog;

	GL::VertexArray vao;

	GL::Buffer vertex_buffer;

	GLsizei num_vertices;

public:
	TriOrderCurve(const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices);

	void draw() const;
};

#endif  // INCLUDED_TRI_ORDER_CURVE

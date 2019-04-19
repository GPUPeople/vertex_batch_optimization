


#ifndef INCLUDED_INVOCATION_CHECKER
#define INCLUDED_INVOCATION_CHECKER

#pragma once


#include <cstddef>
#include <cstdint>
#include <vector>

#include <GL/gl.h>
#include <GL/shader.h>
#include <GL/buffer.h>
#include <GL/texture.h>
#include <GL/vertex_array.h>

#include "Geometry.h"
#include "Camera.h"
#include "Display.h"


class InvocationChecker
{
	Display& display;
	GL::Program prog_invo;

	GL::VertexArray vao;
	
	GL::Buffer vertex_buffer;
	GL::Buffer vertex_invocation_counter_buffer;
	GL::Buffer vertex_invocation_timing_buffer;
	//uint32_t maxvalence;
	GL::Buffer index_buffer;

	GL::Buffer color_buffer;
	GL::Texture color_buffer_texture;

	GLsizei num_vertices;
	GLsizei num_indices;
	std::vector<std::uint32_t> indices;

	void runCheck() const;
public:
	InvocationChecker(Display& display, const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices);

	void draw(GLuint camera_uniform_buffer, GLsizei num_indices) const;
};

#endif  // INCLUDED_INVOCATION_CHECKER




#include <memory>
#include <random>
#include <algorithm>
#include <iostream>

#include <core/utils/memory>
#include <core/utils/io>

#include <GL/error.h>

#include "GeometryViz.h"


extern const char geometry_vs[];
extern const char geometry_show_invocations_vs[];
extern const char geometry_fs[];
extern const char geometry_vertex_color_fs[];
extern const char geometry_show_order_fs[];
extern const char geometry_show_batches_fs[];
extern const char color_fs[];


namespace
{
	auto generateBatchColors(int num_primitives)
	{
		auto color_buffer = core::make_unique_default<std::uint32_t[]>(num_primitives);

		std::generate(&color_buffer[0], &color_buffer[0] + num_primitives, [i = 0, color = 0U, rnd = std::mt19937(42), dist = std::uniform_int_distribution<unsigned int>(0, 0xFFFFFF)]() mutable
		{
			if (i++ % 32 == 0)
				color = dist(rnd); 
			return 0xFF000000U | color;
		});

		return color_buffer;
	}

	auto generateNewBatchColors(const std::uint32_t* batch_id, std::vector<float>& avg_indices, int num_primitives)
	{
		auto colors = core::make_unique_default<std::uint32_t[]>(num_primitives);
		auto color_buffer = core::make_unique_default<std::uint32_t[]>(num_primitives);

		std::generate(&colors[0], &colors[0] + num_primitives, [i = 0, color = 0U, rnd = std::mt19937(42)]() mutable
		{
			color = rnd();
			return 0xFF000000U | color;
		});

		union data
		{
			float f;
			std::uint32_t i;
		};

		for (int i = 0; i < num_primitives; ++i)
		{
			//color_buffer[i] = colors[batch_id[i]];
			data d;
			d.f = avg_indices[batch_id[i]];
			color_buffer[i] = d.i;
		}

		return color_buffer;
	}
}

GeometryViz::GeometryViz(const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* _indices, std::size_t num_indices)
	: num_vertices(static_cast<GLsizei>(num_vertices)),
	  num_indices(static_cast<GLsizei>(num_indices)),
	  indices(_indices, _indices + num_indices),
	  tri_order_curve(vertices, num_vertices, _indices, num_indices),
	  patch_silhouette(vertices, num_vertices, _indices, num_indices),
	  show_batch_primitive_id(-1)
{
	if (GLint64 max_texture_buffer_size; glGetInteger64v(GL_MAX_TEXTURE_BUFFER_SIZE, &max_texture_buffer_size), max_texture_buffer_size < static_cast<GLint64>(num_vertices))
		std::cerr << "WARNING: GL_MAX_TEXTURE_BUFFER_SIZE less than num_vertices\n";

	{
		auto vs = GL::compileVertexShader(geometry_vs);
		auto vs_show_invocations = GL::compileVertexShader(geometry_show_invocations_vs);

		auto fs_normal = GL::compileFragmentShader(geometry_fs);
		auto fs_vertex_color = GL::compileFragmentShader(geometry_vertex_color_fs);
		auto fs_show_order = GL::compileFragmentShader(geometry_show_order_fs);
		auto fs_show_batches = GL::compileFragmentShader(geometry_show_batches_fs);
		auto fs_color = GL::compileFragmentShader(color_fs);

		glAttachShader(prog_normal, vs);
		glAttachShader(prog_normal, fs_normal);
		GL::linkProgram(prog_normal);

		glAttachShader(prog_show_invocations, vs_show_invocations);
		glAttachShader(prog_show_invocations, fs_vertex_color);
		GL::linkProgram(prog_show_invocations);

		glAttachShader(prog_show_order, vs);
		glAttachShader(prog_show_order, fs_show_order);
		GL::linkProgram(prog_show_order);

		glAttachShader(prog_show_batches, vs);
		glAttachShader(prog_show_batches, fs_show_batches);
		GL::linkProgram(prog_show_batches);

		glAttachShader(prog_wire, vs);
		glAttachShader(prog_wire, fs_color);
		GL::linkProgram(prog_wire);


		glProgramUniform4f(prog_wire, 0, 0.02f, 0.02f, 0.02f, 1.0f);
		glProgramUniform1f(prog_show_order, 0, 3.0f / num_indices);
		glProgramUniform1i(prog_show_batches, 1, 1);
	}


	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferStorage(GL_ARRAY_BUFFER, static_cast<GLsizei>(num_vertices * sizeof(GeometryVertex)), vertices, 0U);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_invocation_counter_buffer);
	glBufferStorage(GL_ARRAY_BUFFER, num_vertices * 4U, nullptr, GL_DYNAMIC_STORAGE_BIT);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(num_indices * 4U), _indices, 0U);

	glBindVertexArray(vao);
	glBindVertexBuffer(0U, vertex_buffer, 0U, sizeof(GeometryVertex));
	glBindVertexBuffer(1U, vertex_invocation_counter_buffer, 0U, 4U);
	glEnableVertexAttribArray(0U);
	glEnableVertexAttribArray(1U);
	glEnableVertexAttribArray(3U);
	glVertexAttribFormat(0U, 3, GL_FLOAT, GL_FALSE, 0U);
	glVertexAttribFormat(1U, 3, GL_FLOAT, GL_FALSE, 12U);
	glVertexAttribIFormat(3U, 1, GL_UNSIGNED_INT, 0U);
	glVertexAttribBinding(0U, 0U);
	glVertexAttribBinding(1U, 0U);
	glVertexAttribBinding(3U, 1U);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

	{
		int num_primitives = static_cast<int>(num_indices / 3);
		auto batch_colors = generateBatchColors(num_primitives);

		glBindBuffer(GL_TEXTURE_BUFFER, prediction_batch_color_buffer);
		glBufferStorage(GL_TEXTURE_BUFFER, num_primitives * 4U, nullptr, GL_DYNAMIC_STORAGE_BIT);

		glBindTexture(GL_TEXTURE_BUFFER, prediction_batch_color_buffer_texture);
		glTextureBuffer(prediction_batch_color_buffer_texture, GL_RGBA8, prediction_batch_color_buffer);


		glBindBuffer(GL_TEXTURE_BUFFER, tool_batch_color_buffer);
		glBufferStorage(GL_TEXTURE_BUFFER, num_primitives * 4U, nullptr, GL_DYNAMIC_STORAGE_BIT);

		glBindTexture(GL_TEXTURE_BUFFER, tool_batch_color_buffer_texture);
		glTextureBuffer(tool_batch_color_buffer_texture, GL_RGBA8, tool_batch_color_buffer);
	}

	GL::throw_error();
}

void GeometryViz::loadVertexInvocationCounters(const std::uint32_t* inv_counters, std::size_t num_counters)
{
	GL::throw_error();
	if (num_vertices != num_counters)
		throw std::runtime_error("number of vertices in the model != number of vertex reuse counters");
	glNamedBufferSubData(vertex_invocation_counter_buffer, 0, 4U * num_vertices, inv_counters);

	GL::throw_error();
}

void GeometryViz::loadBatchIfno(std::set<uint32_t>* vertex_info, std::vector<float>& avg_indices, std::size_t num_vertices, bool load_tool)
{
	return;
	auto num_primitives = num_indices / 3;
	auto batch_id = std::make_unique<std::uint32_t[]>(num_primitives);
	for (int i = 0; i < num_primitives; ++i)
	{
		auto id0 = indices[i * 3];
		auto id1 = indices[i * 3 + 1];
		auto id2 = indices[i * 3 + 2];
		auto batches0 = vertex_info[id0];
		auto batches1 = vertex_info[id1];
		auto batches2 = vertex_info[id2];
		std::vector<std::uint32_t> common01;
		std::set_intersection(begin(batches0), end(batches0), begin(batches1), end(batches1), std::back_inserter(common01));
		std::vector<std::uint32_t> common;
		std::set_intersection(begin(common01), end(common01), begin(batches2), end(batches2), std::back_inserter(common));
		batch_id[i] = common[0];
	}
	auto new_batch_colors = generateNewBatchColors(batch_id.get(), avg_indices, num_primitives);

	if (load_tool)
	{
		glBindBuffer(GL_TEXTURE_BUFFER, tool_batch_color_buffer);
		glNamedBufferSubData(tool_batch_color_buffer, 0, 4U * num_primitives, &new_batch_colors[0]);
	}
	else
	{
		glBindBuffer(GL_TEXTURE_BUFFER, prediction_batch_color_buffer);
		glNamedBufferSubData(prediction_batch_color_buffer, 0, 4U * num_primitives, &new_batch_colors[0]);
	}
}

void GeometryViz::focusBatch(int batch)
{
	show_batch_primitive_id = batch;
}

void GeometryViz::draw(GLuint camera_uniform_buffer) const
{
	glBindBufferBase(GL_UNIFORM_BUFFER, 0U, camera_uniform_buffer);

	glEnable(GL_DEPTH_TEST);

	glPolygonOffset(1.0f, 1.0f);
	glEnable(GL_POLYGON_OFFSET_FILL);

	glBindVertexArray(vao);

	switch (render_mode)
	{
	case 1:
		glUseProgram(prog_show_invocations);
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
		break;

	//case 2:
	//	glUseProgram(prog_show_order);
	//	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
	//	break;

	case 2:
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, prediction_batch_color_buffer_texture);
		glUseProgram(prog_show_batches);
		if(show_batch_primitive_id == -1)
			glUniform2i(2, -1, -1);
		else
			glUniform2i(2, show_batch_primitive_id*32, (show_batch_primitive_id+1)*32);
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
		break;

	case 3:
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, tool_batch_color_buffer_texture);
		glUseProgram(prog_show_batches);
		if (show_batch_primitive_id == -1)
			glUniform2i(2, -1, -1);
		else
			glUniform2i(2, show_batch_primitive_id * 32, (show_batch_primitive_id + 1) * 32);
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
		break;

	default:
		glUseProgram(prog_normal);
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
		break;
	}

	glDisable(GL_POLYGON_OFFSET_FILL);

	if (show_wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUseProgram(prog_wire);
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (show_tri_order_curve)
		tri_order_curve.draw();

	if (show_patch_silhouette)
		patch_silhouette.draw();

	GL::throw_error();
}

std::string GeometryViz::cycleRenderMode()
{
	render_mode = (render_mode + 1) % 4;
	std::string s = "";
	switch (render_mode)
	{
	case 1:
		s = s + " invocations heatmap";
		break;
	//case 2:
	//	s = s + " show order (?)";
	//	break;
	case 2:
		s = s + " batches from prediction";
		break;
	case 3:
		s = s + " batches from new tool";
		break;
	}
	return s;
}

bool GeometryViz::toggleWireframe()
{
	return show_wireframe = !show_wireframe;
}

bool GeometryViz::toggleTriOrderCurve()
{
	return show_tri_order_curve = !show_tri_order_curve;
}

bool GeometryViz::togglePatchSilhouette()
{
	return show_patch_silhouette = !show_patch_silhouette;
}

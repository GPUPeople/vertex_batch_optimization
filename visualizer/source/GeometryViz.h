


#ifndef INCLUDED_GEOMETRY_VIZ
#define INCLUDED_GEOMETRY_VIZ

#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <set>

#include <GL/gl.h>
#include <GL/shader.h>
#include <GL/buffer.h>
#include <GL/texture.h>
#include <GL/vertex_array.h>

#include "Geometry.h"
#include "Camera.h"
#include "TriOrderCurve.h"
#include "BatchSilhouette.h"


class GeometryViz
{
	GL::Program prog_normal;
	GL::Program prog_show_invocations;
	GL::Program prog_show_order;
	GL::Program prog_show_batches;

	GL::Program prog_wire;

	unsigned int render_mode = 1;
	bool show_wireframe = false;
	bool show_tri_order_curve = false;
	bool show_patch_silhouette = false;

	GL::VertexArray vao;

	GL::Buffer vertex_buffer;
	GL::Buffer vertex_invocation_counter_buffer;
	GL::Buffer index_buffer;

	GL::Buffer prediction_batch_color_buffer;
	GL::Texture prediction_batch_color_buffer_texture;
	
	GL::Buffer tool_batch_color_buffer;
	GL::Texture tool_batch_color_buffer_texture;

	GLsizei num_vertices;
	GLsizei num_indices;
	std::vector<std::uint32_t> indices;

	TriOrderCurve tri_order_curve;
	BatchSilhouette patch_silhouette;

	GLint show_batch_primitive_id;

public:
	GeometryViz(const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices);

	void loadVertexInvocationCounters(const std::uint32_t* inv_counters, std::size_t num_counters);
	void loadBatchIfno(std::set<uint32_t>* batch_id, std::vector<float>& avg_indices, std::size_t num_vertices, bool load_tool);
	void focusBatch(int batch);

	std::string cycleRenderMode();
	bool toggleWireframe();
	bool toggleTriOrderCurve();
	bool togglePatchSilhouette();

	void draw(GLuint camera_uniform_buffer) const;
};

#endif  // INCLUDED_GEOMETRY_VIZ

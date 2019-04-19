


#include <algorithm>
#include <vector>

#include <core/utils/memory>
#include <core/utils/io>

#include <GL/error.h>

#include "TriOrderCurve.h"


extern const char geometry_vs[];
extern const char color_fs[];


namespace
{
	math::float3 centroid(const GeometryVertex* vertices, int i1, int i2, int i3)
	{
		return (vertices[i1].p + vertices[i2].p + vertices[i3].p) * (1.0f / 3.0f);
	}

	math::float3 midpoint(const GeometryVertex* vertices, int i1, int i2)
	{
		return (vertices[i1].p + vertices[i2].p) * 0.5f;
	}

	auto generateTriSequence(const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices)
	{
		std::vector<math::float3> line;

		auto c = centroid(vertices, indices[0], indices[1], indices[2]);

		for (auto ind = indices + 3; ind < indices + num_indices; ind += 3)
		{
			auto s = math::float3 { 0.0f, 0.0f, 0.0f };

			int shared = 0;
			for (int i = 0; i < 3; ++i)
			{
				auto v = std::find(ind - 2, ind, ind[i]);
				if (v != ind)
				{
					++shared;
					s = (1.0f / shared) * vertices[*v].p + ((shared - 1.0f) / shared) * s;
				}
			}

			auto c_n = centroid(vertices, ind[0], ind[1], ind[2]);

			if (shared)
			{
				line.push_back(c);
				line.push_back(s);
				line.push_back(s);
				line.push_back(c_n);
			}

			c = c_n;
		}

		return line;
	}
}

TriOrderCurve::TriOrderCurve(const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices)
{
	{
		auto vs = GL::compileVertexShader(geometry_vs);
		auto fs_color = GL::compileFragmentShader(color_fs);

		glAttachShader(prog, vs);
		glAttachShader(prog, fs_color);
		GL::linkProgram(prog);

		glProgramUniform4f(prog, 0, 0.0f, 0.0f, 1.0f, 1.0f);
	}

	glBindVertexArray(vao);
	{
		auto line = generateTriSequence(vertices, num_vertices, indices, num_indices);
		this->num_vertices = static_cast<GLsizei>(size(line));

		if(this->num_vertices > 0)
		{ 
			glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
			glBufferStorage(GL_ARRAY_BUFFER, static_cast<GLsizei>(this->num_vertices * 12U), &line[0], 0U);

			glBindVertexBuffer(0U, vertex_buffer, 0U, 12U);
			glEnableVertexAttribArray(0U);
			glVertexAttribFormat(0U, 3, GL_FLOAT, GL_FALSE, 0U);
			glVertexAttribBinding(0U, 0U);
		}
	}

	GL::throw_error();
}

void TriOrderCurve::draw() const
{
	glBindVertexArray(vao);
	glUseProgram(prog);
	glDrawArrays(GL_LINES, 0, num_vertices);

	GL::throw_error();
}

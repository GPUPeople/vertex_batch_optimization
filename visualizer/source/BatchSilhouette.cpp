


#include <tuple>
#include <algorithm>
#include <vector>

#include <core/utils/memory>
#include <core/utils/io>

#include <GL/error.h>

#include "BatchSilhouette.h"


extern const char geometry_vs[];
extern const char color_fs[];


namespace
{
	template<typename T>
	inline auto makeEdge(T a, T b)
	{
		if (a > b)
			return std::make_tuple(b, a);
		return std::make_tuple(a, b);
	}

	template <typename OutputIterator, typename InputIterator>
	inline OutputIterator generateEdges(OutputIterator dest, InputIterator begin, InputIterator end)
	{
		if (begin == end)
			return dest;

		for (auto i_0 = begin, i_1 = begin + 1, i_2 = begin + 2; i_2 < end; i_0 += 3, i_1 += 3, i_2 += 3)
		{
			*dest++ = makeEdge(*i_0, *i_1);
			*dest++ = makeEdge(*i_1, *i_2);
			*dest++ = makeEdge(*i_2, *i_0);
		}

		return dest;
	}

	template<int BATCH_SIZE>
	auto generateSilhouettes(const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices)
	{
		std::vector<math::float3> line;

		for (auto batch = indices; batch < indices + num_indices; batch += BATCH_SIZE * 3)
		{
			std::tuple<std::uint32_t, std::uint32_t> edges[BATCH_SIZE * 3];

			auto edges_end = generateEdges(edges, batch, std::min(batch + BATCH_SIZE * 3, indices + num_indices));

			std::sort(edges, edges_end);

			int k = 1;
			for (int i = 1; i < BATCH_SIZE * 3; ++i)
			{
				if (edges[i] == edges[i - 1])
					k++;
				else
				{
					if (k == 1)
					{
						auto edge = edges[i - 1];
						auto start_point_id = std::get<0>(edge);
						auto end_point_id = std::get<1>(edge);
						line.push_back(vertices[start_point_id].p);
						line.push_back(vertices[end_point_id].p);
					}
					k = 1;
				}
			}
			if (k == 1)
			{
				auto edge = edges[BATCH_SIZE * 3 - 1];
				auto start_point_id = std::get<0>(edge);
				auto end_point_id = std::get<1>(edge);
				line.push_back(vertices[start_point_id].p);
				line.push_back(vertices[end_point_id].p);
			}
		}
		return line;
	}
}

BatchSilhouette::BatchSilhouette(const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices)
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
		auto line = generateSilhouettes<BATCH_SIZE>(vertices, num_vertices, indices, num_indices);
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

void BatchSilhouette::draw() const
{
	glBindVertexArray(vao);
	glUseProgram(prog);
	glDrawArrays(GL_LINES, 0, num_vertices);

	GL::throw_error();
}

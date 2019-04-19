


#include <cassert>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <numeric>
#include <iostream>

#include <core/utils/memory>
#include <core/utils/io>

#include "../io.h"

#include "candy_scene.h"


namespace candyscene
{
	//struct Vertex
	//{
	//	float4 position;
	//	float3 normal;
	//	float3 color;
	//	float occlusion;

	//	Vertex() = default;

	//	Vertex(const float4& position, const float3& normal, const float3& color, float occlusion)
	//		: position(position), normal(normal), color(color), occlusion(occlusion)
	//	{
	//	}
	//};

	//inline bool operator ==(const Vertex& a, const Vertex& b)
	//{
	//	return a.position.x == b.position.x &&
	//		    a.position.y == b.position.y &&
	//		    a.position.z == b.position.z &&
	//		    a.position.w == b.position.w;
	//}

	//inline std::ostream& operator <<(std::ostream& out, const Vertex& v)
	//{
	//	return out << v.position.x << ", " << v.position.y << ", " << v.position.z << ", " << v.position.w;
	//}

	void read(SceneBuilder& builder, const char* begin, std::size_t length)
	{
		memory_istreambuf b(begin, length);
		std::istream file(&b);

		auto res_x = ::read<std::uint32_t>(file);
		auto res_y = ::read<std::uint32_t>(file);

		auto num_vertices = ::read<std::uint32_t>(file);
		{
			std::vector<vertex> vertices;
			vertices.reserve(num_vertices);

			for (std::uint32_t i = 0; i < num_vertices; ++i)
			{
				auto p = ::read<float4>(file);
				auto n = ::read<float3>(file);
				auto c = ::read<float3>(file);
				auto o = ::read<float>(file);

				vertices.push_back(vertex { { p.x, p.y, p.w }, n, {} });
			}

			builder.addVertices(std::move(vertices));
		}

		auto num_meshes = ::read<std::uint32_t>(file);
		{
			//file.seekg(num_meshes * sizeof(float3), std::ios::cur);
			{
				auto colors = core::make_unique_default<float3[]>(num_meshes);
				::read(&colors[0], file, num_meshes);
			}

			{
				auto ranges = core::make_unique_default<std::uint32_t[]>(num_meshes * 2);
				::read(&ranges[0], file, 2 * num_meshes);
			}

			//for (std::uint32_t i = 0; i < num_meshes; ++i)
			//{
			//	auto begin = ::read<std::uint32_t>(file);
			//	auto end = ::read<std::uint32_t>(file);

			//	std::vector<std::uint32_t> indices(end - begin);
			//	assert(end > begin);
			//	//std::iota(std::begin(indices), std::end(indices), begin);

			//	builder.addSurface(PrimitiveType::TRIANGLES, std::move(indices), nullptr, 0U, nullptr);
			//}
		}

		auto num_triangles = ::read<std::uint32_t>(file);
		{
			//auto indices = make_unique_default<std::uint32_t[]>(num_triangles * 3);
			std::vector<std::uint32_t> indices(num_triangles * 3);
			::read(&indices[0], file, num_triangles * 3);
			builder.addSurface(PrimitiveType::TRIANGLES, std::move(indices), nullptr, 0U, nullptr);
		}
	}

	void write(std::ostream& file, const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
	{
		throw std::runtime_error("candy making not implemented atm");
	}
}

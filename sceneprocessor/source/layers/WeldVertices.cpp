


#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>
#include <unordered_map>

#include <core/utils/memory>

#include "WeldVertices.h"


WeldVertices::WeldVertices(SceneSink& next)
	: ProcessingLayer(next)
{
}


void WeldVertices::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	struct vertex_hash
	{
		std::size_t operator()(const vertex& v) const noexcept
		{
			auto h = std::hash<float>{}(v.p.x);
			h = (h << 2) ^ std::hash<float>{}(v.p.y);
			h = (h << 2) ^ std::hash<float>{}(v.p.z);

			h = (h << 2) ^ std::hash<float>{}(v.n.x);
			h = (h << 2) ^ std::hash<float>{}(v.n.y);
			h = (h << 2) ^ std::hash<float>{}(v.n.z);

			h = (h << 2) ^ std::hash<float>{}(v.t.x);
			h = (h << 2) ^ std::hash<float>{}(v.t.y);
			return h;
		}
	};

	std::cout << "------------------ weld vertices ------------------\n";

	auto new_indices = core::make_unique_default<std::uint32_t[]>(num_indices);
	std::unordered_map<vertex, std::size_t, vertex_hash> vertex_map;

	int write_i = 0;
	for (int i = 0; i < num_indices; i++, write_i++)
	{
		auto v = vertices[indices[i]];
		auto it = vertex_map.find(v);
		if (it == vertex_map.end())
		{
			auto ind = vertex_map.size();
			vertex_map.insert({ v, ind });
			new_indices[write_i] = static_cast<std::uint32_t>(ind);
		}
		else
		{
			new_indices[write_i] = static_cast<std::uint32_t>(it->second);
		}

		if (i && i % 3 == 2 && new_indices[write_i] == new_indices[write_i - 1]) //degenerate
		{	write_i -= 3;	}
	}

	auto new_indices2 = core::make_unique_default<std::uint32_t[]>(write_i);
	memcpy((char*)new_indices2.get(), (char*)new_indices.get(), sizeof(uint32_t) * write_i);

	auto new_vertices = core::make_unique_default<vertex[]>(vertex_map.size());
	for (const auto& v : vertex_map)
	{
		new_vertices[v.second] = v.first;
	}

	std::vector<surface> new_surfaces(1);
	new_surfaces[0] = surfaces[0];
	new_surfaces[0].num_indices = write_i;

	//auto vertex_map = core::make_unique_default<int[]>(num_vertices);
	//std::iota(&vertex_map[0], &vertex_map[0] + num_vertices, 0);

	//std::sort(&vertex_map[0], &vertex_map[0] + num_vertices, [&vertices](int ia, int ib) { return vertices[ia].p.z < vertices[ib].p.z; });
	//std::stable_sort(&vertex_map[0], &vertex_map[0] + num_vertices, [&vertices](int ia, int ib) { return vertices[ia].p.y < vertices[ib].p.y; });
	//std::stable_sort(&vertex_map[0], &vertex_map[0] + num_vertices, [&vertices](int ia, int ib) { return vertices[ia].p.x < vertices[ib].p.x; });

	//auto id_map = core::make_unique_default<int[]>(num_vertices);
	//std::transform(&vertex_map[0], &vertex_map[0] + num_vertices, &id_map[0], [&vertices]() {});
	
	//ProcessingLayer::process(vertices, num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
	ProcessingLayer::process(new_vertices.get(), vertex_map.size(), new_indices2.get(), write_i, new_surfaces.data(), num_surfaces, materials, num_materials, textures, num_textures);
}

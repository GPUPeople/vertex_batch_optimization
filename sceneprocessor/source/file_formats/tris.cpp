


#include <cstdint>

#include <core/utils/memory>
#include <core/utils/io>

#include "../io.h"

#include "tris.h"


namespace tris
{
	void read(SceneBuilder& builder, const char* begin, std::size_t length)
	{
		memory_istreambuf b(begin, length);
		std::istream file(&b);

		auto num_vertices = ::read<std::uint32_t>(file);

		std::unique_ptr<float[]> vertices = std::make_unique<float[]>(num_vertices * 4);

		file.read((char*)&vertices[0], 4 * num_vertices);

		if (file.fail())
			throw std::runtime_error("error reading scenefile");

		std::vector<vertex> verts(num_vertices);
		std::vector<uint32_t> indices(num_vertices);

		uint32_t run = 0;

		for (uint32_t i = 0; i < num_vertices; i++)
		{
			verts[i].p = { vertices[i * 4], vertices[i * 4 + 1], vertices[i * 4 + 2] };
			indices[i] = run++;
		}

		builder.addVertices(std::move(verts));
		builder.addSurface(PrimitiveType::TRIANGLES, std::move(indices), "TRIS_FILE", 9, "None");

		std::cout << "Clipspace scene has\n"
			<< "\t" << num_vertices / 3 << " faces\n\n";

		int id = (num_vertices - 1) * 4;
	}

	void write(std::ostream& file, const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
	{

	}
}

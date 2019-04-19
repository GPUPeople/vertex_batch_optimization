


#include <cstdint>
#include <vector>
#include <algorithm>
#include <streambuf>
#include <sstream>
#include <iostream>

#include <core/utils/io>

#include "../io.h"

#include "binscene.h"


namespace
{
	const std::size_t MaterialNameLength = 256;
	const std::size_t TextureNameLength = 256;
	const std::size_t TextureFilenameLength = 1024;
}

namespace binscene
{
	void read(SceneBuilder& builder, const char* begin, std::size_t length)
	{
		memory_istreambuf b(begin, length);
		std::istream in(&b);

		std::vector<vertex> vertices;
		std::vector<std::uint32_t> indices;
		std::vector<surface> surfaces;
		std::vector<material> materials;
		std::vector<texture> textures;

		auto num_vertices = ::read<std::uint32_t>(in);
		vertices.resize(num_vertices);
		::read(&vertices[0], in, num_vertices);


		auto num_indices = ::read<std::uint32_t>(in);
		indices.resize(num_indices);
		::read(&indices[0], in, num_indices);

		auto num_surfaces = ::read<std::uint32_t>(in);
		surfaces.reserve(num_surfaces);
		for (std::uint32_t i = 0; i < num_surfaces; ++i)
		{
			auto start = ::read<std::uint32_t>(in);
			auto primitive_type = ::read<std::uint32_t>(in);
			auto num_indices = ::read<std::uint32_t>(in);
			int matId = ::read<std::int32_t>(in);

			std::stringstream sname;
			sname << "surface" << i;
			surfaces.emplace_back(sname.str().c_str(), sname.str().size(), static_cast<PrimitiveType>(primitive_type), start, num_indices, matId);
		}


		auto num_materials = ::read<std::uint32_t>(in);
		materials.reserve(num_materials);
		char mat_name_buf[MaterialNameLength+1];
		for (std::uint32_t i = 0; i < num_materials; ++i)
		{
			auto ambient = ::read<float3>(in);
			auto diffuse = ::read<float3>(in);
			auto specular = ::read<float4>(in);
			auto alpha = ::read<float>(in);
			int texId = ::read<std::int32_t>(in);

			auto name_length = ::read<std::uint32_t>(in);
			name_length = std::min<std::uint32_t>(name_length, MaterialNameLength);
			in.read(mat_name_buf, MaterialNameLength);
			mat_name_buf[name_length] = '\0';

			materials.emplace_back(mat_name_buf, ambient, diffuse, specular, alpha, texId);
		}

		auto num_textures = ::read<std::uint32_t>(in);
		textures.reserve(num_textures);
		char tex_name_buf[TextureNameLength + 1];
		char tex_fname_buf[TextureFilenameLength + 1];
		for (std::uint32_t i = 0; i < num_textures; ++i)
		{
			auto name_length = ::read<std::uint32_t>(in);
			name_length = std::min<std::uint32_t>(name_length, TextureNameLength);
			in.read(tex_name_buf, TextureNameLength);
			tex_name_buf[name_length] = '\0';

			auto fname_length = ::read<std::uint32_t>(in);
			fname_length = std::min<std::uint32_t>(fname_length, TextureFilenameLength);
			in.read(tex_fname_buf, TextureFilenameLength);
			tex_fname_buf[fname_length] = '\0';

			textures.emplace_back(tex_name_buf, tex_fname_buf);
		}

		for (auto & tex : textures)
			builder.addTexture(tex.name.c_str(), tex.fname.c_str());
		for (auto & mat : materials)
			builder.addMaterial(mat.name.c_str(), mat.ambient, mat.diffuse, mat.specular, mat.alpha, mat.texId >= 0 ? textures[mat.texId].name.c_str() : nullptr);
		for (auto & surface : surfaces)
		{
			std::vector<std::uint32_t> thisIds(&indices[surface.start], (&indices[surface.start]) + surface.num_indices);
			builder.addSurface(surface.primitive_type, std::move(thisIds), surface.name.c_str(), surface.name.size(), surface.matId >= 0 ? materials[surface.matId].name.c_str() : nullptr);
		}
		builder.addVertices(std::move(vertices));
	}


	void write(std::ostream& file, const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
	{
		std::string nothingness(std::max(TextureFilenameLength, std::max(MaterialNameLength, TextureNameLength)), '\0');

		::write(file, static_cast<std::uint32_t>(num_vertices));
		::write(file, vertices, num_vertices);
		

		::write(file, static_cast<std::uint32_t>(num_indices)); 
		::write(file, indices, num_indices);

		::write(file, static_cast<std::uint32_t>(num_surfaces));
		for (const surface* surface = surfaces; surface < surfaces + num_surfaces; ++surface)
		{
			::write(file, static_cast<std::uint32_t>(surface->primitive_type));
			::write(file, surface->start);
			::write(file, surface->num_indices);
			::write(file, surface->matId);
		}

		::write(file, static_cast<std::uint32_t>(num_materials));

		for (const material* material = materials; material < materials + num_materials; ++material)
		{
			::write(file, material->ambient);
			::write(file, material->diffuse);
			::write(file, material->specular);
			::write(file, material->alpha);
			::write(file, material->texId);
			::write(file, static_cast<std::uint32_t>(material->name.size()));
			file.write(material->name.c_str(), std::min(material->name.size(), MaterialNameLength));
			file.write(nothingness.c_str(), MaterialNameLength - std::min(material->name.size(), MaterialNameLength));
		}

		::write(file, static_cast<std::uint32_t>(num_textures));
		for (const texture* texture = textures; texture < textures + num_textures; ++texture)
		{
			::write(file, static_cast<std::uint32_t>(texture->name.size()));
			file.write(texture->name.c_str(), std::min(texture->name.size(),TextureNameLength));
			file.write(nothingness.c_str(), TextureNameLength - std::min(texture->name.size(), TextureNameLength));

			::write(file, static_cast<std::uint32_t>(texture->fname.size()));
			file.write(texture->fname.c_str(), std::min(texture->fname.size(), TextureFilenameLength));
			file.write(nothingness.c_str(), TextureFilenameLength - std::min(texture->fname.size(), TextureFilenameLength));
		}
	}
}

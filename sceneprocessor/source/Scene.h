


#ifndef INCLUDED_SCENE
#define INCLUDED_SCENE

#pragma once

#include <cstdint>
#include <vector>
#include <map>

#include <iosfwd>

#include "SceneBuilder.h"
#include "ProcessingLayer.h"


using import_func_t = void(SceneBuilder& builder, const char* begin, std::size_t length);


class Scene : private virtual SceneBuilder
{
	std::vector<vertex> vertices;
	std::vector<std::uint32_t> indices;

	std::vector<surface> surfaces;
	std::vector<material> materials;
	std::vector<texture> textures;

	std::map<std::string, int> materialMapping;
	std::map<std::string, int> textureMapping;


	void addVertices(std::vector<vertex>&& vertices);
	void addSurface(PrimitiveType primitive_type, std::vector<std::uint32_t>&& indices, const char* name, std::size_t name_length, const char* material_name);
	void addMaterial(const char* name, const float3& ambient, const float3& diffuse, const float4& specular, float alpha, const char* tex_name);
	void addTexture(const char* name, const char* filename);
	bool hasTexture(const char* name);
	bool hasMaterial(const char* name);

	void finalize(bool nomaterial, bool mergeequalmaterials);

public:
	Scene() = default;

	Scene(const Scene&) = delete;
	Scene& operator =(const Scene&) = delete;

	void import(import_func_t& import_func, const char* begin, std::size_t length);
	void importFrame(import_func_t& import_func, const char* begin, std::size_t length);

	void process(SceneSink& processor, bool nomaterial = false, bool mergeequalmaterials = false);
};

#endif  // INCLUDED_SCENE

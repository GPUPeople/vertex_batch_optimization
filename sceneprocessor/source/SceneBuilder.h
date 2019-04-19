


#ifndef INCLUDED_SCENE_BUILDER
#define INCLUDED_SCENE_BUILDER

#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>


struct float2
{
	float x;
	float y;
};

struct float3
{
	float x;
	float y;
	float z;
};

struct float4
{
	float x;
	float y;
	float z;
	float w;
};


struct vertex
{
	float3 p;
	float3 n;
	float2 t;

	vertex() = default;

	vertex(const float3& p, const float3& n, const float2& t)
		: p(p), n(n), t(t)
	{
	}

	bool operator==(const vertex& other) const
	{
		return (p.x == other.p.x) && (p.y == other.p.y) && (p.z == other.p.z)
			&& (n.x == other.n.x) && (n.y == other.n.y) && (n.z == other.n.z)
			&& (t.x == other.t.x) && (t.y == other.t.y);
	}
};

struct texture
{
	std::string name;
	std::string fname;

	texture() = default;

	texture(const char* name, const char* fname)
		: name(name), fname(fname)
	{
	}
};

struct material
{
	std::string name;
	float3 ambient;
	float3 diffuse;
	float4 specular;
	float alpha;
	int texId;

	material() = default;

	material(const char* name, const float3& ambient, const float3& diffuse, const float4& specular, float alpha, int texId = -1)
		: name(name), ambient(ambient), diffuse(diffuse), specular(specular), alpha(alpha), texId(texId)
	{
	}
};

enum class PrimitiveType
{
	TRIANGLES,
	QUADS
};

struct surface
{
	std::string name;
	PrimitiveType primitive_type;
	std::uint32_t start;
	std::uint32_t num_indices;
	int matId;

	surface() = default;

	surface(const char* name, std::size_t name_length, PrimitiveType primitive_type, std::uint32_t start, std::uint32_t num_indices, int matId = -1)
		: name(name, name_length), primitive_type(primitive_type), start(start), num_indices(num_indices), matId(matId)
	{
	}
};

class SceneBuilder
{
protected:
	SceneBuilder() = default;
	SceneBuilder(const SceneBuilder&) = default;
	~SceneBuilder() = default;
	SceneBuilder& operator =(const SceneBuilder&) = default;

public:
	virtual void addVertices(std::vector<vertex>&& vertices) = 0;
	virtual void addSurface(PrimitiveType primitive_type, std::vector<std::uint32_t>&& indices, const char* name, std::size_t name_length, const char* material_name) = 0;
	virtual void addMaterial(const char* name, const float3& ambient, const float3& diffuse, const float4& specular, float alpha, const char* tex_name) = 0;
	virtual void addTexture(const char* name, const char* filename) = 0;
};

#endif  // INCLUDED_SCENE_BUILDER

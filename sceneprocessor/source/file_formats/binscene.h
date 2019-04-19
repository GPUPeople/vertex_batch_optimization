


#ifndef INCLUDED_BINSCENE
#define INCLUDED_BINSCENE

#pragma once

#include <cstddef>
#include <iosfwd>

#include "../SceneBuilder.h"


namespace binscene
{
	void read(SceneBuilder& builder, const char* begin, std::size_t length);
	void write(std::ostream& file, const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures);
}

#endif  // INCLUDED_BINSCENE

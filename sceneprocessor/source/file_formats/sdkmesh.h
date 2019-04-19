


#ifndef INCLUDED_SDKMESH
#define INCLUDED_SDKMESH

#pragma once

#include <cstddef>
#include <iosfwd>

#include "../SceneBuilder.h"


namespace sdkmesh
{
	void read(SceneBuilder& builder, const char* begin, std::size_t length);
}

#endif  // INCLUDED_SDKMESH

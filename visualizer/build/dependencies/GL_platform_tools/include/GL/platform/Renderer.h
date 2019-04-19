


#ifndef INCLUDED_GL_PLATFORM_RENDERER
#define INCLUDED_GL_PLATFORM_RENDERER

#pragma once

#include "interface.h"


namespace GL::platform
{
	struct INTERFACE Renderer
	{
		virtual void render() = 0;

	protected:
		Renderer() = default;
		Renderer(Renderer&&) = default;
		Renderer(const Renderer&) = default;
		Renderer& operator =(Renderer&&) = default;
		Renderer& operator =(const Renderer&) = default;
		~Renderer() = default;
	};
}

#endif  // INCLUDED_GL_PLATFORM_RENDERER

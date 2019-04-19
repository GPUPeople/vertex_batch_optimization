


#ifndef INCLUDED_GL_PLATFORM_DISPLAY_HANDLER
#define INCLUDED_GL_PLATFORM_DISPLAY_HANDLER

#pragma once

#include "interface.h"

#include "window_fwd.h"


namespace GL::platform
{
	struct INTERFACE DisplayHandler
	{
		virtual void close(Window* window) = 0;
		virtual void destroy(Window* window) = 0;

		virtual void move(int x, int y, Window* window) = 0;
		virtual void resize(int width, int height, Window* window) = 0;

	protected:
		DisplayHandler() = default;
		DisplayHandler(DisplayHandler&&) = default;
		DisplayHandler(const DisplayHandler&) = default;
		DisplayHandler& operator =(DisplayHandler&&) = default;
		DisplayHandler& operator =(const DisplayHandler&) = default;
		~DisplayHandler() = default;
	};
}

#endif  // INCLUDED_GL_PLATFORM_DISPLAY_HANDLER

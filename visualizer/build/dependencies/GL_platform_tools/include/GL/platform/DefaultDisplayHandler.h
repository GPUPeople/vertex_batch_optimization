


#ifndef INCLUDED_GL_PLATFORM_DEFAULT_DISPLAY_HANDLER
#define INCLUDED_GL_PLATFORM_DEFAULT_DISPLAY_HANDLER

#pragma once

#include "DisplayHandler.h"


namespace GL::platform
{
	class DefaultDisplayHandler : public virtual DisplayHandler
	{
	protected:
		DefaultDisplayHandler() = default;
		DefaultDisplayHandler(DefaultDisplayHandler&&) = default;
		DefaultDisplayHandler(const DefaultDisplayHandler&) = default;
		DefaultDisplayHandler& operator =(DefaultDisplayHandler&&) = default;
		DefaultDisplayHandler& operator =(const DefaultDisplayHandler&) = default;
		~DefaultDisplayHandler() = default;

	public:
		void close(Window* window) override;
		void destroy(Window* window) override;

		void move(int x, int y, Window* window) override;
		void resize(int width, int height, Window* window) override;
	};
}

#endif  // INCLUDED_GL_PLATFORM_DEFAULT_DISPLAY_HANDLER

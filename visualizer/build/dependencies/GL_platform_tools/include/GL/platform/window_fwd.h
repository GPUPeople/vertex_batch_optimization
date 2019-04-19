


#ifndef INCLUDED_GL_PLATFORM_WINDOW_FWD
#define INCLUDED_GL_PLATFORM_WINDOW_FWD

#pragma once


#if defined(_WIN32)
namespace Win32::GL
{
	class Window;
}

namespace GL::platform
{
	using Win32::GL::Window;
}
#elif defined(__gnu_linux__)
namespace X11::GL
{
	class Window;
}

namespace GL::platform
{
	using X11::GL::Window;
}
#else
#error "platform not supported."
#endif

#endif  // INCLUDED_GL_PLATFORM_WINDOW_FWD




#ifndef INCLUDED_GL_PLATFORM_WINDOW
#define INCLUDED_GL_PLATFORM_WINDOW

#pragma once

#include "window_fwd.h"

#include "DisplayHandler.h"
#include "InputHandler.h"

#if defined(_WIN32)
#include "../../../source/win32/Win32GLWindow.h"
#elif defined(__gnu_linux__)
#include "../../../source/x11/X11GLWindow.h"
#endif

#endif  // INCLUDED_GL_PLATFORM_WINDOW

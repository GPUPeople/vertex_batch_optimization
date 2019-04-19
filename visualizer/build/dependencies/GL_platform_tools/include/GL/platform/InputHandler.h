


#ifndef INCLUDED_GL_PLATFORM_INPUT_HANDLER
#define INCLUDED_GL_PLATFORM_INPUT_HANDLER

#pragma once

#include <cstddef>

#include "interface.h"

#include "window_fwd.h"

#if defined(_WIN32)
#include "../../../source/win32/Win32Input.h"
#elif defined(__gnu_linux__)
#include "../../../source/x11/X11Input.h"
#else
#error "platform not supported."
#endif


namespace GL::platform
{
	struct INTERFACE MouseInputHandler
	{
		virtual void buttonDown(Button button, int x, int y, Window* window) = 0;
		virtual void buttonUp(Button button, int x, int y, Window* window) = 0;
		virtual void mouseMove(int x, int y, Window* window) = 0;
		virtual void mouseWheel(int delta, Window* window) = 0;

	protected:
		MouseInputHandler() = default;
		MouseInputHandler(MouseInputHandler&&) = default;
		MouseInputHandler(const MouseInputHandler&) = default;
		MouseInputHandler& operator =(MouseInputHandler&&) = default;
		MouseInputHandler& operator =(const MouseInputHandler&) = default;
		~MouseInputHandler() = default;
	};

	struct INTERFACE KeyboardInputHandler
	{
		virtual void keyDown(Key key, Window* window) = 0;
		virtual void keyUp(Key key, Window* window) = 0;

	protected:
		KeyboardInputHandler() = default;
		KeyboardInputHandler(KeyboardInputHandler&&) = default;
		KeyboardInputHandler(const KeyboardInputHandler&) = default;
		KeyboardInputHandler& operator =(KeyboardInputHandler&&) = default;
		KeyboardInputHandler& operator =(const KeyboardInputHandler&) = default;
		~KeyboardInputHandler() = default;
	};

	struct INTERFACE ConsoleHandler
	{
		virtual void command(const char* command, std::size_t length) = 0;

	protected:
		ConsoleHandler() = default;
		ConsoleHandler(ConsoleHandler&&) = default;
		ConsoleHandler(const ConsoleHandler&) = default;
		ConsoleHandler& operator =(ConsoleHandler&&) = default;
		ConsoleHandler& operator =(const ConsoleHandler&) = default;
		~ConsoleHandler() = default;
	};
}

#endif  // INCLUDED_GL_PLATFORM_INPUT_HANDLER

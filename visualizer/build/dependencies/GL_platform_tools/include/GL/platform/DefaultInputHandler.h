


#ifndef INCLUDED_GL_PLATFORM_DEFAULT_INPUT_HANDLER
#define INCLUDED_GL_PLATFORM_DEFAULT_INPUT_HANDLER

#pragma once

#include "InputHandler.h"


namespace GL::platform
{
	class DefaultMouseInputHandler : public virtual MouseInputHandler
	{
	protected:
		DefaultMouseInputHandler() = default;
		DefaultMouseInputHandler(DefaultMouseInputHandler&&) = default;
		DefaultMouseInputHandler(const DefaultMouseInputHandler&) = default;
		DefaultMouseInputHandler& operator =(DefaultMouseInputHandler&&) = default;
		DefaultMouseInputHandler& operator =(const DefaultMouseInputHandler&) = default;
		~DefaultMouseInputHandler() = default;

	public:
		void buttonDown(Button button, int x, int y, Window* window) override;
		void buttonUp(Button button, int x, int y, Window* window) override;
		void mouseMove(int x, int y, Window* window) override;
		void mouseWheel(int delta, Window* window) override;
	};

	class DefaultKeyboardInputHandler : public virtual KeyboardInputHandler
	{
	protected:
		DefaultKeyboardInputHandler() = default;
		DefaultKeyboardInputHandler(DefaultKeyboardInputHandler&&) = default;
		DefaultKeyboardInputHandler(const DefaultKeyboardInputHandler&) = default;
		DefaultKeyboardInputHandler& operator =(DefaultKeyboardInputHandler&&) = default;
		DefaultKeyboardInputHandler& operator =(const DefaultKeyboardInputHandler&) = default;
		~DefaultKeyboardInputHandler() = default;

	public:
		void keyDown(Key key, Window* window) override;
		void keyUp(Key key, Window* window) override;
	};

	class DefaultConsoleHandler : public virtual ConsoleHandler
	{
	protected:
		DefaultConsoleHandler() = default;
		DefaultConsoleHandler(DefaultConsoleHandler&&) = default;
		DefaultConsoleHandler(const DefaultConsoleHandler&) = default;
		DefaultConsoleHandler& operator =(DefaultConsoleHandler&&) = default;
		DefaultConsoleHandler& operator =(const DefaultConsoleHandler&) = default;
		~DefaultConsoleHandler() = default;

	public:
		void command(const char* command, std::size_t length) override;
	};
}

#endif  // INCLUDED_GL_PLATFORM_DEFAULT_INPUT_HANDLER

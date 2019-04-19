


#include <GL/platform/DefaultInputHandler.h>


namespace GL::platform
{
	void DefaultMouseInputHandler::buttonDown(Button button, int x, int y, Window* window)
	{
	}

	void DefaultMouseInputHandler::buttonUp(Button button, int x, int y, Window* window)
	{
	}

	void DefaultMouseInputHandler::mouseMove(int x, int y, Window* window)
	{
	}

	void DefaultMouseInputHandler::mouseWheel(int delta, Window* window)
	{
	}


	void DefaultKeyboardInputHandler::keyDown(Key key, Window* window)
	{
	}

	void DefaultKeyboardInputHandler::keyUp(Key key, Window* window)
	{
	}


	void DefaultConsoleHandler::command(const char* command, std::size_t length)
	{
	}
}

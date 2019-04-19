


#include <GL/platform/Application.h>
#include <GL/platform/DefaultDisplayHandler.h>


namespace GL::platform
{
	void DefaultDisplayHandler::close(Window* window)
	{
		GL::platform::quit();
	}

	void DefaultDisplayHandler::destroy(Window* window)
	{
	}

	void DefaultDisplayHandler::move(int x, int y, Window* window)
	{
	}

	void DefaultDisplayHandler::resize(int width, int height, Window* window)
	{
	}
}




#include <cstdint>
#include <algorithm>
#include <memory>
#include <iostream>

#include <GL/error.h>

#include "GeometryViz.h"
#include "Display.h"

extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x1U;

namespace
{
	void APIENTRY OpenGLDebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		OutputDebugStringA(message);
		OutputDebugStringA("\n");
	}

	WINDOWPLACEMENT loadWindowPlacement(const config::Database& config)
	{
		WINDOWPLACEMENT window_placement;
		window_placement.length = sizeof(WINDOWPLACEMENT);
		window_placement.flags = config.queryInt("flags", 0U);
		window_placement.showCmd = config.queryInt("show", SW_SHOWNORMAL);
		window_placement.ptMinPosition.x = config.queryInt("min_x", 0);
		window_placement.ptMinPosition.y = config.queryInt("min_y", 0);
		window_placement.ptMaxPosition.x = config.queryInt("max_x", 0);
		window_placement.ptMaxPosition.y = config.queryInt("max_y", 0);
		window_placement.rcNormalPosition.left = config.queryInt("left", 0);
		window_placement.rcNormalPosition.top = config.queryInt("top", 0);
		window_placement.rcNormalPosition.right = config.queryInt("right", 800);
		window_placement.rcNormalPosition.bottom = config.queryInt("bottom", 600);
		return window_placement;
	}

	void saveWindowPlacement(config::Database& config, const WINDOWPLACEMENT& window_placement)
	{
		config.storeInt("flags", window_placement.flags);
		config.storeInt("show", window_placement.showCmd);
		config.storeInt("min_x", window_placement.ptMinPosition.x);
		config.storeInt("min_y", window_placement.ptMinPosition.y);
		config.storeInt("max_x", window_placement.ptMaxPosition.x);
		config.storeInt("max_y", window_placement.ptMaxPosition.y);
		config.storeInt("left", window_placement.rcNormalPosition.left);
		config.storeInt("top", window_placement.rcNormalPosition.top);
		config.storeInt("right", window_placement.rcNormalPosition.right);
		config.storeInt("bottom", window_placement.rcNormalPosition.bottom);
	}
}

Display::Display(const config::Database& config, Camera& camera)
	: window("vertex processing visualizer", loadWindowPlacement(config.queryNode("window")), 24),
	  context(window.createContext(4, 5, true)),
	  ctx(context, window),
	  camera(camera)
{
	std::cout << "OpenGL on " << glGetString(GL_RENDERER) << std::endl;

	glDebugMessageCallback(OpenGLDebugOutputCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	glEnable(GL_FRAMEBUFFER_SRGB);
	//glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
	glClearColor(0.6f, 0.7f, 1.0f, 1.0f);

	glBindBuffer(GL_UNIFORM_BUFFER, camera_uniform_buffer);
	glBufferStorage(GL_UNIFORM_BUFFER, sizeof(Camera::UniformBuffer), nullptr, GL_DYNAMIC_STORAGE_BIT);

	window.attach(this);
	GL::throw_error();

	window.resize(2048,2048);
	//window.resize(1024,1024);
}

void Display::loadGeometry(const GeometryViz* geometry_viz)
{
	this->geometry_viz = geometry_viz;
}

void Display::resize(int width, int height, GL::platform::Window*)
{
	buffer_width = width;
	buffer_height = height;
}

void Display::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, buffer_width, buffer_height);

	if (geometry_viz)
	{
		Camera::UniformBuffer camera_params;
		camera.writeUniformBuffer(&camera_params, buffer_width * 1.0f / buffer_height);
		glNamedBufferSubData(camera_uniform_buffer, 0, sizeof(Camera::UniformBuffer), &camera_params);
		geometry_viz->draw(camera_uniform_buffer);
	}

	GL::throw_error();

	ctx.swapBuffers();
}

image2D<RGBA8> Display::screenshot() const
{
	image2D<RGBA8> buffer(buffer_width, buffer_height);

	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, buffer_width, buffer_height, GL_RGBA, GL_UNSIGNED_BYTE, data(buffer));
	GL::throw_error();

	using std::swap;
	for (int y = 0; y < height(buffer) / 2; ++y)
		for (int x = 0; x < width(buffer); ++x)
			std::swap(buffer(x, y), buffer(x, height(buffer) - y - 1));

	return buffer;
}

void Display::attach(GL::platform::MouseInputHandler* mouse_input)
{
	window.attach(mouse_input);
}

void Display::attach(GL::platform::KeyboardInputHandler* keyboard_input)
{
	window.attach(keyboard_input);
}

void Display::addSubtitle(const std::string& subtitle)
{
	std::string newtitle = title + subtitle;
	window.title(newtitle.c_str());
}

void Display::save(config::Database& config) const
{
	WINDOWPLACEMENT placement;
	window.savePlacement(placement);
	saveWindowPlacement(config.openNode("window"), placement);
}

void Display::swapBuffers()
{
	ctx.swapBuffers();
}

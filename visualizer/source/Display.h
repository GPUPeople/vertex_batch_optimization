


#ifndef INCLUDED_DISPLAY
#define INCLUDED_DISPLAY

#pragma once

#include <optional>

#include <config/Database.h>

#include <GL/platform/Renderer.h>
#include <GL/platform/Context.h>
#include <GL/platform/Window.h>
#include <GL/platform/DefaultDisplayHandler.h>

#include <GL/buffer.h>

#include <image.h>
#include <rgba8.h>

#include "Camera.h"


class GeometryViz;

class Display : public virtual GL::platform::Renderer, private GL::platform::DefaultDisplayHandler
{
	GL::platform::Window window;
	GL::platform::Context context;
	GL::platform::context_scope<GL::platform::Window> ctx;

	Camera& camera;

	int buffer_width;
	int buffer_height;

	const std::string title = "vertex processing visualizer";

	GL::Buffer camera_uniform_buffer;

	const GeometryViz* geometry_viz = nullptr;

	void resize(int width, int height, GL::platform::Window*) override;

public:
	Display(const config::Database& config, Camera& camera);

	void loadGeometry(const GeometryViz* geometry_viz);

	void render();

	image2D<RGBA8> screenshot() const;

	void attach(GL::platform::MouseInputHandler* mouse_input);
	void attach(GL::platform::KeyboardInputHandler* keyboard_input);

	void addSubtitle(const std::string& subtitle);

	void save(config::Database& config) const;

	void swapBuffers();
};

#endif  // INCLUDED_DISPLAY

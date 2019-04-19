


#ifndef INCLUDED_VISUALIZER
#define INCLUDED_VISUALIZER

#pragma once

#include <string>
#include <optional>
#include <filesystem>

#include <config/Database.h>

#include "OrbitalNavigator.h"
#include "PerspectiveCamera.h"
#include "GeometryViz.h"
#include "Display.h"


class Visualizer : public virtual GL::platform::KeyboardInputHandler, public virtual GL::platform::MouseInputHandler
{
	OrbitalNavigator navigator;
	PerspectiveCamera camera;
	Display display;

	std::optional<GeometryViz> geometry_viz;

	void keyDown(GL::platform::Key key, GL::platform::Window*) override;
	void keyUp(GL::platform::Key key, GL::platform::Window*) override;
	void buttonDown(GL::platform::Button button, int x, int y, GL::platform::Window*) override;
	void buttonUp(GL::platform::Button button, int x, int y, GL::platform::Window*) override;

	void mouseMove(int x, int y, GL::platform::Window*) override;
	void mouseWheel(int delta, GL::platform::Window*) override;

	bool singleBatchMode;
	int singleBatch;

public:
	Visualizer(const config::Database& config);

	void loadVertexInvocationCounters(const std::experimental::filesystem::path& vsi_file);
	void loadBatchInfo(const std::experimental::filesystem::path & vsi_file, bool load_tool);
	void loadScene(const std::experimental::filesystem::path& scene_file);

	void run();

	void screenshot(const char* filename = nullptr);

	void save(config::Database& config) const;
};

#endif  // INCLUDED_VISUALIZER

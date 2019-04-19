


#ifndef INCLUDED_SCENE_PROCESSOR
#define INCLUDED_SCENE_PROCESSOR

#pragma once

#include <string_view>
#include <filesystem>
#include <stack>
#include <deque>

#include "ProcessingLayer.h"

#include "Scene.h"


class SceneProcessor : private virtual SceneSink
{
	Scene scene;

	SceneSink* processing_layer = this;

	bool perform_export = false;
	std::experimental::filesystem::path output_file_name;

	using clock_t = std::chrono::steady_clock;
	using time_t = std::chrono::time_point<clock_t>;
	using stack_t = std::stack<time_t, std::deque<time_t>>;
	stack_t timings;

	virtual void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;

public:
	void addProcessingLayer(std::string_view name);
	void addTimingLayer();
	void addOutputLayer(const std::experimental::filesystem::path& filename);
	void ingestFrame(const std::experimental::filesystem::path& filename);
	void ingest(const std::experimental::filesystem::path& filename);
	void process();
};

#endif  // INCLUDED_SCENE_PROCESSOR

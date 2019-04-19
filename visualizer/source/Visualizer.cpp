


#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>

#include <core/utils/memory>
#include <core/utils/io>

#include <png.h>

#include <GL/platform/Application.h>

#include "Visualizer.h"


Visualizer::Visualizer(const config::Database& config)
	: navigator(config.queryNode("navigator"), -math::constants<float>::pi() * 0.5f, 0.0f, 2.0f),
	  camera(60.0f * math::constants<float>::pi() / 180.0f, 0.01f, 1000.0f),
	  display(config.queryNode("display"), camera),
	  singleBatchMode(false),
	  singleBatch(0)
{
	camera.attach(&navigator);
	display.attach(static_cast<GL::platform::MouseInputHandler*>(&navigator));
	display.attach(static_cast<GL::platform::KeyboardInputHandler*>(this));
	//renderer.attach(static_cast<GL::platform::MouseInputHandler*>(&input_handler));

	std::cout << R"""(usage:
	 Tab     cycle render modes
	  W      toggle wireframe
	  T      toggle triangle order curve
	  S      toggle patch silhouette
	  B      toggle single batch vis
	RIGHT    inc selected batch
	 UP      inc selected batch by 10
	LEFT     dec selected batch
	DOWN     dec selected batch by 10

	left mouse        rotate
	middle mouse      pan
	right mouse       zoom
	mouse wheel       zoom
	BACKSPACE         reset camera
)""" << std::endl;
}

void Visualizer::keyDown(GL::platform::Key key, GL::platform::Window* window)
{
	static_cast<GL::platform::KeyboardInputHandler*>(&navigator)->keyDown(key, window);
}

void Visualizer::keyUp(GL::platform::Key key, GL::platform::Window* window)
{
	switch (key)
	{
	case GL::platform::Key::BACKSPACE:
		navigator.reset();
		return;

	case GL::platform::Key::TAB:
	{
		auto subtitle = geometry_viz->cycleRenderMode();
		display.addSubtitle(subtitle);
		return;
	}
	case GL::platform::Key::C_T:
		geometry_viz->toggleTriOrderCurve();
		return;

	case GL::platform::Key::C_S:
		geometry_viz->togglePatchSilhouette();
		return;

	case GL::platform::Key::C_W:
		geometry_viz->toggleWireframe();
		return;

	case GL::platform::Key::F8:
		screenshot();
		return;

	case GL::platform::Key::C_B:
		singleBatchMode = !singleBatchMode;
		if (singleBatchMode)
			geometry_viz->focusBatch(singleBatch);
		else
			geometry_viz->focusBatch(-1);
		return;

	case GL::platform::Key::RIGHT:
		singleBatchMode = true;
		geometry_viz->focusBatch(++singleBatch);
		return;

	case GL::platform::Key::LEFT:
		singleBatchMode = true;
		geometry_viz->focusBatch(--singleBatch);
		return;

	case GL::platform::Key::UP:
		singleBatchMode = true;
		geometry_viz->focusBatch(singleBatch += 10);
		return;

	case GL::platform::Key::DOWN:
		singleBatchMode = true;
		geometry_viz->focusBatch(singleBatch -= 10);
		return;
	}
	static_cast<GL::platform::KeyboardInputHandler*>(&navigator)->keyDown(key, window);
}

void Visualizer::buttonDown(GL::platform::Button button, int x, int y, GL::platform::Window*)
{
}

void Visualizer::buttonUp(GL::platform::Button button, int x, int y, GL::platform::Window*)
{
}

void Visualizer::mouseMove(int x, int y, GL::platform::Window*)
{
}

void Visualizer::mouseWheel(int delta, GL::platform::Window*)
{
}

namespace
{
	auto countBits(std::uint32_t v)
	{
		auto c = ((v & 0xfff) * 0x1001001001001 & 0x84210842108421) % 0x1f;
		c += (((v & 0xfff000) >> 12) * 0x1001001001001 & 0x84210842108421) % 0x1f;
		c += ((v >> 24) * 0x1001001001001 & 0x84210842108421) % 0x1f;
		return c;
	}
}

void Visualizer::loadVertexInvocationCounters(const std::experimental::filesystem::path& vsi_file)
{
	// vsi file format
	//
	// uint8_t            length of GPU description
	// char[]             GPU description
	// uint32_t           PCI vendor ID
	// uint32_t           PCI device ID
	// uint32_t           number of indices drawn
	// uint32_t           number of vertices
	// uint8_t[]          per vertex invocation counters
	//

	auto file = std::ifstream(vsi_file, std::ios::binary);
	if (!file)
		throw std::runtime_error("unable to open invocation counters file");

	auto gpu_desc_length = read<std::uint8_t>(file);
	file.seekg(gpu_desc_length + 8U, std::ios::cur);

	auto num_indices = read<std::uint32_t>(file);
	auto clock_ticks = read<std::uint64_t>(file);
	auto clock_frequency = read<std::uint64_t>(file);
	auto vertex_shader_invoc = read<std::uint64_t>(file);

	auto num = read<std::uint32_t>(file);

	if ((num & 0x80000000) == 0)
	{
		auto num_vertices = num;
		auto inv_counters = core::make_unique_default<std::uint32_t[]>(num_vertices);

		//read(&inv_counters[0], file, num_vertices);
		for (unsigned int i = 0; i < num_vertices; ++i)
			inv_counters[i] = read<std::uint8_t>(file);

		geometry_viz->loadVertexInvocationCounters(&inv_counters[0], num_vertices);
	}
	else
	{
		std::uint64_t total_observed_shader_invoc = 0;
		std::uint32_t max_id = 0;
		int batch = 0;
		auto inv_counters = std::make_unique<std::uint32_t[]>(num_indices);
		auto batch_ids = std::make_unique<std::set<uint32_t>[]>(num_indices);
		std::uint64_t num_batch_info_elements = num & 0x7FFFFFFF;
		std::vector<float> avg_batch_indices;
		while (num_batch_info_elements)
		{
			std::uint32_t mask[4];
			read(mask, file);
			auto num_active_threads = countBits(mask[0]) + countBits(mask[1]) + countBits(mask[2]) + countBits(mask[3]);
			total_observed_shader_invoc += num_active_threads;
			std::uint32_t sum_batch_inds = 0;
			for (int i = 0; i < num_active_threads; ++i)
			{
				auto index = read<std::uint32_t>(file);
				sum_batch_inds += index;
				batch_ids[index].insert(batch);
				//printf("%d ", index);
				max_id = std::max(max_id, index);
				inv_counters[index]++;
			}
			avg_batch_indices.push_back(static_cast<float>(sum_batch_inds) / num_active_threads);
			num_batch_info_elements -= 4 + num_active_threads;
			batch++;
		}
		std::uint32_t num_vertices = max_id + 1;
		geometry_viz->loadVertexInvocationCounters(&inv_counters[0], num_vertices);
	}
}

void Visualizer::loadBatchInfo(const std::experimental::filesystem::path& vsi_file, bool load_tool)
{
	// vsi file format
	//
	// uint8_t            length of GPU description
	// char[]             GPU description
	// uint32_t           PCI vendor ID
	// uint32_t           PCI device ID
	// uint32_t           number of indices drawn
	// uint32_t           number of vertices
	// uint8_t[]          per vertex invocation counters
	//

	auto file = std::ifstream(vsi_file, std::ios::binary);
	if (!file)
		throw std::runtime_error("unable to open invocation counters file");

	auto gpu_desc_length = read<std::uint8_t>(file);
	file.seekg(gpu_desc_length + 8U, std::ios::cur);

	auto num_indices = read<std::uint32_t>(file);
	auto clock_ticks = read<std::uint64_t>(file);
	auto clock_frequency = read<std::uint64_t>(file);
	auto vertex_shader_invoc = read<std::uint64_t>(file);

	auto num = read<std::uint32_t>(file);

	if ((num & 0x80000000) == 0)
	{
		auto num_vertices = num;
		auto inv_counters = core::make_unique_default<std::uint32_t[]>(num_vertices);

		//read(&inv_counters[0], file, num_vertices);
		for (unsigned int i = 0; i < num_vertices; ++i)
			inv_counters[i] = read<std::uint8_t>(file);

		geometry_viz->loadVertexInvocationCounters(&inv_counters[0], num_vertices);
	}
	else
	{
		std::uint64_t total_observed_shader_invoc = 0;
		std::uint32_t max_id = 0;
		int batch = 0;
		auto inv_counters = std::make_unique<std::uint32_t[]>(num_indices);
		auto batch_ids = std::make_unique<std::set<uint32_t>[]>(num_indices);
		std::uint64_t num_batch_info_elements = num & 0x7FFFFFFF;
		std::vector<float> avg_batch_indices;
		while (num_batch_info_elements)
		{
			std::uint32_t mask[4];
			read(mask, file);
			auto num_active_threads = countBits(mask[0]) + countBits(mask[1]) + countBits(mask[2]) + countBits(mask[3]);
			total_observed_shader_invoc += num_active_threads;
			std::uint32_t sum_batch_inds = 0;
			for (int i = 0; i < num_active_threads; ++i)
			{
				auto index = read<std::uint32_t>(file);
				sum_batch_inds += index;
				batch_ids[index].insert(batch);
				//printf("%d ", index);
				max_id = std::max(max_id, index);
				inv_counters[index]++;
			}
			avg_batch_indices.push_back(static_cast<float>(sum_batch_inds) / num_active_threads);
			num_batch_info_elements -= 4 + num_active_threads;
			batch++;
		}
		std::uint32_t num_vertices = max_id + 1;
		geometry_viz->loadBatchIfno(batch_ids.get(), avg_batch_indices, num_vertices, load_tool);
	}
}

void Visualizer::loadScene(const std::experimental::filesystem::path& scene_file)
{
	std::ifstream file(scene_file, std::ios::binary);

	if (!file)
		throw std::runtime_error("unable to open scene file");

	auto num_vertices = read<std::uint32_t>(file);
	auto vertices = core::make_unique_default<GeometryVertex[]>(num_vertices);
	read(&vertices[0], file, num_vertices);

	auto num_indices = read<std::uint32_t>(file);
	auto indices = core::make_unique_default<std::uint32_t[]>(num_indices);
	read(&indices[0], file, num_indices);

	// geometry_viz.emplace(display, &vertices[0], num_vertices, &indices[0], num_indices);
	geometry_viz.emplace(&vertices[0], num_vertices, &indices[0], num_indices);

	//if (vsi_file.extension() != ".vsi")
	//	throw std::runtime_error("unknown file format");
	//
	//loadVertexInvocationCounters(vsi_file);

	display.loadGeometry(&*geometry_viz);
}

void Visualizer::run()
{
	GL::platform::run(display);
}

void Visualizer::screenshot(const char* filename)
{
	display.render();

	if (filename)
	{
		PNG::saveRGBA8(filename, display.screenshot());
	}
	else
	{
		SYSTEMTIME time;
		GetLocalTime(&time);

		std::ostringstream filename;
		filename << time.wYear << '-' << std::setfill('0') << std::setw(2)
		         << time.wMonth << '-' << std::setw(2)
		         << time.wDay << 'T' << std::setw(2)
		         << time.wHour << '_' << std::setw(2)
		         << time.wMinute << '_' << std::setw(2)
		         << time.wSecond << '_' << std::setw(3)
		         << time.wMilliseconds << "_"
		         << "bla" << ".png";

		PNG::saveRGBA8(filename.str().c_str(), display.screenshot());
	}
}

void Visualizer::save(config::Database& config) const
{
	navigator.save(config.openNode("navigator"));
	display.save(config.openNode("display"));
}

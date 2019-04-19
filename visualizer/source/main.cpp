


#include <exception>
#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <config/InMemoryDatabase.h>
#include <configfile.h>

#include "argparse.h"
#include "Visualizer.h"

using namespace std::literals;


namespace
{
	std::ostream& printUsage(std::ostream& out)
	{
		return out << R"""(usage: visualizer [-screen <screenshot-name>] [--prediction <vsi-file>] [--info <vsi-file>] <scene-file>
)""";
	}

	std::experimental::filesystem::path findVSIFile(const std::experimental::filesystem::path& scene_file, const std::experimental::filesystem::path& vsi_dir)
	{
		auto stem = scene_file.stem();

		for (auto&& f : std::experimental::filesystem::directory_iterator(vsi_dir))
		{
			auto p = f.path();

			if (p.extension() == ".vsi" && p.stem().stem() == stem)
				return p;
		}

		return {};
	}
}

int main(int argc, char* argv[])
{
	try
	{
		config::InMemoryDatabase config;

		constexpr char configfile[] = "vpv.cfg";

		{
			std::ifstream file(configfile);
			if (file)
				configfile::read(config, file, configfile);
		}

		Visualizer visualizer(config);

		const char* scene = nullptr;
		const char* tool_vsi = nullptr;
		const char* prediction_vsi = nullptr;
		const char* screenshot = nullptr;

		for (const char* const * a = argv + 1; *a; ++a)
		{
			if (parseStringArgument(prediction_vsi, a, "--prediction"sv) || parseStringArgument(tool_vsi, a, "--info"sv))
				;
			else if (parseStringArgument(screenshot, a, "--screen"sv))
				;
			else
				scene = *a;
		}

		if (!scene)
			throw usage_error("no scene file specified");

		std::experimental::filesystem::path scene_file = scene;

		visualizer.loadScene(scene_file);

		if (!prediction_vsi && !tool_vsi)
		{
			auto f = findVSIFile(scene_file, scene_file.parent_path());

			if (!f.empty())
				visualizer.loadVertexInvocationCounters(f);
		}
		if (tool_vsi)
		{
			std::experimental::filesystem::path vsi_path = tool_vsi;
			if (std::experimental::filesystem::is_directory(vsi_path))
			{
				auto f = findVSIFile(scene_file, vsi_path);

				if (!f.empty())
				{
					visualizer.loadBatchInfo(f, true);
					visualizer.loadVertexInvocationCounters(f);
				}
			}
			else
			{
				auto f = vsi_path;
				if (!std::experimental::filesystem::exists(f))
					throw std::runtime_error("unable to open invocation counters file");
				visualizer.loadBatchInfo(f, true);
				visualizer.loadVertexInvocationCounters(f);
			}
		}
		if (prediction_vsi)
		{
			std::experimental::filesystem::path vsi_path = prediction_vsi;
			if (std::experimental::filesystem::is_directory(vsi_path))
			{
				auto f = findVSIFile(scene_file, vsi_path);

				if (!f.empty())
					visualizer.loadBatchInfo(f, false);
			}
			else
			{
				auto f = vsi_path;
				if (!std::experimental::filesystem::exists(f))
					throw std::runtime_error("unable to open invocation counters file");
				visualizer.loadBatchInfo(f, false);
			}
		}

		if (screenshot)
			visualizer.screenshot(screenshot);
		else
			visualizer.run();

		visualizer.save(config);

		configfile::write(configfile, config);
	}
	catch (const usage_error& e)
	{
		std::cerr << e.what() << std::endl;
		printUsage(std::cout);
		return -1;
	}
	catch (const std::exception& e)
	{
		std::cout << "error: " << e.what() << '\n';
		return -1;
	}
	catch (...)
	{
		std::cout << "unknown error\n";
		return -128;
	}

	return 0;
}

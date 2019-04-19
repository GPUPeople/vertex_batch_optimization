#include <exception>
#include <iostream>
#include <cstdint>
#include <memory>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <core/utils/memory>

#include "layers/GBatchOptimizer.h"
#include "layers/VertexReuseStats.h"
#include "layers/Randi.h"

#include "file_formats/obj.h"
#include "file_formats/tris.h"
#include "file_formats/candy_scene.h"
#include "file_formats/sdkmesh.h"
#include "file_formats/binscene.h"

#include "Scene.h"


namespace
{
	import_func_t& selectImporter(std::string_view ext)
	{
		if (ext == ".sdkmesh")
			return sdkmesh::read;
		else if (ext == ".obj")
			return obj::read;
		else if (ext == ".tris")
			return tris::read;
		else if (ext == ".candy")
			return candyscene::read;
		else if (ext == ".scene")
			return binscene::read;
		else
			throw std::runtime_error("unsupported file format");
	}


	struct MemoryBuffer
	{
		std::unique_ptr<char[]> data;
		std::size_t size;
	};

	MemoryBuffer readFile(const std::experimental::filesystem::path& filename)
	{
		std::ifstream in(filename, std::ios::binary);

		if (!in)
			throw std::runtime_error("unable to open file " + filename.u8string());

		in.seekg(0, std::ios::end);
		std::size_t file_size = in.tellg();
		auto buffer = core::make_unique_default<char[]>(file_size);

		in.seekg(0, std::ios::beg);
		in.read(&buffer[0], file_size);

		if (!in)
			throw std::runtime_error("error reading file " + filename.u8string());

		return { std::move(buffer), file_size };
	}
}






class AutotunerCalc : virtual SceneSink
{
	double result;
	uint32_t batchSize;

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override
	{
		if (num_surfaces > 1)
			std::cout << "WARNING: autotuning only on the first surface\n";
		result = VertexReuseStats::compute(false, batchSize, batchSize, indices + surfaces[0].start, surfaces[0].num_indices);
	}

public:

	template<class PROC, class... Args>
	double run(uint32_t batchSize, Scene& scene, Args... args)
	{
		this->batchSize = batchSize;
		PROC processor(*this, args...);
		Randi rn(processor);
		scene.process(rn);
		return result;
	}
};

int main(int argc, char* argv[])
{
	uint32_t batchSizes[] = {3 * 32, 3 * 64, 3 * 16};
	int32_t cacheWeights[] = { 1024, 64, 32, 4 };
	int32_t valenceWeights[] = { -16, -8, -4, -3, -2, -1, 0 };
	int32_t distanceWeights[] = { 16, 8, 4, 3, 2, 1, 0, -1, -2, -4 };
	int32_t batchNeighborWeights[] = { -16, -8, -4, -3, -2, -1, 0, 1, 2, 4};
	int32_t finPointWeights[] = { -16, -8, -4, -3, -2, -1, 0, 1, 2, 4 };

	if (argc < 2)
	{
		std::cout << "usage: autotuner <scenefile> [outfile]\n";
		return -1;
	}
	std::string outfile = std::string(argv[1]) + "_autotune.csv";
	if(argc > 2)
		outfile = argv[2];
	try
	{
		Scene scene;
		std::experimental::filesystem::path filename(argv[1]);
		import_func_t& import_func = selectImporter(filename.extension().u8string().c_str());
		std::cout << "loading file " << filename << std::endl;
		auto buffer = readFile(filename);
		scene.import(import_func, &buffer.data[0], buffer.size);

		std::ofstream out(outfile);
		out << "\"sep=;\"" << std::endl;
		out << "batchSize;cacheWeights;valenceWeights;distanceWeights;batchNeighborWeights;finPointWeights;" << std::endl;

		for(auto batchSize : batchSizes)
			for (auto cache : cacheWeights)
				for (auto valence : valenceWeights)
					for (auto distance : distanceWeights)
						for (auto neighbour : batchNeighborWeights)
							for (auto fin : finPointWeights)
							{
								AutotunerCalc tuner;
								double res = tuner.run<GBatchOptimizer>(batchSize, scene, batchSize, cache, valence, distance, neighbour, fin);
								out << batchSize << ";" << cache << ";" << valence << ";" << distance << ";" << neighbour << ";" << fin << ";" << res  << std::endl;
								out.flush();
								std::cout << batchSize << ";" << cache << ";" << valence << ";" << distance << ";" << neighbour << ";" << fin << ";" << res << std::endl;
							}
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
		return -1;
	}
	catch (...)
	{
		std::cout << "unknown error" << std::endl;
		return -128;
	}

	return 0;
}

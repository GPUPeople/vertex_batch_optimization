


#include <cstdint>
#include <memory>
#include <fstream>
#include <iostream>

#include <core/utils/memory>

#include "layers/ZFlip.h"
#include "layers/WindingOrderFlip.h"
#include "layers/Randi.h"
#include "layers/LinYuOptimizer.h"
#include "layers/HoppeOptimizer.h"
#include "layers/TomFOptimizer.h"
#include "layers/ModifiedTomFOptimizer.h"
#include "layers/BatchOptimizer.h"
#include "layers/GBatchOptimizer.h"
#include "layers/BatchEnumerator.h"
#include "layers/VertexReuseStats.h"
#include "layers/VertexCacheSimulation.h"
#include "layers/TipsifyOptimizer.h"
#include "layers/WeldVertices.h"
#include "layers/UnweldVertices.h"
#include "layers/Timing.h"
#include "layers/CentralVertexCacheSimulation.h"
#include "layers/LRUVertexCacheSimulation.h"

#include "file_formats/obj.h"
#include "file_formats/tris.h"
#include "file_formats/candy_scene.h"
#include "file_formats/sdkmesh.h"
#include "file_formats/binscene.h"

#include "SceneProcessor.h"


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

	using export_func_t = void(std::ostream& file, const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures);

	export_func_t& selectExporter(std::string_view ext)
	{
		if (ext == ".scene")
			return binscene::write;
		else if (ext == ".obj")
			return obj::write;
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


void SceneProcessor::addProcessingLayer(std::string_view name)
{
	if (name == "zflip")
		processing_layer = new ZFlip(*processing_layer);
	else if (name == "woflip")
		processing_layer = new WindingOrderFlip(*processing_layer);
	else if (name == "randi")
		processing_layer = new Randi(*processing_layer);
	else if (name.substr(0, strlen("linyu")) == "linyu")
		processing_layer = new LinYuOptimizer(*processing_layer, std::atoi(name.substr(strlen("linyu"), 10).data()));
	else if (name.substr(0, strlen("hoppe")) == "hoppe")
		processing_layer = new HoppeOptimizer(*processing_layer, std::atoi(name.substr(strlen("hoppe"), 10).data()));
	else if (name.substr(0, strlen("tipsify")) == "tipsify")
		processing_layer = new TipsifyOptimizer(*processing_layer, std::atoi(name.substr(strlen("tipsify"), 10).data()));
	else if (name == "tomf")
		processing_layer = new TomFOptimizer(*processing_layer);
	else if (name == "mtomf")
		processing_layer = new ModifiedTomFOptimizer(*processing_layer);
	else if (name == "sbatch")
		processing_layer = new BatchOptimizer(*processing_layer, 96, 96, 32);
	else if (name == "ssbatch")
		processing_layer = new BatchOptimizer(*processing_layer, 96, 96, -1);
	else if (name == "dbatch")
		processing_layer = new BatchOptimizer(*processing_layer, 1023, 256, -1);
	else if (name == "gbatch")
		processing_layer = new GBatchOptimizer(*processing_layer, VRS_NV_DX, 1024, -4, -1, 0, 0, true); //-4, -1, 1, 0)
	else if (name == "gbatchND")
		processing_layer = new GBatchOptimizer(*processing_layer, VRS_NV_DX, 1024, -3, 0, -3, 0, true); //-4, -1, 1, 0)

	else if (name == "gbatch.intel")
		processing_layer = new GBatchOptimizer(*processing_layer, VRS_INTEL_EXPERIMENTAL, 1024, -4, -1, 0, 0, false); //-4, -1, 1, 0)
	else if (name == "gbatchND.intel")
		processing_layer = new GBatchOptimizer(*processing_layer, VRS_INTEL_EXPERIMENTAL, 1024, -3, 0, -3, 0, false); //-4, -1, 1, 0)
	//else if (name == "gbatch.intel.NC")
	//	processing_layer = new GBatchOptimizer(*processing_layer, VRS_INTEL_EXPERIMENTAL, 1024, -4, -1, 0, 0, false); //-4, -1, 1, 0)
	//else if (name == "gbatchND.intel.NC")
	//	processing_layer = new GBatchOptimizer(*processing_layer, VRS_INTEL_EXPERIMENTAL, 1024, -3, 0, -3, 0, false); //-4, -1, 1, 0)

	else if (name == "gbatch.amd")
		processing_layer = new GBatchOptimizer(*processing_layer, VRS_ATI, 1024, -16, -1, 0, 0, false); //-4, -1, 1, 0)
	else if (name == "gbatchND.amd")
		processing_layer = new GBatchOptimizer(*processing_layer, VRS_ATI, 1024, -16, 0, -3, 0, false); //-4, -1, 1, 0)
	//else if (name == "gbatch.amd.NC")
	//	processing_layer = new GBatchOptimizer(*processing_layer, VRS_ATI, 1024, -4, -1, 0, 0, false); //-4, -1, 1, 0)
	//else if (name == "gbatchND.amd.NC")
	//	processing_layer = new GBatchOptimizer(*processing_layer, VRS_ATI, 1024, -3, 0, -3, 0, false); //-4, -1, 1, 0)

	//else if (name.substr(0, strlen("gbatchVAR")) == "gbatchVAR")
	//{
	//	std::size_t p1 = name.find_first_of('.');
	//	std::size_t p2 = name.find_first_of('.', p1+1);
	//	std::size_t p3 = name.find_first_of('.', p2+1);

	//	int asize = std::atoi(name.substr(p1+1, p2 - p1).data());
	//	int bsize = std::atoi(name.substr(p2+1, p3 - p2).data());
	//	int csize = std::atoi(name.substr(p3+1).data());
	//	processing_layer = new GBatchOptimizer(*processing_layer, asize, bsize, csize, 1024, -3, 0, -3, 0); //-4, -1, 1, 0)
	//}
	else if (name == "enumbatch")
		processing_layer = new BatchEnumerator(*processing_layer, 96, -1);
	else if (name.substr(0, strlen("vcs")) == "vcs")
	{
		bool output = false;
		int off = 0;
		if (name.find_first_of('+') != std::string::npos)
		{
			output = true;
			off = 1;
		}

		auto num_s = name.substr(strlen("vcs") + off, 10);
		int method = -1;
		if (num_s.size() > 0)
		{
			method = std::atoi(num_s.data());
			if (method > 5)
				method = -1;
		}
		processing_layer = new VertexReuseStats(*processing_layer, method, output);
	}
	else if (name.substr(0, strlen("ccachesim")) == "ccachesim")
	{
		bool output = false;
		int off = 0;
		if (name.find_first_of('+') != std::string::npos)
		{
			output = true;
			off = 1;
		}
		processing_layer = new CentralVertexCacheSimulation(*processing_layer, output, std::atoi(name.substr(strlen("ccachesim") + off, 10).data()));
	}
	else if (name.substr(0, strlen("LRUcachesim")) == "LRUcachesim")
	{
		bool output = false;
		int off = 0;
		if (name.find_first_of('+') != std::string::npos)
		{
			output = true;
			off = 1;
		}
		processing_layer = new LRUVertexCacheSimulation(*processing_layer, output, std::atoi(name.substr(strlen("LRUcachesim") + off, 10).data()));
	}
	else if (name == "vcachesim")
		processing_layer = new VertexCacheSimulation(*processing_layer);
	else if (name == "weld")
		processing_layer = new WeldVertices(*processing_layer);
	else if (name == "unweld")
		processing_layer = new UnweldVertices(*processing_layer);
	else
		throw std::runtime_error((std::string("unknown processing layer name: \"")+&name[0]+"\"").c_str());
}

void SceneProcessor::addTimingLayer()
{
		processing_layer = new Timing(*processing_layer, timings);
}
void SceneProcessor::addOutputLayer(const std::experimental::filesystem::path& filename)
{
	output_file_name = filename;
	perform_export = true;
}

void SceneProcessor::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	//std::cout << "writing scene file \"" << filename << "\"\n";
	std::cout << "\t" << num_vertices << " vertices\n";
	std::cout << "\t" << num_indices << " indices\n";
	std::cout << "\t" << num_surfaces << " surfaces\n";
	std::cout << "\t" << num_materials << " materials\n";
	std::cout << "\t" << num_textures << " textures\n";

	if (perform_export)
	{
		auto export_func = selectExporter(output_file_name.extension().u8string());

		std::ofstream file(output_file_name, std::ios::out | std::ios::binary);
		export_func(file, vertices, num_vertices, indices, num_indices, surfaces, num_surfaces, materials, num_materials, textures, num_textures);
	}
}

void SceneProcessor::ingestFrame(const std::experimental::filesystem::path& filename)
{
	import_func_t& import_func = selectImporter(filename.extension().u8string().c_str());

	auto buffer = readFile(filename);

	scene.importFrame(import_func, &buffer.data[0], buffer.size);
}

void SceneProcessor::ingest(const std::experimental::filesystem::path& filename)
{
	import_func_t& import_func = selectImporter(filename.extension().u8string().c_str());

	std::cout << "loading file " << filename << std::endl;

	auto buffer = readFile(filename);

	scene.import(import_func, &buffer.data[0], buffer.size);

	if (output_file_name.empty())
		(output_file_name = filename).replace_extension(".scene");
}

void SceneProcessor::process()
{
	scene.process(*processing_layer);
}

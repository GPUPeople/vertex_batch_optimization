


#include <exception>
#include <iostream>

#include "cmd_args.h"

#include "SceneProcessor.h"


int main(int argc, char* argv[])
{
	try
	{
		SceneProcessor scene_processor;

		parseArgs(scene_processor, argc - 1, argv + 1);

		scene_processor.process();
	}
	catch (const usage_error&)
	{
		printUsage(std::cout) << std::endl;
		return -1;
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

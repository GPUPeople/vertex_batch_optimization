


#include <cstdlib>
#include <cstring>
#include <string_view>
#include <iostream>

#include "SceneProcessor.h"

#include "cmd_args.h"


using namespace std::literals;


namespace
{
	const char* parseOption(const char* const *& args, std::string_view option)
	{
		if (**args == '-' && std::string_view(*args + 1, option.length()) == option)
			return *args + 1 + option.length();
		return nullptr;
	}

	const char* parseOptionArg(const char* arg, const char* const *& args, const char* default_value)
	{
		if (*arg)
			return arg;

		if (*(args + 1) && *(args + 2) && **(args + 1) != '-')
			return *++args;

		return default_value;
	}

	const char* parseOptionArg(const char* arg, const char* const *& args)
	{
		if (*arg)
			return arg;

		if (*(args + 1) && **(args + 1) != '-')
			return *++args;

		throw usage_error("expected argument");
	}
}

void parseArgs(SceneProcessor& processor, int argc, char* argv[])
{
	for (const char* const * a = argv; *a; ++a)
	{
		if (const char* target_file = parseOption(a, "o"sv))
			processor.addOutputLayer(parseOptionArg(target_file, a, ""));
		else if (const char* name = parseOption(a, "p"sv))
			processor.addProcessingLayer(parseOptionArg(name, a));
		else if (const char* source_file = parseOption(a, "f"sv))
			processor.ingestFrame(parseOptionArg(source_file, a));
		else if (*a == "-t"sv)
			processor.addTimingLayer();
		else if (**a == '-')
			throw usage_error("unknown argument");
		else
		{
			processor.ingest(*a);
		}
	}
}

std::ostream& printUsage(std::ostream& file)
{
	return file << "usage: sceneconverter [-o <target-file>] [{-p <processing-layer>}] {[-f] <source-file>}\n";
}

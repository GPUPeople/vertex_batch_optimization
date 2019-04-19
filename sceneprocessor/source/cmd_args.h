


#ifndef INCLUDED_CMD_ARGS
#define INCLUDED_CMD_ARGS

#include <stdexcept>
#include <iosfwd>


struct usage_error : std::runtime_error
{
	explicit usage_error(const std::string& msg)
		: runtime_error(msg)
	{
	}
};

class SceneProcessor;

void parseArgs(SceneProcessor& processor, int argc, char* argv[]);
std::ostream& printUsage(std::ostream& file);


#endif  // INCLUDED_CMD_ARGS




#ifndef INCLUDED_IO
#define INCLUDED_IO

#pragma once

#include <iostream>


class memory_istreambuf : public std::basic_streambuf<char>
{
public:
	memory_istreambuf(const char* buffer, std::size_t length)
	{
		char* b = const_cast<char*>(buffer);
		setg(b, b, b + length);
	}

	std::streampos seekoff(off_type off, std::ios_base::seekdir way, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
	{
		return std::streampos(gptr() - eback());
	}

	std::streampos seekpos(pos_type off, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
	{
		return std::streampos(gptr() - eback());
	}
};

#endif  // INCLUDED_IO

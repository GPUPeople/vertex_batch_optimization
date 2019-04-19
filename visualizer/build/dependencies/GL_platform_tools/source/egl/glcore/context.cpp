


#include <stdexcept>

#include "context.h"


namespace
{
	thread_local const glcoreContext* context = nullptr;
}

extern "C"
{
	glcoreContext::glcoreContext()
	{

		if ( == nullptr)
			return; // throw std::runtime_error("OpenGL IAT initialization failed");
	}

	const glcoreContext* glcoreContextInit()
	{
		return new glcoreContext;
	}
	
	void glcoreContextDestroy(const glcoreContext* ctx)
	{
		delete ctx;
	}
	
	void glcoreContextMakeCurrent(const glcoreContext* ctx)
	{
		context = ctx;
	}
	
	const glcoreContext* glcoreContextGetCurrent()
	{
		return context;
	}

}

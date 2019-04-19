


#ifndef INCLUDED_PLATFORM_X11_COLORMAP_HANDLE
#define INCLUDED_PLATFORM_X11_COLORMAP_HANDLE

#pragma once

#include <utility>

#include <x11/platform.h>


namespace X11
{
	class ColormapHandle
	{
		::Display* display;
		::Colormap colormap;

	public:
		ColormapHandle(const ColormapHandle&) = delete;
		ColormapHandle& operator =(const ColormapHandle&) = delete;

		ColormapHandle()
			: display(nullptr),
			  colormap(0)
		{
		}

		ColormapHandle(::Display* display, ::Colormap colormap)
			: display(display),
			  colormap(colormap)
		{
		}

		ColormapHandle(ColormapHandle&& cm)
			: display(cm.display),
			  colormap(cm.colormap)
		{
			cm.colormap = 0;
		}

		~ColormapHandle()
		{
			if (colormap)
				XFreeColormap(display, colormap);
		}

		ColormapHandle& operator =(ColormapHandle&& cm)
		{
			using std::swap;
			display = cm.display;
			swap(colormap, cm.colormap);
			return *this;
		}

		operator Colormap() const { return colormap; }
	};

	inline ColormapHandle createColorMap(::Display* display, ::Window window, ::Visual* visual, int alloc)
	{
		return ColormapHandle(display, XCreateColormap(display, window, visual, alloc));
	}
}

#endif  // INCLUDED_PLATFORM_X11_COLORMAP_HANDLE

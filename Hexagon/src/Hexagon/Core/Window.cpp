#include "hxpch.h"
#include "Hexagon/Core/Window.h"

#ifdef HX_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Hexagon
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef HX_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			HX_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}
#include "hxpch.h"
#include "Hexagon/Core/Input.h"

#ifdef HX_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Hexagon {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		#ifdef HX_PLATFORM_WINDOWS
			return CreateScope<WindowsInput>();
		#else
			HX_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}
#pragma once

#include <memory>

#ifdef HX_PLATFORM_WINDOWS
#if HX_DYNAMIC_LINK
	#ifdef HX_BUILD_DLL
		#define HEXAGON_API __declspec(dllexport)
	#else
		#define HEXAGON_API __declspec(dllimport)
	#endif
#else
	#define HEXAGON_API
#endif
#else
	#error Hazel only supports Windows!
#endif

#ifdef HX_DEBUG
	#define HX_ENABLE_ASSERTS
#endif

#ifdef HX_ENABLE_ASSERTS
	#define HX_ASSERT(x, ...) { if(!(x)) { HX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HX_CORE_ASSERT(x, ...) { if(!(x)) { HX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HX_ASSERT(x, ...)
	#define HX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hexagon 
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}

#pragma once

#include <memory>

// Platform Detection
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
	/* Windows x64  */
		#define HX_PLATFORM_WINDOWS
	#else
	/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define HX_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define HX_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define HX_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define HX_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif 

// DLL Support
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

// Debugging
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

// Misc
#define BIT(x) (1 << x)

#define HX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hexagon 
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
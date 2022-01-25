#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hexagon
{
	class HEXAGON_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		
	};
	
}

// Core log macros
#define HX_CORE_TRACE(...) ::Hexagon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HX_CORE_INFO(...)  ::Hexagon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HX_CORE_WARN(...)  ::Hexagon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HX_CORE_ERROR(...) ::Hexagon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HX_CORE_FATAL(...) ::Hexagon::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HX_TRACE(...)      ::Hexagon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HX_INFO(...)       ::Hexagon::Log::GetClientLogger()->info(__VA_ARGS__)
#define HX_WARN(...)       ::Hexagon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HX_ERROR(...)      ::Hexagon::Log::GetClientLogger()->error(__VA_ARGS__)
#define HX_FATAL(...)      ::Hexagon::Log::GetClientLogger()->critical(__VA_ARGS__)
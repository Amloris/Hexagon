// Wrapper for a logging library

#include "hxpch.h"

#include "Hexagon/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Hexagon
{

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%Y-%m-%d %T.%e] %n: %v%$");      // Sets color, timestamp, logger name, and then logger message

		s_CoreLogger = spdlog::stdout_color_mt("HEXAGON");
		s_CoreLogger->set_level(spdlog::level::trace);           // Todo: Expose log level

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}

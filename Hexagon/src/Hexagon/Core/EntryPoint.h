#pragma once

#include "Hexagon/Core/Core.h"

#ifdef HX_PLATFORM_WINDOWS

extern Hexagon::Application* Hexagon::CreateApplication();

int main(int argc, char** argv)
{
	Hexagon::Log::Init();
	HX_CORE_WARN("Initialized Log!");

	HX_PROFILE_BEGIN_SESSION("Startup", "HexagonProfile-Startup.json");
	auto app = Hexagon::CreateApplication();
	HX_PROFILE_END_SESSION();

	HX_PROFILE_BEGIN_SESSION("Runtime", "HexagonProfile-Runtime.json");
	app->Run();
	HX_PROFILE_END_SESSION();

	HX_PROFILE_BEGIN_SESSION("Shutdown", "HexagonProfile-Shutdown.json");
	delete app;
	HX_PROFILE_END_SESSION();

}

#endif
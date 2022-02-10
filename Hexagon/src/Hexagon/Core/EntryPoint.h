#pragma once

#include "Hexagon/Core/Core.h"

#ifdef HX_PLATFORM_WINDOWS

extern Hexagon::Application* Hexagon::CreateApplication();

int main(int argc, char** argv)
{
	Hexagon::Log::Init();
	HX_CORE_WARN("Initialized Log!");                   //Equivalent to Hexagon::Log::GetCoreLogger()->warn("Initialized Log!");

	auto app = Hexagon::CreateApplication();
	app->Run();
	delete app;
}

#endif
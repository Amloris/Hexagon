#pragma once

#ifdef HX_PLATFORM_WINDOWS

extern Hexagon::Application* Hexagon::CreateApplication();

int main(int argc, char** argv)
{
	Hexagon::Log::Init();
	HX_CORE_WARN("Initialized Log!");                   //Equivalent to Hexagon::Log::GetCoreLogger()->warn("Initialized Log!");
	int a{ 5 };
	HX_INFO("Hello! Var={0}", a);                                  //Equivalent to Hexagon::Log::GetClientLogger()->info("Hello!");

	auto app = Hexagon::CreateApplication();
	app->Run();
	delete app;
}

#endif
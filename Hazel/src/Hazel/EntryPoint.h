#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");                   //Equivalent to Hazel::Log::GetCoreLogger()->warn("Initialized Log!");
	int a{ 5 };
	HZ_INFO("Hello! Var={0}", a);                                  //Equivalent to Hazel::Log::GetClientLogger()->info("Hello!");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif
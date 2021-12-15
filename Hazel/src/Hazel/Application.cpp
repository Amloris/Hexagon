#include "hzpch.h"

#include "Application.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel {


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		HZ_CORE_TRACE("{0}", e);  //Log all events

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	}


	void Application::Run()
	{

		while (m_Running)
		{

			glClearColor(0.1875, .0391, .1406, 0.8);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

}

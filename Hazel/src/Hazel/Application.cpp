#include "hzpch.h"

#include "Application.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

#include "Input.h"

namespace Hazel {


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		//HZ_CORE_TRACE("{0}", e);  //Log all events

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )     // Handle events from the top down
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	void Application::Run()
	{

		while (m_Running)
		{

			glClearColor(0.1875f, 0.0391f, 0.1406f, 0.8f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImguiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();


			/*
			auto [x, y] = Input::GetMousePosition();
			HZ_CORE_TRACE("{0}, {1}", x, y);

			bool state = Input::IsMouseButtonPressed(0);
			state == true ? HZ_CORE_TRACE("Mouse Button 1: (Pressed)") : HZ_CORE_TRACE("Mouse Button 1: (Not Pressed)");

			bool spacePressed = Input::IsKeyPressed(32);
			spacePressed == true ? HZ_CORE_TRACE("Spacebar: (Pressed)") : HZ_CORE_TRACE("Spacebar: (Not Pressed)");
			*/
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

}

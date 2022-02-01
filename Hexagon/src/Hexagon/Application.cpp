#include "hxpch.h"

#include "Application.h"
#include "Hexagon/Log.h"
#include "Renderer/Renderer.h"

//#include "Input.h"

// Temporary
#include <GLFW/glfw3.h>  



namespace Hexagon {


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
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
		//HX_CORE_TRACE("{0}", e);  //Log all events

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
			float time = (float)glfwGetTime();  // TODO: put in Platform::GetTime 
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Layers
			// -------------------------------------------------------------------------
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImguiRender();
			}
			m_ImGuiLayer->End();

			// Windows
			// -------------------------------------------------------------------------
			m_Window->OnUpdate();

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

}

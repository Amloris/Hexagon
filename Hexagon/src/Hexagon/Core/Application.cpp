#include "hxpch.h"

#include "Hexagon/Core/Application.h"
#include "Hexagon/Core/Log.h"
#include "Hexagon/Renderer/Renderer.h"

// Temporary
#include <GLFW/glfw3.h>  

namespace Hexagon 
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HX_PROFILE_FUNCTION();

		HX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(HX_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		HX_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		HX_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		HX_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		HX_PROFILE_FUNCTION();

		//HX_CORE_TRACE("{0}", e);  //Log all events

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HX_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HX_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )     // Handle events from the top down
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	void Application::Run()
	{
		HX_PROFILE_FUNCTION();

		while (m_Running)
		{
			HX_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();  // TODO: put in Platform::GetTime 
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Layers
			// -------------------------------------------------------------------------
			if (!m_Minimized)
			{
				HX_PROFILE_SCOPE("Application::Run - LayerStack OnUpdates");

				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			{
				HX_PROFILE_SCOPE("Application::Run - ImGui LayerStack Updates");

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack) {
					layer->OnImguiRender();
				}
				m_ImGuiLayer->End();
			}

			// Windows
			// -------------------------------------------------------------------------
			m_Window->OnUpdate();

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		HX_PROFILE_FUNCTION();

		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		HX_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}

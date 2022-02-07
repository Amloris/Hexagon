#pragma once

#include "Core.h"

#include "Window.h"
#include "Hexagon/Core/LayerStack.h"
#include "Hexagon/Events/Event.h"
#include "Hexagon/Events/ApplicationEvent.h"

#include "Hexagon/Core/Timestep.h"

#include "Hexagon/ImGui/ImGuiLayer.h"

namespace Hexagon {

	class HEXAGON_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT	
	Application* CreateApplication();

}


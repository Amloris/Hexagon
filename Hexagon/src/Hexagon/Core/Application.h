#pragma once

#include "Hexagon/Core/Core.h"

#include "Hexagon/Core/Window.h"
#include "Hexagon/Core/LayerStack.h"
#include "Hexagon/Events/Event.h"
#include "Hexagon/Events/ApplicationEvent.h"

#include "Hexagon/Core/Timestep.h"

#include "Hexagon/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Hexagon {

	class  Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		void Run();
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
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT	
	Application* CreateApplication();

}


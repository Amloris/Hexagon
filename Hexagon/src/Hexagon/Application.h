#pragma once

#include "Core.h"

#include "Window.h"
#include "Hexagon/LayerStack.h"
#include "Hexagon/Events/Event.h"
#include "Hexagon/Events/ApplicationEvent.h"

#include "Hexagon/ImGui/ImGuiLayer.h"

#include "Hexagon/Renderer/Shader.h"
#include "Hexagon/Renderer/Buffer.h"


namespace Hexagon {

	class HEXAGON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT	
	Application* CreateApplication();

}


#pragma once

#include "Core.h"

#include "Window.h"
#include "Hexagon/LayerStack.h"
#include "Hexagon/Events/Event.h"
#include "Hexagon/Events/ApplicationEvent.h"

#include "Hexagon/ImGui/ImGuiLayer.h"

#include "Hexagon/Renderer/Buffer.h"
#include "Hexagon/Renderer/Shader.h"
#include "Hexagon/Renderer/VertexArray.h"
#include "Hexagon/Renderer/OrthographicCamera.h"


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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;


		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<VertexArray> m_SquareVertexArray;
		std::shared_ptr<Shader> m_SquareShader;

		OrthographicCamera m_Camera;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT	
	Application* CreateApplication();

}


#include "hxpch.h"

#include <glad/glad.h>

#include "Application.h"
#include "Hazel/Log.h"

#include "Input.h"

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

		// Vertex Array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		

		float vertices[3 * 6] = {
			// Positions         // Colors 
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
		};

		// Vertex Buffer
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		//m_VertexBuffer->Bind();

		// Position Attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// Color Attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		// Index buffer


		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

		// Shader
		std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec3 aColor;
			out vec3 ourColor;
			void main()
			{
			   gl_Position = vec4(aPos, 1.0);
			   ourColor = aColor;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			out vec4 FragColor;
			in vec3 ourColor;
			void main()
			{
				FragColor = vec4(ourColor, 1.0f);
			}
		)";
;
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
			glClearColor(0.1875f, 0.0391f, 0.1406f, 0.8f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);


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
			HX_CORE_TRACE("{0}, {1}", x, y);

			bool state = Input::IsMouseButtonPressed(0);
			state == true ? HX_CORE_TRACE("Mouse Button 1: (Pressed)") : HX_CORE_TRACE("Mouse Button 1: (Not Pressed)");

			bool spacePressed = Input::IsKeyPressed(32);
			spacePressed == true ? HX_CORE_TRACE("Spacebar: (Pressed)") : HX_CORE_TRACE("Spacebar: (Not Pressed)");
			*/
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

}

#include "hxpch.h"

#include "Application.h"
#include "Hexagon/Log.h"
#include "Renderer/Renderer.h"

//#include "Input.h"

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
		m_VertexArray.reset(VertexArray::Create());

		// Vertex Buffer
		float vertices[3 * 7] = {
			// Positions         // Colors 
			-0.5f, -0.5f, 0.0f,  0.8f, 0.2f, 0.2f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.2f, 0.8f, 0.3f, 1.0f,
			 0.0f,  0.5f, 0.0f,  0.2f, 0.3f, 0.8f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "aPos"},
			{ ShaderDataType::Float4, "aColor"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Index buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//Testing Square
		m_SquareVertexArray.reset(VertexArray::Create());
		float squareVertices[3 * 4] = {
			// Positions         // Colors 
			-0.75f, -0.75f, 0.0f,  
			 0.75f, -0.75f, 0.0f,  
			 0.75f,  0.75f, 0.0f,  
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<VertexBuffer> SquareVertexBuffer;
		SquareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		SquareVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "aPos"},
			});
		m_SquareVertexArray->AddVertexBuffer(SquareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> SquareIndexBuffer;
		SquareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(SquareIndexBuffer);

		// Shader
		std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 aColor;
			out vec4 ourColor;
			void main()
			{
			   gl_Position = vec4(aPos, 1.0);
			   ourColor = aColor;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			out vec4 FragColor;
			in vec4 ourColor;
			void main()
			{
				FragColor = vec4(ourColor);
			}
		)";
;
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		//Shader Square
		std::string SquareVertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;

			out vec3 vPos;

			void main()
			{
				vPos = aPos;
				gl_Position = vec4(aPos, 1.0);
			}
		)";

		std::string SquareFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPos;

			void main()
			{
				color = vec4(vPos * 0.5 + 0.5, 1.0);
			}
		)";
		;
		m_SquareShader.reset(new Shader(SquareVertexSrc, SquareFragmentSrc));
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

			// Render Commands
			// -------------------------------------------------------------------------
			const glm::vec4 colorUbuntuTerminal = { 0.1875f, 0.0391f, 0.1406f, 0.8f };
			RenderCommand::SetClearColor(colorUbuntuTerminal);
			RenderCommand::Clear();

			Renderer::BeginScene();
			{
				m_SquareShader->Bind();
				Renderer::Submit(m_SquareVertexArray);
				m_Shader->Bind();
				Renderer::Submit(m_VertexArray);
			}
			Renderer::EndScene();
	
			// Layers
			// -------------------------------------------------------------------------
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImguiRender();
			}
			m_ImGuiLayer->End();

			// Windows
			// -------------------------------------------------------------------------
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

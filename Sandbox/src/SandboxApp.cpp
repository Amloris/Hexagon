#include "Hexagon.h"

#include "imgui/imgui.h"

class ExampleLayer: public Hexagon::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) 
	{
		// Vertex Array
		m_VertexArray.reset(Hexagon::VertexArray::Create());

		// Vertex Buffer
		float vertices[3 * 7] = {
			// Positions         // Colors 
			-0.5f, -0.5f, 0.0f,  0.8f, 0.2f, 0.2f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.2f, 0.8f, 0.3f, 1.0f,
			 0.0f,  0.5f, 0.0f,  0.2f, 0.3f, 0.8f, 1.0f,
		};

		std::shared_ptr<Hexagon::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hexagon::VertexBuffer::Create(vertices, sizeof(vertices)));

		Hexagon::BufferLayout layout = {
			{ Hexagon::ShaderDataType::Float3, "aPos"},
			{ Hexagon::ShaderDataType::Float4, "aColor"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Index buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Hexagon::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hexagon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//Testing Square
		m_SquareVertexArray.reset(Hexagon::VertexArray::Create());
		float squareVertices[3 * 4] = {
			// Positions         // Colors 
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Hexagon::VertexBuffer> SquareVertexBuffer;
		SquareVertexBuffer.reset(Hexagon::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		SquareVertexBuffer->SetLayout({
			{ Hexagon::ShaderDataType::Float3, "aPos"},
			});
		m_SquareVertexArray->AddVertexBuffer(SquareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Hexagon::IndexBuffer> SquareIndexBuffer;
		SquareIndexBuffer.reset(Hexagon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(SquareIndexBuffer);

		// Shader
		std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 aColor;

			uniform mat4 u_ViewProjection;

			out vec4 ourColor;
			void main()
			{
			   gl_Position = u_ViewProjection * vec4(aPos, 1.0);
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
		m_Shader.reset(new Hexagon::Shader(vertexSrc, fragmentSrc));

		//Shader Square
		std::string SquareVertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;

			uniform mat4 u_ViewProjection;

			out vec3 vPos;

			void main()
			{
				vPos = aPos;
				gl_Position = u_ViewProjection * vec4(aPos, 1.0);
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
		m_SquareShader.reset(new Hexagon::Shader(SquareVertexSrc, SquareFragmentSrc));
	}

	void OnUpdate() override
	{
		// Camera Control
		if (Hexagon::Input::IsKeyPressed(HX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_Q))
			m_CameraRotation += m_CameraRotateSpeed;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_E))
			m_CameraRotation -= m_CameraRotateSpeed;


		// Render Commands
		// -------------------------------------------------------------------------
		const glm::vec4 colorUbuntuTerminal = { 0.1875f, 0.0391f, 0.1406f, 0.8f };
		Hexagon::RenderCommand::SetClearColor(colorUbuntuTerminal);
		Hexagon::RenderCommand::Clear();

		Hexagon::Renderer::BeginScene(m_Camera);
		{
			m_Camera.setPosition(m_CameraPosition);
			m_Camera.setRotation(m_CameraRotation);

			Hexagon::Renderer::Submit(m_SquareShader, m_SquareVertexArray);
			Hexagon::Renderer::Submit(m_Shader, m_VertexArray);
		}
		Hexagon::Renderer::EndScene();

	}

	virtual void OnImguiRender() override 
	{
		ImGui::Begin("FPS");
		ImGui::Text("Hello, world!");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0 / double(ImGui::GetIO().Framerate), double(ImGui::GetIO().Framerate));
		ImGui::End();
	}

	void OnEvent(Hexagon::Event& event) override
	{
	}


private:
	std::shared_ptr<Hexagon::VertexArray> m_VertexArray;
	std::shared_ptr<Hexagon::Shader> m_Shader;

	std::shared_ptr<Hexagon::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Hexagon::Shader> m_SquareShader;

	Hexagon::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
	float m_CameraRotation = 0.0f;

	float m_CameraMoveSpeed = 0.01f;
	float m_CameraRotateSpeed = 0.1f;

};

class TestLayer : public Hexagon::Layer
{
public:
	TestLayer()
		: Layer("Test") {}

	virtual void OnImguiRender() override {
		ImGui::Begin("2 Weeks");
		ImGui::Text("Apache Development Schedule");
		ImGui::End();
	}

};

class Sandbox : public Hexagon::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
		PushLayer(new TestLayer);
	}

	~Sandbox()
	{
		
	}

};


Hexagon::Application* Hexagon::CreateApplication()
{
	return new Sandbox();
}
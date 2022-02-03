#include "Hexagon.h"

#include <glm/gtc/matrix_transform.hpp>   // Temporary
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/include/GLFW/glfw3.h>      // Temporary
#include "Platform/OpenGL/OpenGLShader.h" // Temporary

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

		Hexagon::Ref<Hexagon::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hexagon::VertexBuffer::Create(vertices, sizeof(vertices)));

		Hexagon::BufferLayout layout = {
			{ Hexagon::ShaderDataType::Float3, "aPos"},
			{ Hexagon::ShaderDataType::Float4, "aColor"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Index buffer
		uint32_t indices[3] = { 0, 1, 2 };
		Hexagon::Ref<Hexagon::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hexagon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//Testing Square
		m_SquareVertexArray.reset(Hexagon::VertexArray::Create());
		float squareVertices[5 * 4] = {
			// Positions         // Colors 
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Hexagon::Ref<Hexagon::VertexBuffer> SquareVertexBuffer;
		SquareVertexBuffer.reset(Hexagon::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		SquareVertexBuffer->SetLayout({
			{ Hexagon::ShaderDataType::Float3, "aPos"},
			{ Hexagon::ShaderDataType::Float2, "aTexCoord"},
			});
		m_SquareVertexArray->AddVertexBuffer(SquareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Hexagon::Ref<Hexagon::IndexBuffer> SquareIndexBuffer;
		SquareIndexBuffer.reset(Hexagon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(SquareIndexBuffer);

		// Shader
		std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 aColor;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 ourColor;
			void main()
			{
			   gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
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
		
		m_Shader.reset(Hexagon::Shader::Create(vertexSrc, fragmentSrc));

		//Shader Square
		std::string flatColorVertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 vPos;

			void main()
			{
				vPos = aPos;
				gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
			}
		)";

		std::string FlatColorFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPos;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";
		
		m_FlatColorShader.reset(Hexagon::Shader::Create(flatColorVertexSrc, FlatColorFragmentSrc));

		// Texture Shader
		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec2 aTexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;


			void main()
			{
				v_TexCoord = aTexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Hexagon::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
		m_Texture= Hexagon::Texture2D::Create("assets/textures/Checkerboard_UV.png");
		m_ChernoLogoTexture = Hexagon::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Hexagon::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Hexagon::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Hexagon::Timestep timestep) override
	{
		//HX_TRACE("Delta Time: {0}s, ({1}ms)", timestep.GetSeconds(), timestep.GetMilliseconds());

		// Camera Control
		if (Hexagon::Input::IsKeyPressed(HX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_Q))
			m_CameraRotation += m_CameraRotateSpeed * timestep;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_E))
			m_CameraRotation -= m_CameraRotateSpeed * timestep;

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		// Render Commands
		// -------------------------------------------------------------------------
		const glm::vec4 colorUbuntuTerminal = { 0.1875f, 0.0391f, 0.1406f, 0.8f };
		Hexagon::RenderCommand::SetClearColor(colorUbuntuTerminal);
		Hexagon::RenderCommand::Clear();

		m_Camera.setPosition(m_CameraPosition);
		m_Camera.setRotation(m_CameraRotation);

		Hexagon::Renderer::BeginScene(m_Camera);

		{
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			std::dynamic_pointer_cast<Hexagon::OpenGLShader>(m_FlatColorShader)->Bind();
			std::dynamic_pointer_cast<Hexagon::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

			float shift{ 0.11f };
			for (int x = 0; x < 20; x++) {
				for (int y = 0; y < 20; y++) {
					glm::vec3 pos(x * shift, y * shift, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Hexagon::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
				}
			}
		}

		m_Texture->Bind();
		Hexagon::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		m_ChernoLogoTexture->Bind();
		Hexagon::Renderer::Submit(m_TextureShader, m_SquareVertexArray, 
			glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle 
		//Hexagon::Renderer::Submit(m_Shader, m_VertexArray);
		
		Hexagon::Renderer::EndScene();
	}

	virtual void OnImguiRender() override 
	{
		// Application Information
		Hexagon::Application& app = Hexagon::Application::Get();
		unsigned int windowWidth = app.GetWindow().GetWidth();
		unsigned int windowHeight = app.GetWindow().GetHeight();

		auto [mousePosX, mousePosY] = Hexagon::Input::GetMousePosition();
		HX_INFO("Mouse Position: {0}, {1}", mousePosX, mousePosY);

		ImGui::Begin("Hexagon Info");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0 / double(ImGui::GetIO().Framerate), double(ImGui::GetIO().Framerate));
		ImGui::Text("Width: %i, Height: %i", windowWidth, windowHeight);
		ImGui::Text("       %i,         %i", (int)mousePosX, (int)mousePosY);
		ImGui::End();

		// Imgui Color Picker
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();


	}

	void OnEvent(Hexagon::Event& event) override
	{
		Hexagon::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Hexagon::WindowResizeEvent>(HX_BIND_EVENT_FN(ExampleLayer::OnWindowResizeEvent));
	}

	bool OnWindowResizeEvent(Hexagon::WindowResizeEvent& event) 
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return true;
	}


private:
	Hexagon::Ref<Hexagon::Shader> m_Shader;
	Hexagon::Ref<Hexagon::VertexArray> m_VertexArray;

	Hexagon::Ref<Hexagon::Shader> m_FlatColorShader, m_TextureShader;
	Hexagon::Ref<Hexagon::VertexArray> m_SquareVertexArray;
	
	Hexagon::Ref<Hexagon::Texture2D> m_Texture, m_ChernoLogoTexture;

	Hexagon::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
	float m_CameraRotation = 0.0f;

	float m_CameraMoveSpeed = 0.5f;
	float m_CameraRotateSpeed = 10.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

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
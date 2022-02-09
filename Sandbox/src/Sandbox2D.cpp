#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h" // Temporary

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sandbox2D::Sandbox2D()
	: m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	//Testing Square
	m_SquareVertexArray = Hexagon::VertexArray::Create();
	float squareVertices[3 * 4] = {
		// Positions
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	Hexagon::Ref<Hexagon::VertexBuffer> SquareVertexBuffer;
	SquareVertexBuffer = Hexagon::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	SquareVertexBuffer->SetLayout({
		{ Hexagon::ShaderDataType::Float3, "aPos"},
	});
	m_SquareVertexArray->AddVertexBuffer(SquareVertexBuffer);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Hexagon::Ref<Hexagon::IndexBuffer> SquareIndexBuffer;
	SquareIndexBuffer = Hexagon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVertexArray->SetIndexBuffer(SquareIndexBuffer);

	m_FlatColorShader = Hexagon::Shader::Create("assets/Shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hexagon::Timestep timestep)
{
	// Update
	// -------------------------------------------------------------------------
	m_CameraController.OnUpdate(timestep);

	// Render Commands
	// -------------------------------------------------------------------------
	const glm::vec4 colorUbuntuTerminal = { 0.1875f, 0.0391f, 0.1406f, 0.8f };
	Hexagon::RenderCommand::SetClearColor(colorUbuntuTerminal);
	Hexagon::RenderCommand::Clear();

	Hexagon::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Hexagon::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Hexagon::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	m_FlatColorShader->Bind();
	Hexagon::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Hexagon::Renderer::EndScene();
}

void Sandbox2D::OnImguiRender()
{
	// Imgui Color Picker
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hexagon::Event& event)
{
	// Camera
	// -------------------------------------------------------------------------
	m_CameraController.OnEvent(event);
}
#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sandbox2D::Sandbox2D()
	: m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	//m_Texture = Hexagon::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Texture = Hexagon::Texture2D::Create("assets/textures/Checkerboard_UV.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hexagon::Timestep timestep)
{
	HX_PROFILE_FUNCTION();

	// Update
	// -------------------------------------------------------------------------
	{
		HX_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}
	// Render Commands
	// -------------------------------------------------------------------------
	{
		HX_PROFILE_SCOPE("Render Prep");
		const glm::vec4 colorUbuntuTerminal = { 0.1875f, 0.0391f, 0.1406f, 0.8f };
		Hexagon::RenderCommand::SetClearColor(colorUbuntuTerminal);
		Hexagon::RenderCommand::Clear();
	}

	{
		HX_PROFILE_SCOPE("Renderer Draw");
		Hexagon::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hexagon::Renderer2D::DrawQuad({ -0.5f, -0.2f }, { 1.5f, 1.0f }, m_SquareColor);
		Hexagon::Renderer2D::DrawQuad({ 0.5f, 0.5f, 0.1f }, { 1.0f, 1.5f }, { 0.2f, 0.8f, 0.3f, 0.8f });
		Hexagon::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, 10.0f, { 0.5f, 0.5f, 1.0f, 0.9f });
		Hexagon::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImguiRender()
{
	HX_PROFILE_FUNCTION();

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
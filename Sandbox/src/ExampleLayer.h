#pragma once

#include "Hexagon.h"

class ExampleLayer : public Hexagon::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hexagon::Timestep timestep) override;
	virtual void OnImguiRender() override;
	void OnEvent(Hexagon::Event& event) override;
private:
	Hexagon::ShaderLibrary m_shaderLibrary;

	Hexagon::Ref<Hexagon::Shader> m_Shader;
	Hexagon::Ref<Hexagon::VertexArray> m_VertexArray;

	Hexagon::Ref<Hexagon::Shader> m_FlatColorShader;
	Hexagon::Ref<Hexagon::VertexArray> m_SquareVertexArray;

	Hexagon::Ref<Hexagon::Texture2D> m_Texture, m_ChernoLogoTexture, m_BruhTexture;

	Hexagon::OrthographicCameraController m_CameraController;


	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
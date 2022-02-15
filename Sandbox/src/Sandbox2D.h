#pragma once

#include "Hexagon.h"

class Sandbox2D : public Hexagon::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hexagon::Timestep timestep) override;
	virtual void OnImguiRender() override;
	void OnEvent(Hexagon::Event& event) override;
private:
	Hexagon::OrthographicCameraController m_CameraController;

	//Temporary
	Hexagon::Ref<Hexagon::VertexArray> m_SquareVertexArray;
	Hexagon::Ref<Hexagon::Shader> m_FlatColorShader;

	Hexagon::Ref<Hexagon::Texture2D> m_Texture;

	struct ProfileResult
	{
		const char* name;
		float time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
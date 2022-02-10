#include <Hexagon.h>
#include <Hexagon/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>   // Temporary
#include <glm/gtc/type_ptr.hpp>

#include "ExampleLayer.h"
#include "Sandbox2D.h"


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
		//PushLayer(new ExampleLayer);
		//PushLayer(new TestLayer);
		PushLayer(new Sandbox2D);
	}

	~Sandbox()
	{
		
	}

};


Hexagon::Application* Hexagon::CreateApplication()
{
	return new Sandbox();
}
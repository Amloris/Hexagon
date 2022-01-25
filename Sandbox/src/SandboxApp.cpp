#include "Hexagon.h"

#include "imgui/imgui.h"

class ExampleLayer: public Hexagon::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//HZ_INFO("ExampleLayer::Update");

		if (Hexagon::Input::IsKeyPressed(HX_KEY_TAB))
			HX_TRACE("Tab key is pressed! (Poll)");

	}

	virtual void OnImguiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	 }

	void OnEvent(Hexagon::Event& event) override
	{
		//HZ_TRACE("{0}", event);

		if (event.GetEventType() == Hexagon::EventType::KeyPressed)
		{
			Hexagon::KeyPressedEvent& e = (Hexagon::KeyPressedEvent&)event;
			if (Hexagon::Input::IsKeyPressed(HX_KEY_TAB))
				HX_TRACE("Tab key is pressed! (Event)");
			HX_INFO("Key Pressed: {0}", (char)e.GetKeyCode());
		}
	}

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
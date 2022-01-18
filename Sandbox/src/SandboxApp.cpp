#include "Hazel.h"

#include "imgui/imgui.h"

class ExampleLayer: public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//HZ_INFO("ExampleLayer::Update");

		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_TRACE("Tab key is pressed! (Poll)");

	}

	virtual void OnImGuiRender() {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	 }

	void OnEvent(Hazel::Event& event) override
	{
		//HZ_TRACE("{0}", event);

		if (event.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
				HZ_TRACE("Tab key is pressed! (Event)");
			HZ_INFO("Key Pressed: {0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
	}

	~Sandbox()
	{
		
	}

};


Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
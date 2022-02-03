Hexagon Engine
====
### Building Hexagon
1. git clone --recurse-submodules https://github.com/Amloris/Hexagon.git
2. add premake5.lua files to the git submodules
3. modify GenerateProjects.batch as necessary

### Input Examples
Polling
```cpp
void OnUpdate() override {
	if (Hexagon::Input::IsKeyPressed(HX_KEY_TAB))
		HX_INFO("Tab key is pressed! (Poll)"); 

	auto [x, y] = Input::GetMousePosition();
	HX_INFO("Mouse Position: {0}, {1}", x, y);

	bool state = Input::IsMouseButtonPressed(0);
	state == true ? HX_INFO("Mouse Button 1: (Pressed)") : HX_INFO("Mouse Button 1: (Not Pressed)");

	bool spacePressed = Input::IsKeyPressed(32);
	spacePressed == true ? HX_INFO("Spacebar: (Pressed)") : HX_INFO("Spacebar: (Not Pressed)");
}
```

Events
```cpp
void OnEvent(Hexagon::Event& event) override
{
	if (event.GetEventType() == Hexagon::EventType::KeyPressed)
	{
		Hexagon::KeyPressedEvent& e = (Hexagon::KeyPressedEvent&)event;
		if (Hexagon::Input::IsKeyPressed(HX_KEY_TAB))
			HX_INFO("Tab key is pressed! (Event)");
		HX_INFO("Key Pressed: {0}", (char)e.GetKeyCode());
	}
}
```

### Imgui Examples
Simple Window
```cpp
virtual void OnImguiRender() override {
	ImGui::Begin("Test");
	ImGui::Text("Hello World");
	ImGui::End();
	}
```

### Event Dispatching
Events can be dispatched to other functions.  Once those functions have been completed, they can mark the event as handled or not.  This can be used to prevent other layers or functions from acting on events that have already been dealt with.
```cpp
void OnEvent(Hexagon::Event& event) override
{
	Hexagon::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Hexagon::KeyPressedEvent>(HX_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	dispatcher.Dispatch<Hexagon::KeyPressedEvent>(HX_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent2));
}

bool OnKeyPressedEvent(Hexagon::KeyPressedEvent& event) {
	if (event.GetKeyCode() == HX_KEY_TAB) {} // Do Something

	event.Handled() == true ? HX_INFO("Handled") : HX_INFO("Not Handled");
	return true;
}

bool OnKeyPressedEvent2(Hexagon::KeyPressedEvent& event) {

	event.Handled() == true ? HX_INFO("Handled") : HX_INFO("Not Handled");
	return true;
}
```
Output:
```
[2022-01-31 19:21:15.144] APP: Not Handled
[2022-01-31 19:21:15.144] APP: Handled
```

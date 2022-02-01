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

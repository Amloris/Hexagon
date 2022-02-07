#pragma once

#include "hxpch.h"

#include "Hexagon/Core/Core.h"
#include "Hexagon/Events/Event.h"

namespace Hexagon
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hexagon Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			:Title(title), Width(width), Height(height) {}
	};

	// Interface representing a desktop system based on Window
	class HEXAGON_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth()  const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVsyc() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());       //If you don't specify the window parameters is uses the default
	};


}
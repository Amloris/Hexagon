// Todo: Add a OnEnable() function.  When enabled the layer will receive updates, when it is disabled it will not be updated every frame

#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hexagon
{
	class HEXAGON_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImguiRender() {};
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
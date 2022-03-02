// Todo: Add a OnEnable() function.  When enabled the layer will receive updates, when it is disabled it will not be updated every frame

#pragma once

#include "Hexagon/Core/Core.h"
#include "Hexagon/Core/Timestep.h"
#include "Hexagon/Events/Event.h"

namespace Hexagon
{
	class  Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImguiRender() {};
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
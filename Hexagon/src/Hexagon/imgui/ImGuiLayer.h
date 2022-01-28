#pragma once

#include "Hexagon/Layer.h"

#include "Hexagon/Events/ApplicationEvent.h"
#include "Hexagon/Events/KeyEvent.h"
#include "Hexagon/Events/MouseEvent.h"

namespace Hexagon
{
	class HEXAGON_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach()      override;
		virtual void OnDetach()	     override;
		virtual void OnImguiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}
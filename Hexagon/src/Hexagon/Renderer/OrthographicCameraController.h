#pragma once

#include "Hexagon/Core/Timestep.h"
#include "Hexagon/Renderer/OrthographicCamera.h"

#include "Hexagon/Events/ApplicationEvent.h"
#include "Hexagon/Events/MouseEvent.h"

namespace Hexagon
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool allowRotation = true);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool m_AllowRotation;

		OrthographicCamera m_Camera;


		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction

		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 90.0;

	};


}

#include "hxpch.h"

#include "Hexagon/Renderer/OrthographicCameraController.h"

#include "Hexagon/Core/Input.h"
#include "Hexagon/Core/KeyCodes.h"
#include "Hexagon/Core/MouseCodes.h"
#include "Hexagon/Events/KeyEvent.h"

namespace Hexagon
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool allowRotation)
		:m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
			m_AspectRatio(aspectRatio), 
			m_AllowRotation(allowRotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		HX_PROFILE_FUNCTION();

		// Camera Control
		float distanceStep = m_CameraTranslationSpeed * timestep;
		if (Input::IsKeyPressed(Key::A)) {
			m_CameraPosition.x -=  cos(glm::radians(m_CameraRotation)) * distanceStep;
			m_CameraPosition.y -=  sin(glm::radians(m_CameraRotation)) * distanceStep;
		}
		if (Input::IsKeyPressed(Key::D)) {
			m_CameraPosition.x +=  cos(glm::radians(m_CameraRotation)) * distanceStep;
			m_CameraPosition.y +=  sin(glm::radians(m_CameraRotation)) * distanceStep;
		}
		if (Input::IsKeyPressed(Key::W)) {
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * distanceStep;
			m_CameraPosition.y +=  cos(glm::radians(m_CameraRotation)) * distanceStep;
		}
		if (Input::IsKeyPressed(Key::S)) {
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * distanceStep;
			m_CameraPosition.y -=  cos(glm::radians(m_CameraRotation)) * distanceStep;
		}

		if (m_AllowRotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * timestep;
			if (Input::IsKeyPressed(Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * timestep;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			if (m_CameraRotation < -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.setRotation(m_CameraRotation);
		}

		m_Camera.setPosition(m_CameraPosition);
	}
	
	void OrthographicCameraController::OnEvent(Event& event)
	{
		HX_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(HX_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(HX_BIND_EVENT_FN(OrthographicCameraController::OnWindowResizeEvent));
	}

	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& event)
	{
		HX_PROFILE_FUNCTION();

		float yPos = event.GetOffsetY();
		m_ZoomLevel -= yPos;

		//m_ZoomLevel *= 0.25f
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		HX_PROFILE_FUNCTION();

		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
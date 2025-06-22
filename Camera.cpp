//
// Created by Ciro on 06/20/2025.
//

#include "Camera.hpp"

#include "Utils/Input.hpp"

namespace VoxelEngine
{

	Camera::Camera(glm::vec3 startPos, glm::vec3 startRotation)
		: position(startPos), rotation(startRotation)
	{
		updateVectors();
	}


	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(position, position + m_front, m_up);
	}

	void Camera::ProcessInput(const float deltaTime, const bool forward, const bool backward, const bool left, const bool right, const bool upKey, const bool downKey)
	{
		const float velocity = speed * deltaTime;

		if (Input::IsKeyDown(GLFW_KEY_W)) position += m_front * velocity;
		if (Input::IsKeyDown(GLFW_KEY_S)) position -= m_front * velocity;
		if (Input::IsKeyDown(GLFW_KEY_A)) position -= m_right * velocity;
		if (Input::IsKeyDown(GLFW_KEY_D)) position += m_right * velocity;
		if (Input::IsKeyDown(GLFW_KEY_SPACE)) position += m_up * velocity;
		if (Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT)) position -= m_up * velocity;
	}

	void Camera::ProcessMouse(float offsetX, float offsetY, const bool constrainPitch)
	{
		offsetX *= sensitivity;
		offsetY *= sensitivity;

		rotation.x += offsetX;
		rotation.y += offsetY;

		if (constrainPitch) {
			if (rotation.y > 89.0f) rotation.y = 89.0f;
			if (rotation.y < -89.0f) rotation.y = -89.0f;
		}

		updateVectors();
	}

	void Camera::updateVectors()
	{
		glm::vec3 newFront;
		newFront.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
		newFront.y = sin(glm::radians(rotation.y));
		newFront.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
		m_front = glm::normalize(newFront);
		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}

}
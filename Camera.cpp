#include "Camera.hpp"

#include "Utils/Input.hpp"

namespace VoxelEngine
{
	Camera::Camera(glm::vec3 position, float yaw, float pitch,
	               float fovDeg, float aspectRatio, float nearPlane, float farPlane)
	    : Position(position), Yaw(yaw), Pitch(pitch),
	      FovDeg(fovDeg), AspectRatio(aspectRatio), NearPlane(nearPlane), FarPlane(farPlane)
	{
	    UpdateCameraVectors();
	    UpdateProjectionMatrix();
	    UpdateViewMatrix();
	}

	void Camera::SetPerspective(float fovDeg, float aspectRatio, float nearPlane, float farPlane)
	{
	    FovDeg = fovDeg;
	    AspectRatio = aspectRatio;
	    NearPlane = nearPlane;
	    FarPlane = farPlane;
	    UpdateProjectionMatrix();
	    UpdateViewMatrix(); // viewProj also depends on this
	}

	void Camera::ProcessKeyboard(float deltaTime)
	{
	    float velocity = MovementSpeed * deltaTime;

		auto deltaForward = Input::IsKeyDown(GLFW_KEY_W) ? 1.0f : Input::IsKeyDown(GLFW_KEY_S) ? -1.0f : 0.0f;
		auto deltaRight = Input::IsKeyDown(GLFW_KEY_D) ? 1.0f : Input::IsKeyDown(GLFW_KEY_A) ? -1.0f : 0.0f;
		auto deltaUp = Input::IsKeyDown(GLFW_KEY_SPACE) ? 1.0f : Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT) ? -1.0f : 0.0f;

	    Position += Front * deltaForward * velocity;
	    Position += Right * deltaRight * velocity;
	    Position += WorldUp * deltaUp * velocity;
	    UpdateViewMatrix();
	}

	void Camera::ProcessMouseMovement()
	{
	    Yaw += Input::GetMouseOffsetX() * MouseSensitivity;
	    Pitch += Input::GetMouseOffsetY() * MouseSensitivity;

	    if (Pitch > 89.0f) Pitch = 89.0f;
	    if (Pitch < -89.0f) Pitch = -89.0f;

	    UpdateCameraVectors();
	    UpdateViewMatrix();
	}

	void Camera::UpdateCameraVectors()
	{
	    glm::vec3 front;
	    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	    front.y = sin(glm::radians(Pitch));
	    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	    Front = glm::normalize(front);

	    Right = glm::normalize(glm::cross(Front, WorldUp));
	    Up = glm::normalize(glm::cross(Right, Front));
	}

	void Camera::UpdateViewMatrix()
	{
	    viewMatrix = glm::lookAt(Position, Position + Front, Up);
	    viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void Camera::UpdateProjectionMatrix()
	{
	    projectionMatrix = glm::perspective(glm::radians(FovDeg), AspectRatio, NearPlane, FarPlane);
	}
}
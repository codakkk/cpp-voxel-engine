#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace VoxelEngine
{

	class Camera {
	public:
		Camera(glm::vec3 position, float yaw, float pitch,
			   float fovDeg, float aspectRatio, float nearPlane, float farPlane);

		void SetPerspective(float fovDeg, float aspectRatio, float nearPlane, float farPlane);

		void ProcessKeyboard(float deltaTime);
		void ProcessMouseMovement();

		void SetMovementSpeed(float speed) { MovementSpeed = speed; }
		void SetMouseSensitivity(float sensitivity) { MouseSensitivity = sensitivity; }

		const glm::mat4& GetViewMatrix() const { return viewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }

		glm::vec3 GetPosition() const { return Position; }
		glm::vec3 GetForward() const { return Front; }

		float GetYaw() const { return Yaw; }
		float GetPitch() const { return Pitch; }


	private:
		void UpdateCameraVectors();
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		float Yaw, Pitch;
		float MovementSpeed = 3.0f;
		float MouseSensitivity = 0.1f;

		float FovDeg, AspectRatio, NearPlane, FarPlane;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 viewProjectionMatrix;
	};

}

#endif

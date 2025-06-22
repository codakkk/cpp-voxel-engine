#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace VoxelEngine
{

class Camera {
public:
	glm::vec3 position;
	glm::vec3 rotation;

	float speed = 5.0f;
	float sensitivity = 0.1f;

	explicit Camera(glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 3.0f),
	                glm::vec3 startRotation = glm::vec3(-90.0f, 0.0f, 0.0f));

	glm::mat4 GetViewMatrix() const;

	void ProcessInput(float deltaTime, bool forward, bool backward, bool left, bool right, bool upKey, bool downKey);

	void ProcessMouse(float offsetX, float offsetY, bool constrainPitch = true);

private:
	glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_right = glm::vec3(0.0f);
	glm::vec3 m_up = glm::vec3(0.0f);
	glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	void updateVectors();
};

}
#endif

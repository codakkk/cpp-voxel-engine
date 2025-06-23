//
// Created by Ciro on 06/22/2025.
//

#ifndef INPUT_HPP
#define INPUT_HPP
#include "GLFW/glfw3.h"

namespace Input
{
	void Init(GLFWwindow* window);

	void ProcessKeyboard();
	void ProcessMouse(double xpos, double ypos);

	bool IsKeyDown(int key);
	bool IsKeyPressed(int key); // pressed this frame only

	bool IsKeyReleased(int key);

	float GetMouseX();
	float GetMouseY();

	float GetMouseOffsetX();
	float GetMouseOffsetY();

	void ResetMouse();
} // Utils

#endif //INPUT_HPP

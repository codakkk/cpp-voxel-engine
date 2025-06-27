//
// Created by Ciro on 06/22/2025.
//

#include "Input.hpp"

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace Input
{

	static GLFWwindow* g_Window = nullptr;
	static bool g_IsProcessingInput = true;

	static std::unordered_map<int, bool> g_CurrentKeys;
	static std::unordered_map<int, bool> g_PreviousKeys;

	static std::unordered_map<int, bool> g_CurrentMouseButtons;
	static std::unordered_map<int, bool> g_PreviousMouseButtons;

	static float g_MouseX, g_MouseY, g_MouseXOffset, g_MouseYOffset;

	void Init(GLFWwindow* window)
	{
		g_Window = window;
	}

	void ProcessKeyboard()
	{
		static bool wasPressed = false;

		if (glfwGetKey(g_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			if (!wasPressed)
			{
				g_IsProcessingInput = !g_IsProcessingInput;
				glfwSetInputMode(g_Window, GLFW_CURSOR, g_IsProcessingInput ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

				wasPressed = true;
			}
		}
		else
		{
			wasPressed = false;
		}

		if (g_IsProcessingInput == false)
		{
			return;
		}

		g_PreviousKeys = g_CurrentKeys;

		for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
			g_CurrentKeys[key] = glfwGetKey(g_Window, key) == GLFW_PRESS;
		}
	}

	void ProcessMouse(double xpos, double ypos)
	{
		static float lastX = xpos, lastY = ypos;

		if (g_IsProcessingInput == false)
		{
			lastX = xpos, lastY = ypos;
			return;
		}


		float offsetX = xpos - lastX;
		float offsetY = lastY - ypos; // Reversed: y-coordinates go from bottom to top

		g_MouseX = xpos;
		g_MouseY = ypos;

		g_MouseXOffset = offsetX;
		g_MouseYOffset = offsetY;

		lastX = xpos;
		lastY = ypos;

		// camera.ProcessMouse(offsetX, offsetY);
	}

	void ProcessMouseButtons()
	{
		if (g_IsProcessingInput == false)
		{
			return;
		}

		g_PreviousMouseButtons = g_CurrentMouseButtons;

		for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button)
		{
			g_CurrentMouseButtons[button] = glfwGetMouseButton(g_Window, button) == GLFW_PRESS;
		}
	}

	void ResetMouse()
	{
		g_MouseXOffset = g_MouseYOffset = 0;
	}

	bool IsKeyDown(const int key)
	{
		return g_CurrentKeys[key];
	}

	bool IsKeyPressed(const int key)
	{
		return g_CurrentKeys[key] && !g_PreviousKeys[key];
	}

	bool IsMouseDown(int button)
	{
		return g_CurrentMouseButtons[button];
	}

	bool IsMousePressed(int button)
	{
		return g_CurrentMouseButtons[button] && !g_PreviousMouseButtons[button];
	}

	float GetMouseX()
	{
		return g_MouseX;
	}

	float GetMouseY()
	{
		return g_MouseY;
	}

	float GetMouseOffsetX()
	{
		return g_MouseXOffset;
	}

	float GetMouseOffsetY()
	{
		return g_MouseYOffset;
	}
}

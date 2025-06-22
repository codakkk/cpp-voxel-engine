//
// Created by Ciro on 06/22/2025.
//

#include "Engine.hpp"

#include "Utils/ShaderProgram.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/gl.h>

static auto g_BaseVertexShader =		"#version 330 core\n"
								"layout (location = 0) in vec3 aPos;\n"
								"void main()\n"
								"{\n"
									"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								"}\0";

static auto g_BaseFragmentShader =		"#version 330 core\n"
								"out vec4 FragColor;\n"
								"void main()\n"
								"{\n"
									"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
								"}\0";
namespace VoxelEngine {
	Engine::Engine()
		: m_Camera(glm::vec3(0, 0, 0)),
		  m_ShaderProgram(g_BaseVertexShader, g_BaseFragmentShader)
	{}

	Engine::~Engine() {}

	void Engine::Render() const
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(m_Camera.GetViewMatrix()));

		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);  // Enable depth testing
	}

	void Engine::Update(float deltaTime) {}

	void Engine::Input(float deltaTime)
	{

	}


} // VoxelEngine
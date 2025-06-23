//
// Created by Ciro on 06/22/2025.
//

#include "Engine.hpp"

#include "imgui.h"
#include "Utils/ShaderProgram.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/gl.h>

#define GLSL(src) "#version 330 core\n" #src

static auto g_BaseVertexShader = GLSL(
	layout (location = 0) in vec3 aPos;
	uniform mat4 u_ViewProjection;

	void main()
	{
		gl_Position = u_ViewProjection * vec4(aPos, 1.0);
	}
);

static auto g_BaseFragmentShader = GLSL(
	out vec4 FragColor;
	void main()
	{
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}
);

namespace VoxelEngine
{

	Engine::Engine(const float wx, const float wy)
		: m_Camera(glm::vec3(-3.11, 2, 0.42), -6.4f, -27.40f, 70.0, wx / wy, 0.1, 500.0),
		  m_Chunk(glm::vec3(0, 0, 0)),
		  m_ShaderProgram(g_BaseVertexShader, g_BaseFragmentShader)
	{
		// m_Chunk.BuildMesh();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_VAO.Bind();

		m_VBO.Bind();
		m_VBO.BufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
		m_VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		m_VBO.Unbind();

		m_VAO.Unbind();
	}

	Engine::~Engine() {}

	void Engine::RenderUi() const
	{
		ImGui::Begin("Engine");

		// --- Camera ---
		if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
		{
			auto cameraPos = m_Camera.GetPosition();
			ImGui::Text("Pos: %.2f %.2f %.2f", cameraPos.x, cameraPos.y, cameraPos.z);
			ImGui::Text("Yaw: %.2f", m_Camera.GetYaw());
			ImGui::Text("Pitch: %.2f", m_Camera.GetPitch());
		}


		ImGui::End();
	}

	void Engine::Render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);  // Enable depth testing


		m_ShaderProgram.Use();
		m_ShaderProgram.SetMatrix4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
		m_VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		m_VAO.Unbind();
		// m_Chunk.BuildMesh();
		// m_ShaderProgram.Use();
		// m_ShaderProgram.SetMatrix4("u_ViewProjection", m_Camera.GetProjectionMatrix());
		// const auto meshBuilder = m_Chunk.p_MeshBuilder;
		//
		// meshBuilder.VAO.Bind();
		// glDrawElements(GL_TRIANGLES, floor(meshBuilder.VerticesCount / 4) * 6, GL_UNSIGNED_INT, nullptr);
		// meshBuilder.VAO.Unbind();
	}

	void Engine::Update(float deltaTime)
	{

	}

	void Engine::Input(float deltaTime)
	{
		m_Camera.ProcessKeyboard(deltaTime);
		m_Camera.ProcessMouseMovement();
	}

	void Engine::OnWindowResize(const int width, const int height)
	{
		glViewport(0, 0, width, height);
		m_Camera.SetPerspective(70.0, width / height, 0.1, 500.0);
	}

} // VoxelEngine
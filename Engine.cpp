//
// Created by Ciro on 06/22/2025.
//

#include "Engine.hpp"

#include "imgui.h"
#include "Utils/ShaderProgram.hpp"
#include "Utils/Vertex.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <GL/gl.h>

#define GLSL(src) "#version 330 core\n" #src

static auto g_BaseVertexShader = GLSL(
	layout (location = 0) in uvec3 aPos;
	layout(location = 1) in uvec3 aColor;

	uniform mat4 u_ViewProjection;

	out vec3 v_Color;

	void main()
	{
		v_Color = vec3(aColor);
		gl_Position = u_ViewProjection * vec4(aPos, 1.0);
	}
);

static auto g_BaseFragmentShader = GLSL(
	in vec3 v_Color;

	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(v_Color, 1.0);
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

		m_Vertices.clear();

		m_BlockFaces[Top][0] = glm::vec4(0, 1, 0, 1);
		m_BlockFaces[Top][1] = glm::vec4(0, 1, 1, 1);
		m_BlockFaces[Top][2] = glm::vec4(1, 1, 0, 1);
		m_BlockFaces[Top][3] = glm::vec4(1, 1, 0, 1);
		m_BlockFaces[Top][4] = glm::vec4(0, 1, 1, 1);
		m_BlockFaces[Top][5] = glm::vec4(1, 1, 1, 1);

		m_BlockFaces[Bottom][0] = glm::vec4(0, 0, 0, 1);
		m_BlockFaces[Bottom][1] = glm::vec4(1, 0, 0, 1);
		m_BlockFaces[Bottom][2] = glm::vec4(0, 0, 1, 1);
		m_BlockFaces[Bottom][3] = glm::vec4(0, 0, 1, 1);
		m_BlockFaces[Bottom][4] = glm::vec4(1, 0, 0, 1);
		m_BlockFaces[Bottom][5] = glm::vec4(1, 0, 1, 1);

		m_BlockFaces[Front][0] = glm::vec4(0, 0, 1, 1);
		m_BlockFaces[Front][1] = glm::vec4(1, 0, 1, 1);
		m_BlockFaces[Front][2] = glm::vec4(0, 1, 1, 1);
		m_BlockFaces[Front][3] = glm::vec4(0, 1, 1, 1);
		m_BlockFaces[Front][4] = glm::vec4(1, 0, 1, 1);
		m_BlockFaces[Front][5] = glm::vec4(1, 1, 1, 1);

		m_BlockFaces[Back][0] = glm::vec4(0, 0, 0, 1);
		m_BlockFaces[Back][1] = glm::vec4(0, 1, 0, 1);
		m_BlockFaces[Back][2] = glm::vec4(1, 0, 0, 1);
		m_BlockFaces[Back][3] = glm::vec4(1, 0, 0, 1);
		m_BlockFaces[Back][4] = glm::vec4(0, 1, 0, 1);
		m_BlockFaces[Back][5] = glm::vec4(1, 1, 0, 1);

		m_BlockFaces[Left][0] = glm::vec4(0, 1, 0, 1);
		m_BlockFaces[Left][1] = glm::vec4(0, 0, 0, 1);
		m_BlockFaces[Left][2] = glm::vec4(0, 1, 1, 1);
		m_BlockFaces[Left][3] = glm::vec4(0, 1, 1, 1);
		m_BlockFaces[Left][4] = glm::vec4(0, 0, 0, 1);
		m_BlockFaces[Left][5] = glm::vec4(0, 0, 1, 1);

		m_BlockFaces[Right][0] = glm::vec4(1, 0, 0, 1);
		m_BlockFaces[Right][1] = glm::vec4(1, 1, 0, 1);
		m_BlockFaces[Right][2] = glm::vec4(1, 0, 1, 1);
		m_BlockFaces[Right][3] = glm::vec4(1, 0, 1, 1);
		m_BlockFaces[Right][4] = glm::vec4(1, 1, 0, 1);
		m_BlockFaces[Right][5] = glm::vec4(1, 1, 1, 1);

		for (int x = 0; x < CHUNK_SIZE_X; ++x)
		{
			for (int y = 0; y < CHUNK_SIZE_Y; ++y)
			{
				for (int z = 0; z < CHUNK_SIZE_Z; ++z)
				{
					auto current = m_Chunk.GetBlock({x, y, z});

					if (current == false)
					{
						continue;
					}

					auto left = m_Chunk.GetBlock({x-1, y, z});
					auto right = m_Chunk.GetBlock({x+1, y, z});
					auto front = m_Chunk.GetBlock({x, y, z+1});
					auto back = m_Chunk.GetBlock({x, y, z-1});
					auto top = m_Chunk.GetBlock({x, y+1, z});
					auto bottom = m_Chunk.GetBlock({x, y-1, z});


					if (left == false)
					{
						AddFace(glm::vec3(x, y, z), i8Color3(0, 0, 255), Left);
					}

					if (right == false)
					{
						AddFace(glm::vec3(x, y, z), i8Color3(255, 255, 0), Right);
					}

					if (front == false)
					{
						AddFace(glm::vec3(x, y, z), i8Color3(255, 0, 0), Front);
					}

					if (back == false)
					{
						AddFace(glm::vec3(x, y, z), i8Color3(0, 255, 0), Back);
					}

					if (top == false)
					{
						AddFace(glm::vec3(x, y, z), i8Color3(255, 0, 255), Top);
					}

					if (bottom == false)
					{
						AddFace(glm::vec3(x, y, z), i8Color3(255, 255, 255), Bottom);
					}

				}
			}
		}

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		/// aPos
		glVertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
		glEnableVertexAttribArray(0);

		/// aColor
		glVertexAttribIPointer(1, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
		glEnableVertexAttribArray(1);

		/// Buffer data to VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), &m_Vertices.front(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	Engine::~Engine()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

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

		if (ImGui::CollapsingHeader("Rendering", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("Chunk Size: %dx%dx%d", CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z);
			ImGui::Text("Total Voxels: %d", CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
			ImGui::Text("Vertices: %d", m_Vertices.size());
			ImGui::Text("Triangles: %d", m_Vertices.size() / 3);
			ImGui::Text("Quads: %d", (m_Vertices.size() / 3) / 2);
		}


		ImGui::End();
	}

	void Engine::Render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);  // Enable depth testing
		glEnable(GL_CULL_FACE);

		m_ShaderProgram.Use();
		m_ShaderProgram.SetMatrix4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
		glBindVertexArray(0);
	}

	void Engine::Update(float deltaTime) const
	{

	}

	void Engine::Input(const float deltaTime)
	{
		m_Camera.ProcessKeyboard(deltaTime);
		m_Camera.ProcessMouseMovement();
	}

	void Engine::OnWindowResize(const int width, const int height)
	{
		glViewport(0, 0, width, height);

		float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		m_Camera.SetPerspective(70.0, aspectRatio, 0.1, 500.0);

		std::cout << "width: " << width << " height: " << height << std::endl;
		std::cout << "Aspect Ratio: " << aspectRatio << std::endl;
	}

	void Engine::AddFace(const glm::vec3& position, const i8Color3& color, BlockFaceType faceType)
	{
		const auto translation = glm::vec4(position, 0.0f);

		const auto blockFace = m_BlockFaces[faceType];

		Vertex v[6];

		v[0].position = translation + blockFace[0];
		v[0].color = color;

		v[1].position = translation + blockFace[1];
		v[1].color = color;

		v[2].position = translation + blockFace[2];
		v[2].color = color;

		v[3].position = translation + blockFace[3];
		v[3].color = color;

		v[4].position = translation + blockFace[4];
		v[4].color = color;

		v[5].position = translation + blockFace[5];
		v[5].color = color;

		m_Vertices.push_back(v[0]); m_Vertices.push_back(v[1]); m_Vertices.push_back(v[2]);
		m_Vertices.push_back(v[3]); m_Vertices.push_back(v[4]); m_Vertices.push_back(v[5]);
	}
} // VoxelEngine
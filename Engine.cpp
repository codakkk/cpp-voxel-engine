//
// Created by Ciro on 06/22/2025.
//

#include "Engine.hpp"

#include "Ray.hpp"
#include "imgui.h"
#include "Utils/Input.hpp"
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
		:	m_Camera(glm::vec3(-3.11, 2, 0.42), -6.4f, -27.40f, 70.0, wx / wy, 0.1, 500.0),
			m_Chunk(glm::vec3(0, 0, 0)),
			m_ShaderProgram(g_BaseVertexShader, g_BaseFragmentShader),
			m_IndexOffset(0),
			m_EnableCulling(true),
			m_EnableVoxelFaceCulling(true),
			m_Vertices(0),
			m_IsMeshDirty(true)
	{
		// +Z (Front)
		m_BlockFaces[Front][0] = glm::vec4(0, 0, 1, 1); // bottom-left
		m_BlockFaces[Front][1] = glm::vec4(1, 0, 1, 1); // bottom-right
		m_BlockFaces[Front][2] = glm::vec4(1, 1, 1, 1); // top-right
		m_BlockFaces[Front][3] = glm::vec4(0, 1, 1, 1); // top-left

		// -Z (Back)
		m_BlockFaces[Back][0] = glm::vec4(1, 0, 0, 1); // bottom-right
		m_BlockFaces[Back][1] = glm::vec4(0, 0, 0, 1); // bottom-left
		m_BlockFaces[Back][2] = glm::vec4(0, 1, 0, 1); // top-left
		m_BlockFaces[Back][3] = glm::vec4(1, 1, 0, 1); // top-right

		// +Y (Top)
		m_BlockFaces[Top][0] = glm::vec4(0, 1, 1, 1); // front-left
		m_BlockFaces[Top][1] = glm::vec4(1, 1, 1, 1); // front-right
		m_BlockFaces[Top][2] = glm::vec4(1, 1, 0, 1); // back-right
		m_BlockFaces[Top][3] = glm::vec4(0, 1, 0, 1); // back-left

		// -Y (Bottom)
		m_BlockFaces[Bottom][0] = glm::vec4(0, 0, 0, 1); // back-left
		m_BlockFaces[Bottom][1] = glm::vec4(1, 0, 0, 1); // back-right
		m_BlockFaces[Bottom][2] = glm::vec4(1, 0, 1, 1); // front-right
		m_BlockFaces[Bottom][3] = glm::vec4(0, 0, 1, 1); // front-left

		// -X (Left)
		m_BlockFaces[Left][0] = glm::vec4(0, 0, 0, 1); // back-bottom
		m_BlockFaces[Left][1] = glm::vec4(0, 0, 1, 1); // front-bottom
		m_BlockFaces[Left][2] = glm::vec4(0, 1, 1, 1); // front-top
		m_BlockFaces[Left][3] = glm::vec4(0, 1, 0, 1); // back-top

		// +X (Right)
		m_BlockFaces[Right][0] = glm::vec4(1, 0, 1, 1); // front-bottom
		m_BlockFaces[Right][1] = glm::vec4(1, 0, 0, 1); // back-bottom
		m_BlockFaces[Right][2] = glm::vec4(1, 1, 0, 1); // back-top
		m_BlockFaces[Right][3] = glm::vec4(1, 1, 1, 1); // front-top

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
	}

	Engine::~Engine()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void Engine::RenderUi()
	{
		ImGui::Begin("Engine");

		// --- Camera ---
		if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
		{
			const auto cameraPos = m_Camera.GetPosition();
			ImGui::Text("Pos: %.2f %.2f %.2f", cameraPos.x, cameraPos.y, cameraPos.z);
			ImGui::Text("Yaw: %.2f", m_Camera.GetYaw());
			ImGui::Text("Pitch: %.2f", m_Camera.GetPitch());
		}

		// --- Rendering Options ---
		if (ImGui::CollapsingHeader("Rendering", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("Chunk Size: %dx%dx%d", CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z);
			ImGui::Text("Total Voxels: %d", CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
			ImGui::Text("Vertices: %d", m_Vertices.size());
			ImGui::Text("Triangles: %d", m_Indices.size() / 3);
			ImGui::Text("Quads: %d", (m_Indices.size() / 3) / 2);
			ImGui::Text("Indices: %d", m_Indices.size());

			ImGui::Checkbox("GL CULL FACE", &m_EnableCulling);
			if (ImGui::Checkbox("Voxel Face Cull", &m_EnableVoxelFaceCulling))
			{
				m_IsMeshDirty = true;
			}
		}

		// --- World Options ---
		if (ImGui::CollapsingHeader("World", ImGuiTreeNodeFlags_DefaultOpen))
		{
			static int x = 0, y = 0, z = 0;

			ImGui::Begin("Toggle Block");

			// Integer inputs for x, y, z
			ImGui::InputInt("X", &x);
			ImGui::InputInt("Y", &y);
			ImGui::InputInt("Z", &z);

			// Insert button
			if (ImGui::Button("Toggle"))
			{
				const auto pos = glm::vec3(x, y, z);
				auto state = m_Chunk.GetBlock(pos);

				m_Chunk.SetBlock(pos, !state);

				m_IsMeshDirty = true;
			}

			ImGui::End();

		}

		// Crosshair
		const ImGuiIO& io = ImGui::GetIO();
		ImDrawList* drawList = ImGui::GetForegroundDrawList();

		const ImVec2 center(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
		constexpr float size = 5.0f;
		constexpr ImU32 color = IM_COL32(255, 255, 255, 255); // white
		drawList->AddRect(ImVec2(center.x - size, center.y-size), ImVec2(center.x + size, center.y+size), color, 1.0f);

		ImGui::End();
	}

	void Engine::Render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);  // Enable depth testing

		if (m_EnableCulling)
		{
			glEnable(GL_CULL_FACE);
		}

		m_ShaderProgram.Use();
		m_ShaderProgram.SetMatrix4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());

		if (!m_Vertices.empty())
		{
			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		if (m_EnableCulling)
		{
			glDisable(GL_CULL_FACE);
		}

		if (m_IsMeshDirty)
		{
			CreateMesh();
		}
	}

	void Engine::Update(float deltaTime) const
	{

	}

	void Engine::Input(const float deltaTime)
	{
		m_Camera.ProcessKeyboard(deltaTime);
		m_Camera.ProcessMouseMovement();

		constexpr float maxDistance = 5.0f;
		constexpr float step = 0.2f;

		if(Input::IsMousePressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			Ray ray = MakeCenterScreenRay(m_Camera);
			ray.origin = m_Camera.GetPosition();
			ray.direction = m_Camera.GetForward();

			for (float t = 0.0f; t < maxDistance; t += step) {
				glm::vec3 pos = ray.origin + ray.direction * t;
				// Test the voxel at floor(pos)

				if (!m_Chunk.IsInBounds(pos))
				{
					continue;
				}

				auto state = m_Chunk.GetBlock(pos);

				if (state == true && m_Chunk.SetBlock(pos, false))
				{
					m_IsMeshDirty = true;
					break;
				}
			}
		}

		if(Input::IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			auto ray = MakeCenterScreenRay(m_Camera);
			auto hit = RaycastVoxelHit(ray, m_Chunk, 5);

			if (hit.has_value())
			{
				auto [hitBlock, face] = hit.value();
				glm::ivec3 offset = GetFaceOffset(face);
				glm::ivec3 placeAt = hitBlock + offset;

				m_Chunk.SetBlock(placeAt, true); // or any type
				m_IsMeshDirty = true;
			}
		}
	}

	void Engine::OnWindowResize(const int width, const int height)
	{
		glViewport(0, 0, width, height);

		const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		m_Camera.SetPerspective(70.0, aspectRatio, 0.1, 500.0);

		std::cout << "width: " << width << " height: " << height << std::endl;
		std::cout << "Aspect Ratio: " << aspectRatio << std::endl;
	}

	void Engine::CreateMesh()
{
	if (!m_IsMeshDirty)
		return;

	m_IsMeshDirty = false;

	m_IndexOffset = 0;
	m_Vertices.clear();
	m_Indices.clear();

	glm::ivec3 dims(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z);

	for (int face = 0; face < 6; ++face)
	{
		bool isBackFace = face > 2;
		int dir = face % 3;
		int u = (dir + 1) % 3;
		int v = (dir + 2) % 3;

		glm::ivec3 start(0);
		glm::ivec3 curr(0);

		for (start[dir] = 0; start[dir] < dims[dir]; ++start[dir])
		{
			std::vector<std::vector<bool>> merged(dims[u], std::vector<bool>(dims[v], false));

			for (start[u] = 0; start[u] < dims[u]; ++start[u])
			{
				for (start[v] = 0; start[v] < dims[v]; ++start[v])
				{
					if (merged[start[u]][start[v]])
						continue;

					bool voxel = m_Chunk.GetBlock(start);

					if (!voxel || !IsFaceVisible(start, dir, isBackFace))
						continue;

					glm::ivec3 quadSize(0);
					curr = start;

					// Extend in v direction
					for (++curr[v]; curr[v] < dims[v] &&
						!merged[curr[u]][curr[v]] &&
						m_Chunk.GetBlock(curr) &&
						m_Chunk.GetBlock(curr) == voxel &&
						IsFaceVisible(curr, dir, isBackFace); ++curr[v]) {}

					quadSize[v] = curr[v] - start[v];

					// Extend in u direction
					curr = start;
					for (++curr[u]; curr[u] < dims[u]; ++curr[u])
					{
						bool allMatch = true;
						for (curr[v] = start[v]; curr[v] < start[v] + quadSize[v]; ++curr[v])
						{
							if (merged[curr[u]][curr[v]] ||
								!m_Chunk.GetBlock(curr) ||
								m_Chunk.GetBlock(curr) != voxel ||
								!IsFaceVisible(curr, dir, isBackFace))
							{
								allMatch = false;
								break;
							}
						}
						if (!allMatch)
							break;
					}
					quadSize[u] = curr[u] - start[u];

					// Mark merged area
					for (int du = 0; du < quadSize[u]; ++du)
						for (int dv = 0; dv < quadSize[v]; ++dv)
							merged[start[u] + du][start[v] + dv] = true;

					// Construct quad
					glm::ivec3 m(0), n(0);
					m[u] = quadSize[u];
					n[v] = quadSize[v];

					glm::ivec3 offset = start;
					offset[dir] += isBackFace ? 0 : 1;

					glm::vec3 v0 = glm::vec3(offset);
					glm::vec3 v1 = glm::vec3(offset + m);
					glm::vec3 v2 = glm::vec3(offset + m + n);
					glm::vec3 v3 = glm::vec3(offset + n);

					// Use face enums to drive color for now
					i8Color3 color = GetColorForFace((BlockFaceType)face);
					AddQuad(v0, v1, v2, v3, color, isBackFace);
				}
			}
		}
	}

	// GPU buffer upload
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);

	glVertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribIPointer(1, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

	void Engine::AddQuad(const glm::i8vec3& v0, const glm::i8vec3& v1, const glm::i8vec3& v2, const glm::i8vec3& v3, const i8Color3& color, bool flip)
	{
		std::vector<Vertex> quad(4);
		quad[0].position = v0;
		quad[0].color = color;
		quad[1].position = v1;
		quad[1].color = color;
		quad[2].position = v2;
		quad[2].color = color;
		quad[3].position = v3;
		quad[3].color = color;


		std::vector<GLuint> indices = flip
			? std::vector<GLuint>{ m_IndexOffset + 2, m_IndexOffset + 1, m_IndexOffset + 0,
								   m_IndexOffset + 0, m_IndexOffset + 3, m_IndexOffset + 2 }
		: std::vector<GLuint>{ m_IndexOffset + 0, m_IndexOffset + 1, m_IndexOffset + 2,
							   m_IndexOffset + 2, m_IndexOffset + 3, m_IndexOffset + 0 };

		m_Vertices.insert(m_Vertices.end(), quad.begin(), quad.end());
		m_Indices.insert(m_Indices.end(), indices.begin(), indices.end());
		m_IndexOffset += 4;
	}

	bool Engine::IsFaceVisible(glm::ivec3 pos, int axis, bool backFace) const
	{
		pos[axis] += backFace ? -1 : 1;
		return !m_Chunk.IsInBounds(pos) || !m_Chunk.GetBlock(pos);
	}

	i8Color3 Engine::GetColorForFace(BlockFaceType face) const
	{
		switch (face)
		{
			case Left:   return i8Color3(0, 0, 255);
			case Right:  return i8Color3(255, 255, 0);
			case Front:  return i8Color3(255, 0, 0);
			case Back:   return i8Color3(0, 255, 0);
			case Top:    return i8Color3(255, 0, 255);
			case Bottom: return i8Color3(255, 255, 255);
			default:     return i8Color3(127, 127, 127);
		}
	}
} // VoxelEngine
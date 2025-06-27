//
// Created by Ciro on 06/22/2025.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>

#include "Camera.hpp"
#include "Enums.hpp"
#include "World/Chunk.hpp"
#include "Utils/ShaderProgram.hpp"


namespace VoxelEngine {

struct i8Color3;
struct Vertex;

class Engine {

public:
	Engine(float wx, float wy);
	~Engine();

	void Input(float deltaTime);

	void OnWindowResize(int width, int height);

	void Update(float deltaTime) const;

	void RenderUi();

	void Render();

private:
	Camera m_Camera;

	World::Chunk m_Chunk;

	bool m_EnableCulling;
	bool m_EnableVoxelFaceCulling;

	bool m_IsMeshDirty;

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;

	Utils::ShaderProgram m_ShaderProgram;

	std::vector<Vertex> m_Vertices;
	std::vector<GLuint> m_Indices;

	GLuint m_IndexOffset;

	std::unordered_map<BlockFaceType, glm::vec4[4]> m_BlockFaces;

	void CreateMesh();
	void AddQuad(const glm::i8vec3& v0, const glm::i8vec3& v1, const glm::i8vec3& v2, const glm::i8vec3& v3, const i8Color3& color, bool flip);

	bool IsFaceVisible(glm::ivec3 pos, int axis, bool backFace) const;

	i8Color3 GetColorForFace(BlockFaceType face) const;
};

} // VoxelEngine

#endif //ENGINE_HPP

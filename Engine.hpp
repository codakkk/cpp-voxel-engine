//
// Created by Ciro on 06/22/2025.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

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
	void AddFace(const glm::vec3& position, const i8Color3& color, BlockFaceType faceType);
};

} // VoxelEngine

#endif //ENGINE_HPP

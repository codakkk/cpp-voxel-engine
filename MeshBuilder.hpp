//
// Created by Ciro on 06/22/2025.
//

#ifndef MESHBUILDER_HPP
#define MESHBUILDER_HPP
#include "Enums.hpp"
#include "Utils/Vao.hpp"
#include "Utils/Vbo.hpp"
#include "Utils/Vertex.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include <vector>



namespace VoxelEngine {

	class Chunk;

	class MeshBuilder {
	public:
		MeshBuilder();
		~MeshBuilder();

		void Build(const Chunk &chunk);

		std::uint32_t VerticesCount;

		Utils::VAO VAO;

		void AddFace(const Chunk& chunk, BlockFaceType faceType);
	private:

		std::vector<Vertex> m_Vertices;
		Utils::VBO m_VBO;

		glm::vec4 m_TopFace[4];
		glm::vec4 m_BottomFace[4];
		glm::vec4 m_FrontFace[4];
		glm::vec4 m_BackFace[4];
		glm::vec4 m_LeftFace[4];
		glm::vec4 m_RightFace[4];
	};

} // VoxelEngine

#endif //MESHBUILDER_HPP

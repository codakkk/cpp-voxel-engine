//
// Created by Ciro on 06/20/2025.
//

#ifndef CHUNK_HPP
#define CHUNK_HPP


#include "../Constants.hpp"
#include "../MeshBuilder.hpp"

#include <array>

#include "../Voxel.hpp"
#include "glm/vec3.hpp"

namespace World
{

	class Chunk
	{
	public:
		explicit Chunk(const glm::vec3& position);
		~Chunk();

		void BuildMesh();

		void SetBlock(const glm::vec3& position, VoxelEngine::VoxelType type);
		VoxelEngine::VoxelType GetBlock(const glm::vec3& position) const;

		VoxelEngine::MeshBuilder p_MeshBuilder;


	private:
		glm::vec3 m_Position;
		std::array<std::array<std::array<VoxelEngine::VoxelType, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> m_Data{};

	};

}



#endif //CHUNK_HPP

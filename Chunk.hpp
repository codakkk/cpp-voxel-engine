//
// Created by Ciro on 06/20/2025.
//

#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <array>

#include "Voxel.hpp"
#include "glm/vec3.hpp"

#include <cstdint>

namespace VoxelEngine
{

class Chunk
{
public:
	explicit Chunk(const glm::vec3& position);
	~Chunk();

	void SetBlock(const glm::vec3& position, VoxelType type);
	VoxelType GetBlock(const glm::vec3& position) const;

	#define CHUNK_SIZE_X 16
	#define CHUNK_SIZE_Y 255
	#define CHUNK_SIZE_Z 16


private:
	glm::vec3 m_position;
	std::array<std::array<std::array<VoxelType, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> m_data{};
};

}



#endif //CHUNK_HPP

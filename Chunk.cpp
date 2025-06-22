//
// Created by Ciro on 06/20/2025.
//

#include "Chunk.hpp"

#include <cstring>

VoxelEngine::Chunk::Chunk(const glm::vec3& position)
	: m_position(position)
{
	memset(&m_data, static_cast<int>(VoxelType::Grass), CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
}

VoxelEngine::Chunk::~Chunk() = default;

void VoxelEngine::Chunk::SetBlock(const glm::vec3& position, const VoxelType type)
{
	const auto x = static_cast<int>(position.x);
	const auto y = static_cast<int>(position.y);
	const auto z = static_cast<int>(position.z);

	m_data.at(x).at(y).at(z) = type;
}

VoxelEngine::VoxelType VoxelEngine::Chunk::GetBlock(const glm::vec3& position) const
{
	const auto x = static_cast<int>(position.x);
	const auto y = static_cast<int>(position.y);
	const auto z = static_cast<int>(position.z);

	return m_data.at(x).at(y).at(z);
}
//
// Created by Ciro on 06/20/2025.
//

#include "Chunk.hpp"

#include <cstring>

namespace VoxelEngine
{

	Chunk::Chunk(const glm::vec3& position)
		: m_Position(position)
	{
		memset(&m_Data, static_cast<int>(VoxelType::Grass), CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
	}

	Chunk::~Chunk() = default;

	void Chunk::SetBlock(const glm::vec3& position, const VoxelType type)
	{
		const auto x = static_cast<int>(position.x);
		const auto y = static_cast<int>(position.y);
		const auto z = static_cast<int>(position.z);

		m_Data.at(x).at(y).at(z) = type;
	}

	VoxelType Chunk::GetBlock(const glm::vec3& position) const
	{
		const auto x = static_cast<int>(position.x);
		const auto y = static_cast<int>(position.y);
		const auto z = static_cast<int>(position.z);

		return m_Data.at(x).at(y).at(z);
	}

	void Chunk::BuildMesh()
	{
		p_MeshBuilder.Build(*this);
	}

}
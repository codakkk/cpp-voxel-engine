//
// Created by Ciro on 06/20/2025.
//

#include "Chunk.hpp"


#include <cstring>

namespace World
{
	Chunk::Chunk(const glm::vec3& position)
		: m_Position(position)
	{
		memset(&m_Data, true, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
	}

	Chunk::~Chunk() = default;

	bool Chunk::SetBlock(const glm::vec3 &position, bool type)
	{
		const auto x = static_cast<int>(position.x);
		const auto y = static_cast<int>(position.y);
		const auto z = static_cast<int>(position.z);

		if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z)
		{
			return false;
		}

		m_Data.at(x).at(y).at(z) = type;
		return true;
	}

	bool Chunk::GetBlock(const glm::vec3& position) const
	{
		const auto x = static_cast<int>(position.x);
		const auto y = static_cast<int>(position.y);
		const auto z = static_cast<int>(position.z);

		if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z)
		{
			return false;
		}

		return m_Data.at(x).at(y).at(z);
	}

	bool Chunk::IsInBounds(const glm::vec3& position) const
	{
		const auto x = static_cast<int>(position.x);
		const auto y = static_cast<int>(position.y);
		const auto z = static_cast<int>(position.z);

		if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z)
		{
			return false;
		}

		return true;
	}
}
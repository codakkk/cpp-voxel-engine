//
// Created by Ciro on 06/20/2025.
//

#ifndef CHUNK_HPP
#define CHUNK_HPP


#include "../Constants.hpp"

#include <array>

#include "glm/vec3.hpp"

namespace World
{

	class Chunk
	{
	public:
		explicit Chunk(const glm::vec3& position);
		~Chunk();

		void BuildMesh();

		bool SetBlock(const glm::vec3 &position, bool value);
		bool GetBlock(const glm::vec3& position) const;

		bool IsInBounds(const glm::vec3& position) const;
	private:
		glm::vec3 m_Position;
		std::array<std::array<std::array<bool, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> m_Data{};

	};

}



#endif //CHUNK_HPP

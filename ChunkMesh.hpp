//
// Created by Ciro on 06/22/2025.
//

#ifndef CHUNKMESH_HPP
#define CHUNKMESH_HPP
#include "Enums.hpp"
#include "glm/vec3.hpp"

#include <cstdint>
#include <vector>

namespace VoxelEngine {

class Chunk;

class ChunkMesh {
public:
	ChunkMesh();
	~ChunkMesh();

	bool Construct(const Chunk& chunk);

	std::uint32_t verticesCount;


private:
	void AddFace(const Chunk& chunk, BlockFaceType face, const glm::vec3& position);

	std::vector<void> m_vertices;

};

} // VoxelEngine

#endif //CHUNKMESH_HPP

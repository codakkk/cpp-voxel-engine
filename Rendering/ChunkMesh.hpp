//
// Created by Ciro on 06/23/2025.
//

#ifndef CHUNKMESH_HPP
#define CHUNKMESH_HPP
#include "Mesh.hpp"


namespace Rendering
{
	class ChunkMesh
	{
	public:
		ChunkMesh() = default;

		void AddFace();
	private:
		Mesh m_Mesh;
	};
}



#endif //CHUNKMESH_HPP

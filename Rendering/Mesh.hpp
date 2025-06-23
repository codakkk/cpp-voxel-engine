//
// Created by Ciro on 06/23/2025.
//

#ifndef MESH_HPP
#define MESH_HPP
#include "glad/glad.h"

#include <vector>

namespace Rendering
{
	struct Mesh
	{
		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
	};
}
#endif //MESH_HPP

//
// Created by Ciro on 06/22/2025.
//

#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "../Constants.hpp"
#include "glm/vec3.hpp"

#include <cmath>
#include <cstdint>

namespace VoxelEngine
{
	struct i8Vec3
	{
		uint8_t x;
		uint8_t y;
		uint8_t z;

		i8Vec3 operator=(const glm::vec3& vec)
		{
			assert(floor(vec.x) <= CHUNK_SIZE_X);
			assert(floor(vec.y) <= CHUNK_SIZE_Y);
			assert(floor(vec.z) <= CHUNK_SIZE_Z);

			x = floor(vec.x);
			y = floor(vec.y);
			z = floor(vec.z);

			return *this;
		}
	};

	struct i8Color3
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;

		i8Color3 operator=(const glm::vec3& vec)
		{
			r = floor(vec.x);
			g = floor(vec.y);
			b = floor(vec.z);
			return *this;
		}
	};


	struct Vertex
	{
		i8Vec3 position;
		i8Color3 color;
	};
}
#endif //VERTEX_HPP

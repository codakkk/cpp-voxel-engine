//
// Created by Ciro on 06/25/2025.
//

#ifndef RAY_HPP
#define RAY_HPP
#include "glm/fwd.hpp"
#include "glm/matrix.hpp"
#include "glm/vec3.hpp"

#include <optional>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction; // should be normalized
};

static Ray MakeCenterScreenRay(const VoxelEngine::Camera& camera)
{
	glm::mat4 invViewProj = glm::inverse(camera.GetViewProjectionMatrix());

	// NDC (Normalized Device Coordinates)
	glm::vec4 nearPointNDC = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f); // Near plane center
	glm::vec4 farPointNDC  = glm::vec4(0.0f, 0.0f,  1.0f, 1.0f); // Far plane center

	glm::vec4 nearWorld = invViewProj * nearPointNDC;
	glm::vec4 farWorld  = invViewProj * farPointNDC;

	// Perspective divide
	nearWorld /= nearWorld.w;
	farWorld  /= farWorld.w;

	glm::vec3 origin = glm::vec3(nearWorld);
	glm::vec3 direction = glm::normalize(glm::vec3(farWorld - nearWorld));

	return { origin, direction };
}

static std::optional<std::tuple<glm::ivec3, VoxelEngine::BlockFaceType>> RaycastVoxelHit(const Ray& ray, const World::Chunk& chunk, float maxDistance = 100.0f)
{
	glm::ivec3 lastBlock;

	for (float t = 0.0f; t < maxDistance; t += 0.01f)
	{
		glm::vec3 currentPos = ray.origin + ray.direction * t;
		glm::ivec3 blockPos = glm::floor(currentPos);

		if (chunk.GetBlock(blockPos) != false)
		{
			glm::ivec3 delta = blockPos - lastBlock;

			VoxelEngine::BlockFaceType face;
			if (delta.x == 1)       face = VoxelEngine::Left;
			else if (delta.x == -1) face = VoxelEngine::Right;
			else if (delta.y == 1)  face = VoxelEngine::Bottom;
			else if (delta.y == -1) face = VoxelEngine::Top;
			else if (delta.z == 1)  face = VoxelEngine::Back;
			else if (delta.z == -1) face = VoxelEngine::Front;
			else                    continue; // should not happen

			return std::make_tuple(blockPos, face);
		}

		lastBlock = glm::floor(currentPos);
	}

	return std::nullopt;
}

#endif //RAY_HPP

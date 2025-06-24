//
// Created by Ciro on 06/22/2025.
//

#ifndef ENUMS_HPP
#define ENUMS_HPP

namespace VoxelEngine
{
	enum BlockFaceType
	{
		Top = 0,
		Bottom = 1,
		Left = 2,
		Right = 3,
		Front = 4,
		Back = 5,

		Last
	};

	inline glm::ivec3 GetFaceOffset(const BlockFaceType face)
	{
		switch (face)
		{
		case Front:    return {  0,  0,  1 };
		case Back:	   return {  0,  0, -1 };
		case Left:     return { -1,  0,  0 };
		case Right:    return {  1,  0,  0 };
		case Top:      return {  0,  1,  0 };
		case Bottom:   return {  0, -1,  0 };
		default:       return { 0, 0, 0 };
		}
	}
}

#endif //ENUMS_HPP

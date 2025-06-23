//
// Created by Ciro on 06/22/2025.
//

#include "MeshBuilder.hpp"

#include "Chunk.hpp"
#include "Utils/IndexBuffer.hpp"
#include "glm/vec4.hpp"

namespace VoxelEngine
{

	MeshBuilder::MeshBuilder() : VerticesCount(0), m_Vertices(0)
	{
		static bool IndexBufferInitialized = false;

		// Static index buffer
		static Utils::IndexBuffer StaticIBO;

		if (IndexBufferInitialized == false)
		{
			IndexBufferInitialized = true;

			GLuint* IndexBuffer = nullptr;

			constexpr int indexSz = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6;
			int indexOffset = 0;

			IndexBuffer = new GLuint[indexSz * 6];

			for (size_t i = 0; i < indexSz; i += 6)
			{
				IndexBuffer[i] = 0 + indexOffset;
				IndexBuffer[i + 1] = 1 + indexOffset;
				IndexBuffer[i + 2] = 2 + indexOffset;
				IndexBuffer[i + 3] = 2 + indexOffset;
				IndexBuffer[i + 4] = 3 + indexOffset;
				IndexBuffer[i + 5] = 0 + indexOffset;

				indexOffset = indexOffset + 4;
			}

			StaticIBO.BufferData(indexSz * 6 * sizeof(GLuint), IndexBuffer, GL_STATIC_DRAW);

			delete[] IndexBuffer;
		}


		VAO.Bind();
		m_VBO.Bind();
		StaticIBO.Bind();
		m_VBO.VertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		VAO.Unbind();

		m_FrontFace[0] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		m_FrontFace[1] = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
		m_FrontFace[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_FrontFace[3] = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

		m_BackFace[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		m_BackFace[1] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		m_BackFace[2] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		m_BackFace[3] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

		m_TopFace[0] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		m_TopFace[1] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		m_TopFace[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_TopFace[3] = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

		m_BottomFace[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		m_BottomFace[1] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		m_BottomFace[2] = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
		m_BottomFace[3] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

		m_LeftFace[0] = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
		m_LeftFace[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		m_LeftFace[2] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		m_LeftFace[3] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

		m_RightFace[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_RightFace[1] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		m_RightFace[2] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		m_RightFace[3] = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	}

	MeshBuilder::~MeshBuilder() {}

	void MeshBuilder::Build(const Chunk& chunk)
	{
		m_Vertices.clear();

		for (int x = 0; x < CHUNK_SIZE_X; x++)
		{
			for (int y = 0; y < CHUNK_SIZE_Y; y++)
			{
				for (int z = 0; z < CHUNK_SIZE_Z; z++)
				{
					auto voxel = chunk.GetBlock(glm::vec3(x, y, z));

					if (voxel == VoxelType::Air)
					{
						continue;
					}


					AddFace(chunk, Front);
					AddFace(chunk, Backward);
					AddFace(chunk, Top);
					AddFace(chunk, Bottom);
					AddFace(chunk, Left);
					AddFace(chunk, Right);
				}
			}
		}

		VerticesCount = 0;

		if (m_Vertices.size() > 0)
		{
			m_VBO.BufferData(m_Vertices.size() * sizeof(Vertex), &m_Vertices.front(), GL_STATIC_DRAW);
			VerticesCount = m_Vertices.size();

			m_Vertices.clear();
		}
	}

	void MeshBuilder::AddFace(const Chunk &chunk, BlockFaceType faceType)
	{
		glm::vec4 translation = glm::vec4(glm::vec3(0,0,0), 0.0f);
		Vertex v[4];

		switch (faceType)
		{
			case Top:
			{
				v[0].position = translation + m_TopFace[0];
				v[1].position = translation + m_TopFace[1];
				v[2].position = translation + m_TopFace[2];
				v[3].position = translation + m_TopFace[3];
				break;
			}
			case Bottom:
			{
				v[0].position = translation + m_BottomFace[3];
				v[1].position = translation + m_BottomFace[2];
				v[2].position = translation + m_BottomFace[1];
				v[3].position = translation + m_BottomFace[0];
				break;
			}
			case Left:
			{
				v[0].position = translation + m_LeftFace[0];
				v[1].position = translation + m_LeftFace[1];
				v[2].position = translation + m_LeftFace[2];
				v[3].position = translation + m_LeftFace[3];
				break;
			}
			case Right:
			{
				v[0].position = translation + m_RightFace[0];
				v[1].position = translation + m_RightFace[1];
				v[2].position = translation + m_RightFace[2];
				v[3].position = translation + m_RightFace[3];
				break;
			}
			case Front:
			{
				v[0].position = translation + m_FrontFace[3];
				v[1].position = translation + m_FrontFace[2];
				v[2].position = translation + m_FrontFace[1];
				v[3].position = translation + m_FrontFace[0];
				break;
			}
			case Backward:
			{
				v[0].position = translation + m_BackFace[0];
				v[1].position = translation + m_BackFace[1];
				v[2].position = translation + m_BackFace[2];
				v[3].position = translation + m_BackFace[3];
				break;
			}
		}

		m_Vertices.push_back(v[0]);
		m_Vertices.push_back(v[1]);
		m_Vertices.push_back(v[2]);
		m_Vertices.push_back(v[3]);
	}


} // VoxelEngine
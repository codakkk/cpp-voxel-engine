//
// Created by Ciro on 06/22/2025.
//

#include "IndexBuffer.hpp"

namespace Utils {
	IndexBuffer::IndexBuffer()
	{
		this->m_Id = 0;
		glGenBuffers(1, &this->m_Id);
		this->Bind();
	}

	void IndexBuffer::BufferData(const GLsizeiptr size, const void* data, const GLenum usage) const
	{
		this->Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &this->m_Id);
		this->Unbind();
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
} // Utils
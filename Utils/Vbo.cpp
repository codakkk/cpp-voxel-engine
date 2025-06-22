//
// Created by Ciro on 06/22/2025.
//

#include "Vbo.hpp"

namespace Utils {

	VBO::VBO()
	{
		glGenBuffers(1, &this->m_id);
	}

	VBO::~VBO()
	{
		glDeleteBuffers(1, &this->m_id);
	}

	void VBO::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
	}

	void VBO::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::BufferData(GLsizeiptr size, void* data, GLenum usage) const
	{
		this->Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}

	void VBO::BufferSubData(GLintptr offset, GLsizeiptr size, void* data) const
	{
		this->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	void VBO::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const
	{
		this->Bind();
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glEnableVertexAttribArray(index);
	}

	void VBO::VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer) const
	{
		this->Bind();
		glVertexAttribIPointer(index, size, type, stride, pointer);
		glEnableVertexAttribArray(index);
	}
} // Utils
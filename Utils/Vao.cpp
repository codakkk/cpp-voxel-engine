//
// Created by Ciro on 06/22/2025.
//

#include "Vao.hpp"

#include "glad/glad.h"

namespace Utils {
	VAO::VAO() : m_id(0)
	{
		glGenVertexArrays(1, &this->m_id);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &this->m_id);
	}

	void VAO::Bind() const
	{
		glBindVertexArray(this->m_id);
	}

	void VAO::Unbind() const
	{
		glBindVertexArray(0);
	}
} // Utils
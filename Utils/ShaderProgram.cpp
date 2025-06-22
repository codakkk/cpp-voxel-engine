//
// Created by Ciro on 06/22/2025.
//

#include "ShaderProgram.hpp"

#include "Shader.hpp"

namespace Utils
{
	ShaderProgram::ShaderProgram(const char* vertexShader, const char* fragmentShader)
	{
		m_id = glCreateProgram();

		const auto vertex = Shader(GL_VERTEX_SHADER);
		vertex.Compile(vertexShader);

		const auto fragment = Shader(GL_FRAGMENT_SHADER);
		fragment.Compile(fragmentShader);

		glAttachShader(m_id, vertex.GetId());
		glAttachShader(m_id, fragment.GetId());

		glLinkProgram(m_id);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_id);
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(m_id);
	}

} // Utils
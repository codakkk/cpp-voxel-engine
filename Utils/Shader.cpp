//
// Created by Ciro on 06/22/2025.
//

#include "Shader.hpp"

#include <iostream>

namespace Utils {

	Shader::Shader(GLint shaderType)
	{
		m_id = glCreateShader(shaderType);
	}

	Shader::~Shader()
	{
		glDeleteShader(m_id);
	}

	void Shader::Compile(const char *sourceCode) const
	{
		glShaderSource(m_id, 1, &sourceCode, nullptr);
		glCompileShader(m_id);

		int success;
		char infoLog[512];
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

		if(!success)
		{
			glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}


} // Utils
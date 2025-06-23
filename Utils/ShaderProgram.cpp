//
// Created by Ciro on 06/22/2025.
//

#include "ShaderProgram.hpp"

#include "Shader.hpp"
#include "glm/gtc/type_ptr.inl"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Utils
{
	ShaderProgram::ShaderProgram(const char* vertexSource, const char* fragmentSource)
	{
		m_Id = glCreateProgram();

		const auto vertex = Shader(GL_VERTEX_SHADER);
		const auto fragment = Shader(GL_FRAGMENT_SHADER);

		vertex.Compile(vertexSource);
		fragment.Compile(fragmentSource);

		glAttachShader(m_Id, vertex.GetId());
		glAttachShader(m_Id, fragment.GetId());

		glLinkProgram(m_Id);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_Id);
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(m_Id);
	}

	void ShaderProgram::SetMatrix4(const std::string &name, glm::mat4 matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	GLint ShaderProgram::GetUniformLocation(const std::string &name)
	{
		if (m_Location.contains(name) == false)
		{
			GLint loc = glGetUniformLocation(this->m_Id, name.c_str());

			if (loc == -1)
			{
				std::cout << "\nERROR! : UNIFORM NOT FOUND!    |    UNIFORM : " << name << "  \n\n";
			}

			m_Location[name] = loc;
		}

		return m_Location[name];
	}
} // Utils
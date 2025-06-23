//
// Created by Ciro on 06/22/2025.
//

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "glad/glad.h"

#include "glm/glm.hpp"
#include <string>
#include <unordered_map>

namespace Utils {
class Shader;

class ShaderProgram {
public:
	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	~ShaderProgram();

	void Use() const;

	void SetMatrix4(const std::string &name, glm::mat4 matrix);
private:
	GLuint m_Id;

	std::unordered_map<std::string, GLint> m_Location;

	GLint GetUniformLocation(const std::string &name);
};

} // Utils

#endif //SHADERPROGRAM_HPP

//
// Created by Ciro on 06/22/2025.
//

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "glad/glad.h"

namespace Utils {
class Shader;

class ShaderProgram {
public:
	ShaderProgram(const char* vertexShader, const char* fragmentShader);
	~ShaderProgram();

	void Use() const;

private:
	GLuint m_id;
};

} // Utils

#endif //SHADERPROGRAM_HPP

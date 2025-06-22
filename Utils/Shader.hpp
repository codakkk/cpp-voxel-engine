//
// Created by Ciro on 06/22/2025.
//

#ifndef SHADER_HPP
#define SHADER_HPP
#include "glad/glad.h"

namespace Utils {

class Shader {
public:
	explicit Shader(GLint shaderType);
	~Shader();

	void Compile(const char* sourceCode) const;

	GLuint GetId() const { return m_id; }
private:
	GLuint m_id;
};

} // Utils

#endif //SHADER_HPP

//
// Created by Ciro on 06/22/2025.
//

#ifndef VBO_HPP
#define VBO_HPP
#include "glad/glad.h"

namespace Utils {

class VBO {
public:
	VBO();
	~VBO();

	void Bind() const;
	void Unbind() const;

	void BufferData(GLsizeiptr size, void* data, GLenum usage) const;
	void BufferSubData(GLintptr offset, GLsizeiptr size, void* data) const;
	void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const;

	void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer) const;


private:
	GLuint m_id;
};

} // Utils

#endif //VBO_HPP

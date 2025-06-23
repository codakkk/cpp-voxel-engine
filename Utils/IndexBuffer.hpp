//
// Created by Ciro on 06/22/2025.
//

#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP
#include "glad/glad.h"

namespace Utils {

class IndexBuffer {
public:
	IndexBuffer();
	~IndexBuffer();

	void BufferData(GLsizeiptr size, const void* data, GLenum usage) const;


	void Bind() const;

	void Unbind() const;

private:
	GLuint m_Id;
};

} // Utils

#endif //INDEXBUFFER_HPP

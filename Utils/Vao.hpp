//
// Created by Ciro on 06/22/2025.
//

#ifndef VAO_HPP
#define VAO_HPP

#include "glad/glad.h"

namespace Utils {

class VAO {
public:
	VAO();

	~VAO();

	void Bind() const;

	void Unbind() const;
private:
	GLuint m_id;
};

} // Utils

#endif //VAO_HPP

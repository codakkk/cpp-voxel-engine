//
// Created by Ciro on 06/22/2025.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Camera.hpp"
#include "Chunk.hpp"
#include "Utils/ShaderProgram.hpp"
#include "Utils/Vao.hpp"
#include "Utils/Vbo.hpp"


namespace VoxelEngine {
class Engine {

public:
	Engine(float wx, float wy);
	~Engine();

	void Input(float deltaTime);

	void OnWindowResize(int width, int height);

	void Update(float deltaTime);

	void RenderUi() const;

	void Render();

private:
	Camera m_Camera;

	Chunk m_Chunk;

	Utils::VAO m_VAO;
	Utils::VBO m_VBO;

	Utils::ShaderProgram m_ShaderProgram;
};

} // VoxelEngine

#endif //ENGINE_HPP

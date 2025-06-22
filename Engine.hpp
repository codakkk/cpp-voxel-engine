//
// Created by Ciro on 06/22/2025.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "Camera.hpp"
#include "Utils/ShaderProgram.hpp"


namespace VoxelEngine {
class Engine {

public:
	Engine();
	~Engine();

	void Input(float deltaTime);

	void Update(float deltaTime);

	void Render() const;

private:
	Camera m_Camera;

	Utils::ShaderProgram m_ShaderProgram;
};

} // VoxelEngine

#endif //ENGINE_HPP

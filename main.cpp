#include "Camera.hpp"
#include "Chunk.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include "Engine.hpp"
#include "Utils/Input.hpp"
#include "Utils/ShaderProgram.hpp"
#include "Utils/Vao.hpp"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <iostream>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/gtc/type_ptr.hpp>

int g_Frames = 0, g_LastFrames = 0;
float g_LastFrameTime;

float g_RotationSpeed = 45.0f;

bool g_ShowWireframe = false;

void renderUi(const float deltaTime)
{
	// Start ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Your UI here
	ImGui::Begin("Debug Panel");

	// --- Performance Info ---
	if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Delta Time: %.3f ms", deltaTime * 1000.0f);
		ImGui::Text("FPS: %d", g_LastFrames);
	}

	// --- Cube Controls ---
	if (ImGui::CollapsingHeader("Cube Controls", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::SliderFloat("Rotation Speed", &g_RotationSpeed, 0.0f, 360.0f, "%.1f deg/s");
	}

	if (ImGui::CollapsingHeader("Rendering", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Checkbox("Wireframe Mode", &g_ShowWireframe);
	}



	ImGui::End();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void render(GLFWwindow* window, const VoxelEngine::Engine& engine, const float deltaTime)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	const float aspect = static_cast<float>(width) / static_cast<float>(height);

	glViewport(0, 0, width, height);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projection));

	glPolygonMode(GL_FRONT_AND_BACK, g_ShowWireframe ? GL_LINE : GL_FILL);

	engine.Render();

	glDisable(GL_DEPTH_TEST);

	renderUi(deltaTime);

    glfwSwapBuffers(window);

}


int main()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (const int version = gladLoadGL(); version == 0) {
		printf("Failed to initialize OpenGL context\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		Input::ProcessMouse(xpos, ypos);
	});

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

    double lastTime = glfwGetTime();

	auto engine = VoxelEngine::Engine();

	Input::Init(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Compute delta time
    	const auto now = static_cast<float>(glfwGetTime());
        const auto deltaTime = static_cast<float>(now - lastTime);

        glfwPollEvents();

    	Input::ProcessKeyboard();

    	engine.Input(deltaTime);
    	engine.Update(deltaTime);

    	render(window, engine, deltaTime);

    	g_LastFrameTime += deltaTime;
    	g_Frames++;
    	if (g_LastFrameTime >= 1.0f)
    	{
    		g_LastFrameTime = 0.0f;
    		g_LastFrames = g_Frames;
    		g_Frames = 0;

    		std::cout << "FPS: " << g_LastFrames << std::endl;
    	}

        lastTime = now;
    }

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
cmake_minimum_required(VERSION 3.15)
project(cg_voxel LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
)

# GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
)

# ImGui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG docking
)

# Make available
FetchContent_MakeAvailable(glfw glm imgui)

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD (local v2.x)
add_library(glad STATIC
        external/glad/src/glad.c
)
target_include_directories(glad PUBLIC external/glad/include)

# ImGui setup
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw OpenGL::GL glad)

# Output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Your executable
add_executable(${PROJECT_NAME}
        main.cpp
        Camera.cpp Camera.hpp
        Chunk.cpp Chunk.hpp
        Voxel.cpp Voxel.hpp
        ChunkMesh.cpp
        ChunkMesh.hpp
        Enums.hpp
        Utils/Vbo.cpp
        Utils/Vbo.hpp
        Utils/Shader.cpp
        Utils/Shader.hpp
        Utils/ShaderProgram.cpp
        Utils/ShaderProgram.hpp
        Utils/Vao.cpp
        Utils/Vao.hpp
        Engine.cpp
        Engine.hpp
        Utils/Input.cpp
        Utils/Input.hpp
)

# Link everything
target_link_libraries(${PROJECT_NAME}
        PRIVATE glad
        PRIVATE glm::glm
        PRIVATE glfw
        PRIVATE OpenGL::GL
        PRIVATE imgui
)

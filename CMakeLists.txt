cmake_minimum_required(VERSION 3.15)
project(cg_voxel C)

set(CMAKE_C_STANDARD 23)

# Set path to GLUT (freeglut) depending on architecture
set(GLFW_ROOT "C:/Development/glfw")
set(GLFW_INCLUDE_DIR "${GLFW_ROOT}/include")
set(GLFW_LIBRARY "${GLFW_ROOT}/lib-mingw-w64/libglfw3.a")

# Find OpenGL
find_package(OpenGL REQUIRED)

# Define executable
add_executable(cg_voxel main.c)

# Include directories for GLUT
include_directories(${GLFW_INCLUDE_DIR})

# Link against raw OpenGL_LIBRARIES, not OpenGL::OpenGL
target_link_libraries(cg_voxel ${GLFW_LIBRARY} opengl32)

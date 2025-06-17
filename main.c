#include <math.h>
#include <GLFW/glfw3.h>

// Replace gluPerspective
void setPerspective(float fovY, float aspect, float zNear, float zFar)
{
    float fH = tanf(fovY / 360.0f * 3.14159f) * zNear;
    float fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}


void drawCube()
{
    glBegin(GL_TRIANGLES);

    // Each face has 2 triangles (6 vertices), colored per face

    // Front (red)
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1,  1);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1,  1,  1);

    glVertex3f(-1, -1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f(-1,  1,  1);

    // Back (green)
    glColor3f(0, 1, 0);
    glVertex3f( 1, -1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1,  1, -1);

    glVertex3f( 1, -1, -1);
    glVertex3f(-1,  1, -1);
    glVertex3f( 1,  1, -1);

    // Top (blue)
    glColor3f(0, 0, 1);
    glVertex3f(-1,  1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1,  1, -1);

    glVertex3f(-1,  1,  1);
    glVertex3f( 1,  1, -1);
    glVertex3f(-1,  1, -1);

    // Bottom (yellow)
    glColor3f(1, 1, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, -1,  1);

    glVertex3f(-1, -1, -1);
    glVertex3f( 1, -1,  1);
    glVertex3f(-1, -1,  1);

    // Right (magenta)
    glColor3f(1, 0, 1);
    glVertex3f(1, -1,  1);
    glVertex3f(1, -1, -1);
    glVertex3f(1,  1, -1);

    glVertex3f(1, -1,  1);
    glVertex3f(1,  1, -1);
    glVertex3f(1,  1,  1);

    // Left (cyan)
    glColor3f(0, 1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1,  1,  1);

    glVertex3f(-1, -1, -1);
    glVertex3f(-1,  1,  1);
    glVertex3f(-1,  1, -1);

    glEnd();
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);  // Enable depth testing

    float angle = 0.0f;
    double lastTime = glfwGetTime();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        constexpr float rotationSpeed = 45.0f;

        // Compute delta time
        const double currentTime = glfwGetTime();
        const double deltaTime = currentTime - lastTime;

        lastTime = currentTime;

        // Rotate using delta time
        angle += (float)(rotationSpeed * deltaTime);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float aspect = (float)width / (float)height;

        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        setPerspective(60.0f, aspect, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);
        glRotatef(angle, 1.0f, 1.0f, 0.0f);

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawCube();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
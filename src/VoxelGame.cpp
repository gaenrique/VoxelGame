#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Glew init failed
        std::cout << "Error" << std::endl;
    }

    float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int indices[3] = {
        0, 1, 2
    };

    VertexArray va;
    BufferLayout verticesLayout;
    verticesLayout.InsertLayoutElement(3, false);
    va.AddBuffer(VERTEX, vertices, sizeof(vertices), verticesLayout);
    BufferLayout indicesLayout;
    va.AddBuffer(INDEX, indices, sizeof(indices), indicesLayout);

    Shader shader("basic.vert", "basic.frag");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        va.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
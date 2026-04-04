#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.hpp"

#include "assets.h"

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const char *baseWindowTitle = "u24584216";
    const int windowWidth = 1200;
    const int windowHeight = 800;
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, baseWindowTitle, NULL, NULL);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowAspectRatio(window, windowWidth, windowHeight);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int nx, ny;
    glfwGetFramebufferSize(window, &nx, &ny);
    glViewport(0, 0, nx, ny);

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_STENCIL_TEST);

    // Axis setup
    const float axisLength = 1.0f;
    const GLfloat axisVertices[] = {
        -axisLength, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        axisLength, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, -axisLength, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, axisLength, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -axisLength, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, axisLength, 0.0f, 0.0f, 1.0f, 1.0f};

    GLuint axisVAO = 0;
    GLuint axisVBO = 0;
    glGenVertexArrays(1, &axisVAO);
    glGenBuffers(1, &axisVBO);

    glBindVertexArray(axisVAO);
    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Scene setup
    complexSceneHolder *golfCourse = GolfCourse();
    golfCourse->Scale(0.4);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glUseProgram(programID);

        // Draw axes
        glBindVertexArray(axisVAO);
        glDrawArrays(GL_LINES, 0, 6);
        glBindVertexArray(0);

        // --- Pass 1: draw cutouts into stencil ---
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // disable color writes
        glDepthMask(GL_FALSE);                               // disable depth writes

        glStencilFunc(GL_ALWAYS, 1, 0xFF);                   // always pass
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);           // replace stencil with 1

        golfCourse->drawCutoutShapes();                      // draw cutout shapes

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);     // re-enable color writes
        glDepthMask(GL_TRUE);                                // re-enable depth writes

        // --- Pass 2: draw scene with stencil test ---
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);                 // only draw where stencil != 1
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);              // keep stencil values

        golfCourse->draw();                                  // draw normal scene

        // Animate
        golfCourse->RotateY(0.5);
        golfCourse->getIndex(0)->RotateArbitrary(0.5);

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            golfCourse->setWireframeMode();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             !glfwWindowShouldClose(window));

    glDeleteBuffers(1, &axisVBO);
    glDeleteVertexArrays(1, &axisVAO);
    glfwTerminate();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.hpp"

#include "assets.h"

void VectorTesting();
void MatrixTesitng();
void TriangleTesting();
void SquareTesting();

void libraryTesting()
{
	VectorTesting();
	std::cout << std::endl;
	MatrixTesitng();
	std::cout << std::endl;
	TriangleTesting();
	std::cout << std::endl;
	SquareTesting();
}
int main()
{
#ifdef COVERAGE_RUN
    libraryTesting();
    return 0;
#endif

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

    const float axisLength = 1.0f;
    GLfloat axisVertices[42]; // 6 vertices * 7 attributes

    GLuint axisVAO = 0;
    GLuint axisVBO = 0;
    glGenVertexArrays(1, &axisVAO);
    glGenBuffers(1, &axisVBO);

    glBindVertexArray(axisVAO);
    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Cylinder *cyl = new Cylinder(Circle<3>({0.0f, 0.0f, 0}, 0.2f, 10, Colour::DarkBrown), 0.5, Colour::DarkBrown);
    DrawerVisitor *dwr = new DrawerVisitor(cyl);
    dwr->SetMyOrientation(cyl->getOrientation());
    dwr->Translation(Direction::up, 0.5);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        // Update axis vertices based on current center
        Vector<3> center = dwr->getMyOrientation()->getCenter();

        GLfloat updatedAxisVertices[] = {
            center[0] - axisLength, center[1], center[2], 1.0f, 0.0f, 0.0f, 1.0f,
            center[0] + axisLength, center[1], center[2], 1.0f, 0.0f, 0.0f, 1.0f,

            center[0], center[1] - axisLength, center[2], 0.0f, 1.0f, 0.0f, 1.0f,
            center[0], center[1] + axisLength, center[2], 0.0f, 1.0f, 0.0f, 1.0f,

            center[0], center[1], center[2] - axisLength, 0.0f, 0.0f, 1.0f, 1.0f,
            center[0], center[1], center[2] + axisLength, 0.0f, 0.0f, 1.0f, 1.0f};

        glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(updatedAxisVertices), updatedAxisVertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(axisVAO);
        glDrawArrays(GL_LINES, 0, 6);
        glBindVertexArray(0);

        dwr->draw();
        dwr->RotateX(0.5);
        dwr->RotateArbitrary(0.05);
        dwr->getMyOrientation()->getCenter();

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            dwr->setWireframeMode();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             !glfwWindowShouldClose(window));

    glDeleteBuffers(1, &axisVBO);
    glDeleteVertexArrays(1, &axisVAO);
    glfwTerminate();
    delete dwr;

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.hpp"

#include "assets.h"
#include "controls/controlManager.h"

static bool keyPressedOnce(GLFWwindow *window, int key, bool &flag)
{
    if (glfwGetKey(window, key) == GLFW_PRESS)
    {
        if (!flag)
        {
            flag = true;
            return true;
        }
    }
    else
    {
        flag = false;
    }
    return false;
}

int main()
{

    Vector<3> eye = {0.0f, 0.0f, -2};    // camera position, away from origin
    Vector<3> up = {0.0f, 1.0f, 0.0f};   // world up
    Vector<3> gaze = {0.0f, 0.0f, 1.0f}; // looking toward -Z

    Camera &cam = Camera::getInstance(eye, up, gaze);

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

    // Scene setup
    complexSceneHolder *golfCourse = GolfCourse();
    complexSceneHolder *axisScene = Axes();
    golfCourse->Scale(0.5);

    golfCourse->RotateY(270);

    ControlManager controls(window, golfCourse);
    bool spacePressed = false;



    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glUseProgram(programID);

        axisScene->draw();
        golfCourse->draw();
        golfCourse->getIndex(0)->RotateArbitrary(controls.getSpeed());

        glfwPollEvents();
        controls.processInput();

        if (keyPressedOnce(window, GLFW_KEY_SPACE, spacePressed))
        {
        delete golfCourse;
        golfCourse = GolfCourse();
        golfCourse->Scale(0.5);
        golfCourse->RotateY(270);
        controls.setScene(golfCourse);
        }

        glfwSwapBuffers(window);
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             !glfwWindowShouldClose(window));


             
    delete golfCourse;
                delete axisScene;
    glfwTerminate();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.hpp"
#include "camera/camera.h"
#include "controls/controlManager.h"
#include "sceneClasses/drawerVisitor.h"
#include "lights/globalLights.h"
#include "lights/pointLight.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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
GLuint loadTexture(const char *filename)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
                     format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}

static void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    Camera::getInstance().setViewportSize(width, height);
}

int main()
{

    Vector<3> eye = {0.0f, 0.0f, -3};    // camera position, away from origin
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
    double lastFpsTime = glfwGetTime();
    int frameCount = 0;

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
    cam.setViewportSize(nx, ny);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_STENCIL_TEST);

    GlobalLights::getInstance().addLight(new PointLight(Colour::Red, {-1, 1, 1}, 10.0f));
    GlobalLights::getInstance().addLight(new PointLight(Colour::Blue, {1, 1, 1}, 10.0f));

    int numSides = 1;
    MultiFacedSurface *mult = new MultiFacedSurface({0, 0, 0}, 3, 3, numSides, Colour::Chrome);
    mult->setLightAffected(true);

    DrawerVisitor *dwr = new DrawerVisitor(mult);
    dwr->RotateX(70);
    dwr->Translation(Direction::down, 1);

    MultiFacedSurface *multLeft = new MultiFacedSurface({0, 1, 3.5}, 3, 3, 50, Colour::Chrome);
    multLeft->setLightAffected(true);
    DrawerVisitor dwr2(multLeft);
    dwr2.RotateX(360);

    Sphere *sphere = new Sphere({0, 0, 0}, 0.5, 5, 10, Colour::Red);

    // Load color texture
    GLuint sphereTex = loadTexture("textures/ColTex.png");
    sphere->getSurface().setColorTexture(sphereTex);

    // Load displacement texture

    GLuint displacementTex = loadTexture("textures/Displacement.png");
    sphere->getSurface().setDisplacementTexture(displacementTex);
    sphere->getSurface().enableDisplacementTexture(true);
    // Register with DrawerVisitor
    DrawerVisitor dwrSphere(sphere);

    ControlManager controls(window, &dwrSphere);
    bool spacePressed = false;

    DrawerVisitor *lightDwr = new DrawerVisitor(GlobalLights::getInstance().getLights()[0]->getShape());
    DrawerVisitor *lightDwr2 = new DrawerVisitor(GlobalLights::getInstance().getLights()[1]->getShape());

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glUseProgram(programID);

        frameCount++;
        double currentTime = glfwGetTime();
        double elapsedTime = currentTime - lastFpsTime;
        if (elapsedTime >= 1.0)
        {
            int fps = (frameCount / elapsedTime);
            char windowTitle[64];
            snprintf(windowTitle, sizeof(windowTitle), "%s | FPS: %d", baseWindowTitle, fps);
            glfwSetWindowTitle(window, windowTitle);
            frameCount = 0;
            lastFpsTime = currentTime;
        }

        glfwPollEvents();
        controls.processInput();
       // dwr->draw();
       // dwr2.draw();
       // lightDwr->draw();
       // lightDwr2->draw();
        dwrSphere.draw();
        if (keyPressedOnce(window, GLFW_KEY_SPACE, spacePressed))
        {

            numSides++;
            mult->setSides(numSides);
            dwr->Visit(mult);
            dwr->RotateX(70);
            dwr->Translation(Direction::down, 1);
        }

        glfwSwapBuffers(window);
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             !glfwWindowShouldClose(window));

    delete dwr;
    glfwTerminate();
    return 0;
}

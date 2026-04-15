#ifndef CONTROLS_H
#define CONTROLS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Scene;

class ControlManager
{
    GLFWwindow *window;
    Scene *scene;
    float TransAmount;
    float rotationDegrees;
    float arbitrarySpeed;

    bool wireframeActive = false; // track current render mode

private:
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void rotateX();
    void rotateY();
    void rotateZ();

public:
    ControlManager(GLFWwindow *window, Scene *scene)
    {
        this->window = window;
        this->scene = scene;
        this->TransAmount = 0.1f; // sensible defaults
        this->rotationDegrees = 0.6f;
        this->arbitrarySpeed = 0.0f;
    };
    float getSpeed() { return this->arbitrarySpeed; };
    void setScene(Scene *scene) { this->scene = scene; }
    void processInput();
};

#endif // CONTROLS_H

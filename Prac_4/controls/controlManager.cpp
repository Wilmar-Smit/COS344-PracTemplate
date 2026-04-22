#include "controlManager.h"
#include "../sceneClasses/Scene.h"


// helper: returns true while the key is held down
static bool keyHeldDown(GLFWwindow *window, int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

// Private helpers
void ControlManager::moveForward() { scene->Translation(Direction::forward, TransAmount); }
void ControlManager::moveBackward() { scene->Translation(Direction::back, TransAmount); }
void ControlManager::moveLeft() { scene->Translation(Direction::right, TransAmount); }
void ControlManager::moveRight() { scene->Translation(Direction::left, TransAmount); }
void ControlManager::moveUp() { scene->Translation(Direction::up, TransAmount); }
void ControlManager::moveDown() { scene->Translation(Direction::down, TransAmount); }

void ControlManager::rotateX() { scene->RotateX(rotationDegrees); }
void ControlManager::rotateY() { scene->RotateY(rotationDegrees); }
void ControlManager::rotateZ() { scene->RotateZ(rotationDegrees); }

void ControlManager::processInput()
{
    // Rotations
    if (keyHeldDown(window, GLFW_KEY_W))
    {
        rotateX();
    }
    if (keyHeldDown(window, GLFW_KEY_S))
    {
        rotationDegrees = -rotationDegrees;
        rotateX();
        rotationDegrees = -rotationDegrees;
    }

    if (keyHeldDown(window, GLFW_KEY_A))
    {
        rotateY();
    }
    if (keyHeldDown(window, GLFW_KEY_D))
    {
        rotationDegrees = -rotationDegrees;
        rotateY();
        rotationDegrees = -rotationDegrees;
    }

    if (keyHeldDown(window, GLFW_KEY_E))
    {
        rotateZ();
    }
    if (keyHeldDown(window, GLFW_KEY_Q))
    {
        rotationDegrees = -rotationDegrees;
        rotateZ();
        rotationDegrees = -rotationDegrees;
    }

    // Translations
    if (keyHeldDown(window, GLFW_KEY_I))
    {
        moveUp();
    }
    if (keyHeldDown(window, GLFW_KEY_K))
    {
        moveDown();
    }
    if (keyHeldDown(window, GLFW_KEY_L))
    {
        moveRight();
    }
    if (keyHeldDown(window, GLFW_KEY_J))
    {
        moveLeft();
    }
    if (keyHeldDown(window, GLFW_KEY_O))
    {
        moveForward();
    }
    if (keyHeldDown(window, GLFW_KEY_U))
    {
        moveBackward();
    }

    // Rotor speed control
    if (keyHeldDown(window, GLFW_KEY_KP_ADD))
    {
        arbitrarySpeed += 0.5f;
    }
    if (keyHeldDown(window, GLFW_KEY_KP_SUBTRACT))
    {
        arbitrarySpeed = std::max(0.0f, arbitrarySpeed - 0.5f);
    }

    // Wireframe toggle with Enter
    static bool enterWasDown = false;
    bool enterIsDown = keyHeldDown(window, GLFW_KEY_ENTER);

    if (enterIsDown && !enterWasDown)
    {
        if (wireframeActive)
        {
            scene->setNormalMode();
            wireframeActive = false;
        }
        else
        {
            scene->setWireframeMode();
            wireframeActive = true;
        }
    }

    enterWasDown = enterIsDown;
}

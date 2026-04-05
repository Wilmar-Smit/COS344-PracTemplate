#include "controlManager.h"
#include "../sceneClasses/Scene.h"
#include <algorithm>

// one-shot flags
static bool wPressed=false, sPressed=false;
static bool aPressed=false, dPressed=false;
static bool ePressed=false, qPressed=false;
static bool iPressed=false, kPressed=false;
static bool lPressed=false, jPressed=false;
static bool oPressed=false, uPressed=false;
static bool plusPressed=false, minusPressed=false;
static bool enterPressed=false;   // NEW

// helper: returns true only once per press/release cycle
static bool keyPressedOnce(GLFWwindow* window, int key, bool &flag)
{
    if (glfwGetKey(window, key) == GLFW_PRESS)
    {
        if (!flag) { flag = true; return true; }
    }
    else { flag = false; }
    return false;
}

// Private helpers
void ControlManager::moveForward()   { scene->Translation(Direction::forward, TransAmount); }
void ControlManager::moveBackward()  { scene->Translation(Direction::back, TransAmount); }
void ControlManager::moveLeft()      { scene->Translation(Direction::left, TransAmount); }
void ControlManager::moveRight()     { scene->Translation(Direction::right, TransAmount); }
void ControlManager::moveUp()        { scene->Translation(Direction::up, TransAmount); }
void ControlManager::moveDown()      { scene->Translation(Direction::down, TransAmount); }

void ControlManager::rotateX()       { scene->RotateX(rotationDegrees); }
void ControlManager::rotateY()       { scene->RotateY(rotationDegrees); }
void ControlManager::rotateZ()       { scene->RotateZ(rotationDegrees); }

void ControlManager::processInput()
{
    // Rotations
    if (keyPressedOnce(window, GLFW_KEY_W, wPressed)) { rotateX(); }
    if (keyPressedOnce(window, GLFW_KEY_S, sPressed)) { rotationDegrees=-rotationDegrees; rotateX(); rotationDegrees=-rotationDegrees; }

    if (keyPressedOnce(window, GLFW_KEY_A, aPressed)) { rotateY(); }
    if (keyPressedOnce(window, GLFW_KEY_D, dPressed)) { rotationDegrees=-rotationDegrees; rotateY(); rotationDegrees=-rotationDegrees; }

    if (keyPressedOnce(window, GLFW_KEY_E, ePressed)) { rotateZ(); }
    if (keyPressedOnce(window, GLFW_KEY_Q, qPressed)) { rotationDegrees=-rotationDegrees; rotateZ(); rotationDegrees=-rotationDegrees; }

    // Translations
    if (keyPressedOnce(window, GLFW_KEY_I, iPressed)) { moveUp(); }
    if (keyPressedOnce(window, GLFW_KEY_K, kPressed)) { moveDown(); }
    if (keyPressedOnce(window, GLFW_KEY_L, lPressed)) { moveRight(); }
    if (keyPressedOnce(window, GLFW_KEY_J, jPressed)) { moveLeft(); }
    if (keyPressedOnce(window, GLFW_KEY_O, oPressed)) { moveForward(); }
    if (keyPressedOnce(window, GLFW_KEY_U, uPressed)) { moveBackward(); }

    // Rotor speed control
    if (keyPressedOnce(window, GLFW_KEY_KP_ADD, plusPressed)) { arbitrarySpeed += 0.5f; }
    if (keyPressedOnce(window, GLFW_KEY_KP_SUBTRACT, minusPressed)) { arbitrarySpeed = std::max(0.0f, arbitrarySpeed - 0.5f); }

    // Wireframe toggle with Enter
    if (keyPressedOnce(window, GLFW_KEY_ENTER, enterPressed))
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
}

#include "controlManager.h"
#include "Scene.h" // your templated Scene definition
// Movement
template <typename n>
void ControlManager<n>::moveForward(Scene<n> *scene)
{
    scene.Translation(Direction::up, 1);
}

template <typename n>
void ControlManager<n>::moveBackward(Scene<n> *scene)
{
    scene->Translation(Direction::down, 1);
}

template <typename n>
void ControlManager<n>::moveLeft(Scene<n> *scene)
{
    scene->Translation(Direction::left, 1);
}

template <typename n>
void ControlManager<n>::moveRight(Scene<n> *scene)
{
    scene->Translation(Direction::right, 1);
}

// Rotation
template <typename n>
void ControlManager<n>::rotateX(Scene<n> *scene)
{
    // TODO: implement rotation around X axis
}

template <typename n>
void ControlManager<n>::rotateY(Scene<n> *scene)
{
    // TODO: implement rotation around Y axis
}

template <typename n>
void ControlManager<n>::rotateZ(Scene<n> *scene)
{
    // TODO: implement rotation around Z axis
    scene->Rotate(30);
}

// Dispatcher
template <typename n>
void ControlManager<n>::processInput(GLFWwindow *window, Scene<n> *scene)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveForward(scene);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveBackward(scene);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moveLeft(scene);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moveRight(scene);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        rotateX(scene);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        rotateY(scene);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        rotateZ(scene);
}

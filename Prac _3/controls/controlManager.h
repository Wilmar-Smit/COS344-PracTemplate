#ifndef CONTROLS_H
#define CONTROLS_H

#include <GLFW/glfw3.h>

// Forward declaration of templated Scene type
template <typename n>
class Scene;

template <typename n>
class ControlManager {
public:
    ControlManager() = default;

    // Movement
    void moveForward(Scene<n>* scene);
    void moveBackward(Scene<n>* scene);
    void moveLeft(Scene<n>* scene);
    void moveRight(Scene<n>* scene);

    // Rotation
    void rotateX(Scene<n>* scene);
    void rotateY(Scene<n>* scene);
    void rotateZ(Scene<n>* scene);

    // Central dispatcher: checks key states and calls the right functions
    void processInput(GLFWwindow* window, Scene<n>* scene);
};

#endif // CONTROLS_H

#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/MathLibrary/Shape.h"

template <int n>
class Scene
{
private:
public:
    virtual void draw() = 0;
    virtual void reloadVertices() = 0;
    virtual Shape<n> *getShape() const = 0;
    virtual void addScene(Scene<n> *scene) = 0;
    virtual ~Scene() = default;
};

#endif

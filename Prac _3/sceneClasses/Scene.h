#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/MathLibrary/2D shapes/Shape.h"
#include "../include/MathLibrary/Matrix.h"

enum class Direction
{
    left,
    right,
    up,
    down
};
template <int n>
class Scene
{
protected:
    bool selected = false;
    Scene<n> *parent = nullptr;

public:
    virtual void draw() = 0;
    virtual void reloadVertices() = 0;
    virtual Shape<n> *getShape() const = 0;
    virtual void addScene(Scene<n> *scene) = 0;
    virtual ~Scene() = default;
    virtual void Rotate(float degrees) = 0;
    virtual void RotateX(float degrees) = 0;
    virtual void RotateY(float degrees) = 0;
    virtual void RotateZ(float degrees) = 0;
    virtual void Scale(float scale) = 0;
    virtual void Translation(Direction dir, float step) = 0;
    virtual void select() = 0;
    virtual void deselect() = 0;
    virtual void setWireframeMode() = 0;
    virtual void setNormalMode() = 0;
    virtual void setParent(Scene *parent) { this->parent = parent; };
    virtual Scene<n> *selectNext() = 0;
    virtual Scene<n> *getIndex(int i) = 0;
    virtual void transform(Matrix<n + 1, n + 1> &trans, bool toCenter) = 0;
};

#endif

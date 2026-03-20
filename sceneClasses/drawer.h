#ifndef DRAWER_H
#define DRAWER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/MathLibrary/Shape.h"
#include "Scene.h"

template <int n>
class Drawer : public Scene<n>
{
private:
    int numVertices;
    GLuint VAO, VBO;
    GLenum type;

    static const int COLOR_DEPTH = 4;
    static const int VERTEX_DEPTH = n;

    Shape<n> *shape;

public:
    Drawer(Shape<n> *shape, GLenum type);
    void draw() override;
    void reloadVertices() override;
    Shape<n> *getShape() const override;
    void addScene(Scene<n> *scene) override;
    ~Drawer() override;
    virtual void Rotate(float degrees);
    virtual void Scale(float scale);
    virtual void Translation(Direction dir, float step);
    virtual void select();
    virtual void deselect() override;
    virtual void setWireframeMode();
    virtual void setNormalMode();
    virtual Scene<n> *selectNext() { return this; };
    virtual Scene<n> *getIndex(int i)
    {
        return this;
    }
};

#include "drawer.cpp"
#endif

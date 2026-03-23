#ifndef DRAWER_H
#define DRAWER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/MathLibrary/2D shapes/Shape.h"
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
    virtual void RotateX(float degrees);
    virtual void RotateY(float degrees);
    virtual void RotateZ(float degrees);
    virtual void Scale(float scale);
    virtual void Translation(Direction dir, float step);
    virtual void select();
    virtual void deselect() override;
    virtual void setWireframeMode();
    virtual void setNormalMode();
    virtual void transform( Matrix<n+1,n+1> &trans, bool toCenter);
    virtual Scene<n> *selectNext() { return this; };
    virtual Scene<n> *getIndex(int i)
    {
        return this;
    }
};

#include "drawer.cpp"
#endif

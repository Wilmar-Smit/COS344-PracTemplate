#ifndef COMPLETESCENE_H
#define COMPLETESCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/MathLibrary/2D shapes/Shape.h"
#include "../include/MathLibrary/Matrix.h"
#include "../include/MathLibrary/3D_shapes/3D_Shape.h"
#include "complexSceneHolder.h"
#include <vector>

class TotalScene
{

    std::vector<complexSceneHolder *> containers;
    bool selected = false;

public:
    TotalScene();
    virtual ~TotalScene();
    virtual void draw();
    virtual void addScene(complexSceneHolder *);
    virtual void Rotate(float degrees);
    virtual void RotateX(float degrees);
    virtual void RotateY(float degrees);
    virtual void RotateZ(float degrees);
    virtual void Scale(float scale);
    virtual void Translation(Direction dir, float step);

    virtual void select();
    virtual void deselect();
    virtual void setWireframeMode();
    virtual void setNormalMode();
};

#endif

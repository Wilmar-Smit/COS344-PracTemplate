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
 
    TotalScene(); // the passed in center is the shared center amongst all 
    // links to the center of the windmill
    ~TotalScene();
    void draw();
    void addScene(complexSceneHolder *scene);
    void Rotate(float degrees);
    void RotateX(float degrees);
    void RotateY(float degrees);
    void RotateZ(float degrees);
    void Scale(float scale);
    void Translation(Direction dir, float step);

    void select();
    void deselect();
    void setWireframeMode();
    void setNormalMode();
    complexSceneHolder *getIndex(int i)
    {
        if ((i >= 0 && i < containers.size()))
            return this->containers[i];

        return nullptr;
    }
};

#endif

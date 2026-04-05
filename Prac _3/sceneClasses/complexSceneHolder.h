#ifndef COMPLEXSCENEHOLDER_H
#define COMPLEXSCENEHOLDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/MathLibrary/2D shapes/Shape.h"
#include "../include/MathLibrary/Matrix.h"
#include "../include/MathLibrary/3D_shapes/3D_Shape.h"
#include "drawerVisitor.h"
#include <vector>

class complexSceneHolder : public Scene
{
private:
    std::vector<Scene *> visitors;

public:
    complexSceneHolder();
    virtual ~complexSceneHolder();

    virtual void draw();
    virtual void reloadVertices();
    virtual Shape<3> *getShape() const;
    virtual void addScene(Scene *scene);

    virtual void Rotate(float degrees, OrientationObject *orient = nullptr);
    virtual void RotateX(float degrees, OrientationObject *orient = nullptr);
    virtual void RotateY(float degrees, OrientationObject *orient = nullptr);
    virtual void RotateZ(float degrees, OrientationObject *orient = nullptr);
    virtual void Scale(float scale, OrientationObject *orient = nullptr);
    virtual void Translation(Direction dir, float step, OrientationObject *orient = nullptr);
    virtual Matrix<4, 4> transform(Matrix<4, 4> &trans, bool toCenter, OrientationObject *orient = nullptr);
    virtual void RotateArbitrary(float degrees, OrientationObject *orient = nullptr);

    virtual void select();
    virtual void deselect();
    virtual void setWireframeMode();
    virtual void setNormalMode();
    virtual Scene *selectNext();
    virtual Scene *getIndex(int i);
    const std::vector<Scene *> &getVisitors() const { return visitors; }
};

#endif

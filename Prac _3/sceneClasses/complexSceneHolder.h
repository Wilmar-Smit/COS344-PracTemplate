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
    Vector<3> givenCenter;
    std::vector<DrawerVisitor *> visitors;

public:
    complexSceneHolder(_3DShape *shape);
    virtual ~complexSceneHolder();

    virtual void draw();
    virtual void reloadVertices();
    virtual Shape<3> *getShape() const;
    virtual void addScene(Scene *scene) override;
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
    virtual Scene *selectNext();
    virtual Scene *getIndex(int i);
    virtual void transform(Matrix<4, 4> &trans, bool toCenter);

    void setGivenCenter(const Vector<3> &center) { givenCenter = center; }
    Vector<3> getGivenCenter() const { return givenCenter; }

    void addVisitor(DrawerVisitor *visitor) { visitors.push_back(visitor); }
    const std::vector<DrawerVisitor *> &getVisitors() const { return visitors; }
};

#endif

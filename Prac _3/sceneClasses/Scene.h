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
    down,
    forward,
    back
};

class Scene
{

protected:
    bool selected = false;
    OrientationObject *orientation = nullptr;

public:
    virtual void draw() = 0;
    virtual void reloadVertices() = 0;
    virtual Shape<3> *getShape() const = 0;
    virtual void addScene(DrawerVisitor *scene) = 0;
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
    virtual void setParent(Scene *parent) { (void)parent; };
    virtual void transform(Matrix<4, 4> &trans, bool toCenter) = 0;
    virtual void setGivenCenter(const Vector<3> &center) {}
    virtual Vector<3> getGivenCenter() const { return Vector<3>(); }

    virtual void SetMyOrientation(OrientationObject *obj) { this->orientation = obj; };
    virtual OrientationObject *getMyOrientation() { return this->orientation; };
    virtual Vector<3> getRotateDirection()
    {
        if (this->orientation)
        {
            return this->orientation->generateDirection();
        }
        else
            return Vector<3>({0, 0, 0});
    };
};

class OrientationObject
{
private:
    Vector<3> *OPstart;
    Vector<3> *OPend;

public:
    OrientationObject(Vector<3> *OPstart, Vector<3> *OPend, Vector<3> *center) : OPstart(OPstart), OPend(OPend) {};
    // no copy contructor
    Vector<3> generateDirection()
    {
        return *OPend - *OPstart;
    };
    Vector<3> getCenter()
    {
        return (*OPend + *OPstart)* 0.5;
    }
};
#endif

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

class OrientationObject
{
private:
    Vector<3> *OPstart;
    Vector<3> *OPend;

public:
    OrientationObject(Vector<3> *OPstart, Vector<3> *OPend) : OPstart(OPstart), OPend(OPend) {};
    // no copy contructor
    Vector<3> generateDirection()
    {
        return *OPend - *OPstart;
    };
    Vector<3> getCenter()
    {
        return (*OPend + *OPstart) * 0.5;
    }
    void update(Matrix<4, 4> &trans, bool toCenter, OrientationObject *orient = nullptr)
    {
        // Decide which center to use
        Vector<3> center;
        if (toCenter && orient)
            center = orient->getCenter();
        else
            center = getCenter();

        // Build identity matrices
        Matrix<4, 4> toCenterMat, backToOriginMat;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                toCenterMat[i][j] = (i == j) ? 1.0f : 0.0f;
                backToOriginMat[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }

        toCenterMat[0][3] = -center[0];
        toCenterMat[1][3] = -center[1];
        toCenterMat[2][3] = -center[2];

        backToOriginMat[0][3] = center[0];
        backToOriginMat[1][3] = center[1];
        backToOriginMat[2][3] = center[2];

        Matrix<4, 4> fullTransform = trans;
        if (toCenter)
            fullTransform = backToOriginMat * trans * toCenterMat;

        // Homogenize start and end points
        Vector<4> startH({(*OPstart)[0], (*OPstart)[1], (*OPstart)[2], 1.0f});
        Vector<4> endH({(*OPend)[0], (*OPend)[1], (*OPend)[2], 1.0f});

        // Apply transformation
        startH = fullTransform * (Matrix<4, 1>)startH;
        endH = fullTransform * (Matrix<4, 1>)endH;

        // Update stored 3D vectors
        *OPstart = Vector<3>({startH[0], startH[1], startH[2]});
        *OPend = Vector<3>({endH[0], endH[1], endH[2]});
    }
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
    virtual void addScene(Scene *scene) = 0;
    virtual ~Scene() = default;
    virtual void Rotate(float degrees, OrientationObject *orient = nullptr) = 0;
    virtual void RotateX(float degrees, OrientationObject *orient = nullptr) = 0;
    virtual void RotateY(float degrees, OrientationObject *orient = nullptr) = 0;
    virtual void RotateZ(float degrees, OrientationObject *orient = nullptr) = 0;
    virtual void Scale(float scale, OrientationObject *orient = nullptr) = 0;
    virtual void Translation(Direction dir, float step, OrientationObject *orient = nullptr) = 0;
    virtual Matrix<4, 4> transform(Matrix<4, 4> &trans, bool toCenter, OrientationObject *orient = nullptr) = 0;
    virtual void select() = 0;
    virtual void deselect() = 0;
    virtual void setWireframeMode() = 0;
    virtual void setNormalMode() = 0;
    virtual void setParent(Scene *parent) { (void)parent; };

virtual void RotateArbitrary(float degrees, OrientationObject *orient = nullptr) = 0;

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

#endif

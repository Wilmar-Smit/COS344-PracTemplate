#ifndef BORDERSTUB_H
#define BORDERSTUB_H
#include "Vector.h"
#include "2D shapes/Square.h"
#include "3D shapes/3D_Shape.h"
#include "../shapeObservers/borderObserver.h"
class borderStub
{
    friend class BorderContainer;

private:
    void initiateValues(Vector<3> minVals, Vector<3> maxVals);
    borderObserver *obs; // my parents observer to notify about my change

protected:
    Vector<3> frontBottomLeft;
    Vector<3> frontBottomRight;
    Vector<3> frontTopLeft;
    Vector<3> frontTopRight;

    Vector<3> backBottomLeft;
    Vector<3> backBottomRight;
    Vector<3> backTopLeft;
    Vector<3> backTopRight;

public:
    borderStub(Vector<3> minVals, Vector<3> maxVals);
    borderStub(borderStub &stub);
    borderStub(_3DShape<3> *shape);

    virtual Vector<3> *Collision(borderStub *border); // returns a vector of where the collision is blocked from == wall
    virtual void addContainer(borderStub *border);
    virtual _3DShape<3> *getShape(); // likely to be only the golf ball
    virtual ~borderStub();

    virtual void attach(borderObserver *obs);
    virtual void notify();
};

#endif
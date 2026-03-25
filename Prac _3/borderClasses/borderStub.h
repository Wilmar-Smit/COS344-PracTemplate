#ifndef BORDERSTUB_H
#define BORDERSTUB_H
#include "Vector.h"
#include "2D shapes/Square.h"

class borderObserver;
class _3DShape;

class borderStub
{
    friend class BorderContainer;

protected:
    void initiateValues(Vector<3> minVals, Vector<3> maxVals);
    borderObserver *obs = nullptr; // my parents observer to notify about my change
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
    borderStub(_3DShape *shape);

    virtual Vector<3> *Collision(borderStub *border); // returns a vector of where the collision is blocked from == wall
    virtual void addContainer(borderStub *border);
    virtual _3DShape *getShape(); // likely to be only the golf ball
    virtual ~borderStub();

    virtual void attach(borderObserver *obs);
    virtual void notify();
    virtual void recalculateCol(_3DShape *shape);
};

#endif
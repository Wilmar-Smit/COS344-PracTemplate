#ifndef BORDEROBSERVER_H
#define BORDEROBSERVER_H
#include "../include/MathLibrary/3D shapes/3D_Shape.h"
#include "../borderClasses/borderStub.h"
// tells a border to check its boundary again
class borderObserver
{
private:
    borderStub *borderParent;

public:
    borderObserver(_3DShape<3> *shape = nullptr, borderStub *borderParent);
    // calls shape.attach
    void notify(); // tells border to change recalculate its vertices
    void notify(borderStub *resizeTo);
};

#endif
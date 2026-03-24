#ifndef BORDEROBSERVER_H
#define BORDEROBSERVER_H

#include "../borderClasses/borderStub.h"
// tells a border to check its boundary again

class borderObserver
{
private:
    borderStub *borderParent = nullptr;

public:
    borderObserver(borderStub *borderParent, _3DShape<3> *shape = nullptr);
    // calls shape.attach
    void notify(); // tells border to change recalculate its vertices
};

#endif
#include "borderObserver.h"
#include "../include/MathLibrary/3D_shapes/3D_Shape.h"
borderObserver::borderObserver(borderStub *borderParent, _3DShape *shape)
{
    if (shape)
        shape->attach(this);
        
    this->borderParent = borderParent;
}

void borderObserver::notify()
{
    if (borderParent)
        this->borderParent->notify();
}

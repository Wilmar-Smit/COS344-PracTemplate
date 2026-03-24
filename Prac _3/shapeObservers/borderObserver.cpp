#include "borderObserver.h"

borderObserver::borderObserver(_3DShape<3> *shape, borderStub *borderParent)
{
    if (shape)
        shape->attach(this);
    this->borderParent = borderParent;
}

void borderObserver::notify()
{
}
void notify(borderStub *resizeTo)
{
}
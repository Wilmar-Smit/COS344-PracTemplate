#ifndef BORDERCONTAINER_H
#define BORDERCONTAINER_H
#include "borderStub.h"
#include <vector>
class BorderContainer : public borderStub
{
    std::vector<borderStub *> boxes;
    borderObserver *myObserver = nullptr;
    void updateSize();

public:
    BorderContainer(borderStub *border);
    virtual Vector<3> *Collision(borderStub *border);
    virtual ~BorderContainer();
    virtual void addContainer(borderStub *border);
    virtual void notify();
};

#endif

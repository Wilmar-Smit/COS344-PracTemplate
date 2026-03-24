#ifndef BORDERSHAPE_H
#define BORDERSHAPE_H
#include "borderStub.h"

class BorderShape : public borderStub
{
    _3DShape<3> *shape;

public:
    BorderShape(_3DShape<3>* shape); // needs to build this based on shapes inside its container
    virtual Vector<3> *Collision(borderStub *border);  // if this one collides it needs to to fetch the shape in question to get its center to know which side its closest to before collision
    // the theory is to move border boxes before shapes in terms of translation only collisions via rotation are not accounted for
    // so shape stays still but its box will move if collision calculated the wall it would be his
    virtual ~BorderShape();
    virtual _3DShape<3> *getShape();
};

#endif

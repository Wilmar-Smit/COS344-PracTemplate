#ifndef CUBOID_H
#define CUBOID_H

#include "../Matrix.h"
#include "../Vector.h"
#include <vector>
#include "3D_Shape.h"
#include "../2D_shapes/Square.h"

class Cuboid : public _3DShape
{
    friend class borderStub;
    friend class DrawerVisitor;
    Square *base;
    Square *leftSide;
    Square *rightSide;
    Square *top;
    Square *front;
    Square *back;

    Colour col;

public:
    Cuboid(Square base, float height, Colour col);
    Cuboid(const Cuboid &other);
    void generateSides();
    virtual Vector<3> getCenter() override;
    virtual void getBorders(Vector<3> &min, Vector<3> &max) override;
    virtual void acceptVisitor(DrawerVisitor *vis) override;
    virtual ~Cuboid()
    {
        delete leftSide;
        delete top;
        delete base;
        delete back;
        delete front;
        delete rightSide;
    }
};

#endif /* CUBOID_H */

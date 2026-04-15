#ifndef TRIANGULARPRISM_H
#define TRIANGULARPRISM_H

#include "../Matrix.h"
#include "../Vector.h"
#include <vector>
#include "3D_Shape.h"
#include "2D_shapes/Triangle.h"

class TriangularPrism : public _3DShape
{
    friend class DrawerVisitor;
    Square *base;
    Square *rightTop;
    Square *leftTop;
    Triangle *leftSide;
    Triangle *rightSide;
    float height = 0;

public:
    TriangularPrism(Square base, float height, Colour col);
    TriangularPrism(const TriangularPrism &other);

    virtual Vector<3> getCenter() override;
    virtual void getBorders(Vector<3> &min, Vector<3> &max) override;
    virtual void acceptVisitor(DrawerVisitor *vis) override;
    virtual ~TriangularPrism()
    {
        delete base;
        delete rightTop;
        delete leftTop;
        delete leftSide;
        delete rightSide;
    }
};

#endif /* TRIANGULARPRISM_H */

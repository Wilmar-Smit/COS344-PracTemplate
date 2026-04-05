#ifndef SQUAREPYRAMID_H
#define SQUAREPYRAMID_H

#include "../Matrix.h"
#include "../Vector.h"
#include "../2D_shapes/Square.h"
#include "../2D_shapes/Triangle.h"
#include "3D_Shape.h"

class SquarePyramid : public _3DShape
{
    friend class DrawerVisitor;
private:
    Square *base;
    float height;
    Vector<3> extrusion;
    Triangle *side1;
    Triangle *side2;
    Triangle *side3;
    Triangle *side4;

public:
    SquarePyramid(const Square &sq, float h, Colour col);
    SquarePyramid(const Square &sq, const Vector<3> &extrude, Colour col);
    SquarePyramid(const SquarePyramid &other);

    virtual Vector<3> getCenter();
    virtual void getBorders(Vector<3> &min, Vector<3> &max) override;
    virtual ~SquarePyramid()
    {
        delete base;
        delete side1;
        delete side2;
        delete side3;
        delete side4;
    }

    virtual void acceptVisitor(DrawerVisitor *vis) override;
};

#endif /* SQUAREPYRAMID_H */

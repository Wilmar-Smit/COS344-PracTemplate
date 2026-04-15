#ifndef CONE_H
#define CONE_H

#include "../Matrix.h"
#include "../Vector.h"
#include <vector>
#include "../2D_shapes/circle.h"
#include "3D_Shape.h"
#include "../2D_shapes/Triangle.h"

class Cone : public _3DShape
{
    friend class DrawerVisitor;

private:
    int height;
    Circle *base;
    Vector<3> point;
    std::vector<Triangle *> sides;

    void generateSides();

public:
    Cone(Circle base, float height, Colour col);
    Cone(const Cone &other);
    virtual Vector<3> getCenter() override;
    virtual void getBorders(Vector<3> &min, Vector<3> &max) override;
    virtual void acceptVisitor(DrawerVisitor *vis) override;
    virtual ~Cone()
    {
        delete this->base;
        for (int i = 0; i < sides.size(); i++)
        {
            delete sides[i];
        }
    }
};

#endif /* CONE_H */

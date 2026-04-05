#ifndef Cylinder_H
#define Cylinder_H

#include "../Matrix.h"
#include "../Vector.h"
#include <vector>
#include "3D_shapes/3D_Shape.h"

class Cylinder : public _3DShape
{
    friend class DrawerVisitor;
    Circle *base;
    Circle *top;
    float height;
    std::vector<Square *> sides;
    void generateSides();

public:
    Cylinder(Circle base, float height, Colour col);
    Cylinder(const Cylinder &other);
    virtual Vector<3> getCenter() override;
    virtual void getBorders(Vector<3> &min, Vector<3> &max) override;
    virtual ~Cylinder()
    {
        delete base;
        delete top;
        for (std::size_t i = 0; i < sides.size(); i++)
        {
            delete sides[i];
        }
        sides.clear();
    }

    virtual void acceptVisitor(DrawerVisitor *vis) override;
};

#endif /* Cylinder_H */

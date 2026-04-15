#include "SquarePyramid.h"
#include "../../../sceneClasses/drawerVisitor.h"
#include "../2D_shapes/Triangle.h"

SquarePyramid::SquarePyramid(const Square &sq, float h, Colour col)
    : _3DShape(col)
{
    this->base = new Square(sq);
    this->extrusion = base->getCenter();
    this->extrusion[2] += h;
    this->height = h;
    side1 = new Triangle(sq.tl, sq.tr, extrusion, col);
    side2 = new Triangle(sq.tr, sq.br, extrusion, col);
    side3 = new Triangle(sq.br, sq.bl, extrusion, col);
    side4 = new Triangle(sq.bl, sq.tl, extrusion, col);
    this->orientation = new OrientationObject(new Vector<3>(this->extrusion), new Vector<3>(this->base->getCenter()));
}

SquarePyramid::SquarePyramid(const Square &sq, const Vector<3> &extrude, Colour col)
    : _3DShape(col)
{
    this->base = new Square(sq);
    this->extrusion = extrude;
    this->height = extrude[2];

    side1 = new Triangle(sq.tl, sq.tr, extrusion);
    side2 = new Triangle(sq.tr, sq.br, extrusion);
    side3 = new Triangle(sq.br, sq.bl, extrusion);
    side4 = new Triangle(sq.bl, sq.tl, extrusion);
}

SquarePyramid::SquarePyramid(const SquarePyramid &other)
    : _3DShape(other.colour)
{
    this->colour = other.colour;
    this->base = new Square(*other.base);
    this->height = other.height;
    this->extrusion = other.extrusion;

    side1 = new Triangle(*other.side1);
    side2 = new Triangle(*other.side2);
    side3 = new Triangle(*other.side3);
    side4 = new Triangle(*other.side4);
}

Vector<3> SquarePyramid::getCenter()
{
    return this->orientation->getCenter();
}

void SquarePyramid::getBorders(Vector<3> &min, Vector<3> &max)
{
    std::vector<Vector<3>> points = {
        base->bl, base->br, base->tl, base->tr,
        extrusion};

    Vector<3> first = points[0];
    min = Vector<3>({first[0], first[1], first[2]});
    max = Vector<3>({first[0], first[1], first[2]});

    for (int i = 0; i < points.size(); i++)
    {
        Vector<3> p = points[i];
        if (p[0] < min[0])
            min[0] = p[0];
        if (p[1] < min[1])
            min[1] = p[1];
        if (p[2] < min[2])
            min[2] = p[2];

        if (p[0] > max[0])
            max[0] = p[0];
        if (p[1] > max[1])
            max[1] = p[1];
        if (p[2] > max[2])
            max[2] = p[2];
    }
}

void SquarePyramid::acceptVisitor(DrawerVisitor *vis)
{
    vis->Visit(this);
}

#include "TriangularPrism.h"
#include "../../../sceneClasses/drawerVisitor.h"

TriangularPrism::TriangularPrism(Square baseParam, float height, Colour col) : _3DShape(col)
{
    this->base = new Square(baseParam);
    Vector<3> mid_left = (this->base->bl + this->base->tl) * 0.5;
    Vector<3> mid_right = (this->base->br + this->base->tr) * 0.5;

    this->height = height;

    mid_left[2] += height;
    mid_right[2] += height;

    leftSide = new Triangle(base->bl, base->tl, mid_left, col);
    rightSide = new Triangle(base->br, base->tr, mid_right, col);

    rightTop = new Square(mid_left, mid_right, base->br, base->bl, col);
    leftTop = new Square(mid_left, mid_right, base->tr, base->tl, col);

    Vector<3> topCen = this->base->getCenter();
    topCen[2] += height;
    this->orientation = new OrientationObject(new Vector<3>(this->base->getCenter()), new Vector<3>(topCen));
}

TriangularPrism::TriangularPrism(const TriangularPrism &other) : _3DShape(other.colour)
{
    this->colour = other.colour;
}

Vector<3> TriangularPrism::getCenter()
{
    return this->orientation->getCenter();
}

void TriangularPrism::getBorders(Vector<3> &min, Vector<3> &max)
{
    std::vector<Vector<3>> points = {
        base->bl, base->br, base->tl, base->tr,
        leftSide->p3, rightSide->p3};

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

void TriangularPrism::acceptVisitor(DrawerVisitor *vis)
{
    vis->Visit(this);
}

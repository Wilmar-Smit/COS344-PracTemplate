#include "Cuboid.h"
#include "../../../sceneClasses/drawerVisitor.h"

Cuboid::Cuboid(Square baseParam, float height, Colour col) : _3DShape(col)
{
    this->base = new Square(baseParam);

    this->top = new Square(baseParam);
    top->bl[2] += height;
    top->tr[2] += height;
    top->br[2] += height;
    top->tl[2] += height;

    this->orientation = new OrientationObject(new Vector<3>(base->getCenter()), new Vector<3>(top->getCenter()));
    generateSides();
}

void Cuboid::generateSides()
{
    this->front = new Square(Colour::White);
    this->front->setSurface(this->getSurface());
    front->tl = top->bl;
    front->tr = top->br;
    front->bl = base->bl;
    front->br = base->br;

    this->back = new Square(Colour::White);
    this->back->setSurface(this->getSurface());
    back->tl = top->tl;
    back->tr = top->tr;
    back->bl = base->tl;
    back->br = base->tr;

    this->leftSide = new Square(Colour::White);
    this->leftSide->setSurface(this->getSurface());
    leftSide->tl = top->tl;
    leftSide->tr = top->bl;
    leftSide->bl = base->tl;
    leftSide->br = base->bl;

    this->rightSide = new Square(Colour::White);
    this->rightSide->setSurface(this->getSurface());
    rightSide->tl = top->tr;
    rightSide->tr = top->br;
    rightSide->bl = base->tr;
    rightSide->br = base->br;
}

Cuboid::Cuboid(const Cuboid &other) : _3DShape(Colour::White)
{
    this->setSurface(other.getSurface());
}

Vector<3> Cuboid::getCenter()
{
    return this->orientation->getCenter();
}

void Cuboid::getBorders(Vector<3> &min, Vector<3> &max)
{
    Vector<3> first = base->bl;
    min = Vector<3>({first[0], first[1], first[2]});
    max = Vector<3>({first[0], first[1], first[2]});

    std::vector<Vector<3>> points = {
        base->bl, base->br, base->tl, base->tr,
        top->bl, top->br, top->tl, top->tr};

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

void Cuboid::acceptVisitor(DrawerVisitor *vis)
{
    vis->Visit(this);
}

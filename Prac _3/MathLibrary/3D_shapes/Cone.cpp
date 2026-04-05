#include "Cone.h"
#include "../../../sceneClasses/drawerVisitor.h"

Cone::Cone(Circle base, float height, Colour col)
    : _3DShape(col), base(new Circle(base))
{
    point = base.getCenter();
    point[2] += height;
    this->height = height;
    this->orientation = new OrientationObject(new Vector<3>(point), new Vector<3>(base.getCenter()));
    generateSides();
}

Cone::Cone(const Cone &other)
    : _3DShape(other.colour), base(new Circle(*other.base)), sides()
{
    this->colour = other.colour;
    this->height = other.height;
    this->point = other.point;
    generateSides();
}

void Cone::generateSides()
{
    for (int i = 0; i < sides.size(); i++)
        delete sides[i];
    sides.clear();

    std::vector<Vector<3>> baseSides = base->getVectors();
    for (int i = 0; i < base->getNumSides(); i++)
    {
        int next;
        if (i + 1 == baseSides.size())
            next = 0;
        else
            next = i + 1;

        Vector<3> bl = baseSides[i];
        Vector<3> br = baseSides[next];
        sides.push_back(new Triangle(bl, br, point, this->colour));
    }
}

Vector<3> Cone::getCenter()
{
    return this->orientation->getCenter();
}

void Cone::getBorders(Vector<3> &min, Vector<3> &max)
{
    std::vector<Vector<3>> baseVectors = base->getVectors();

    Vector<3> firstPoint = point;
    if (!baseVectors.empty())
        firstPoint = baseVectors[0];

    min = Vector<3>({firstPoint[0], firstPoint[1], firstPoint[2]});
    max = Vector<3>({firstPoint[0], firstPoint[1], firstPoint[2]});

    for (int i = 0; i < baseVectors.size(); i++)
    {
        Vector<3> v = baseVectors[i];
        if (v[0] < min[0])
            min[0] = v[0];
        if (v[1] < min[1])
            min[1] = v[1];
        if (v[2] < min[2])
            min[2] = v[2];

        if (v[0] > max[0])
            max[0] = v[0];
        if (v[1] > max[1])
            max[1] = v[1];
        if (v[2] > max[2])
            max[2] = v[2];
    }

    if (point[0] < min[0])
        min[0] = point[0];
    if (point[1] < min[1])
        min[1] = point[1];
    if (point[2] < min[2])
        min[2] = point[2];

    if (point[0] > max[0])
        max[0] = point[0];
    if (point[1] > max[1])
        max[1] = point[1];
    if (point[2] > max[2])
        max[2] = point[2];
}

void Cone::acceptVisitor(DrawerVisitor *vis)
{
    vis->Visit(this);
}

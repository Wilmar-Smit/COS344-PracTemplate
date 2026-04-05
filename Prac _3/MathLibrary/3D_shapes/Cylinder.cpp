#include "Cylinder.h"
#include "../../../sceneClasses/drawerVisitor.h"

Cylinder::Cylinder(Circle baseCircle, float height, Colour col)
    : _3DShape(col), base(new Circle(baseCircle)), top(new Circle(baseCircle))
{
    std::vector<Vector<3>> topVectors = top->getVectors();
    for (int i = 0; i < topVectors.size(); i++)
    {
        topVectors[i][2] += height;
    }
    top->setVectors(topVectors);
    this->height = height;
    this->orientation = new OrientationObject(new Vector<3>(base->getCenter()), new Vector<3>(top->getCenter()));
    generateSides();
}

void Cylinder::generateSides()
{
    for (int i = 0; i < sides.size(); i++)
    {
        delete sides[i];
    }
    sides.clear();

    std::vector<Vector<3>> baseSides = base->getVectors();
    std::vector<Vector<3>> topSides = top->getVectors();

    if (baseSides.size() < 3 || topSides.size() != baseSides.size())
    {
        return;
    }

    for (int i = 0; i < baseSides.size(); i++)
    {
        int next;
        if (i + 1 == baseSides.size())
            next = 0;
        else
            next = i + 1;

        Vector<3> bottomCurrent = baseSides[i];
        Vector<3> bottomNext = baseSides[next];
        Vector<3> topCurrent = topSides[i];
        Vector<3> topNext = topSides[next];

        sides.push_back(new Square(bottomCurrent, topCurrent, topNext, bottomNext, this->colour));
    }
}

Cylinder::Cylinder(const Cylinder &other)
    : _3DShape(other.colour), base(new Circle(*other.base)), top(new Circle(*other.top)), sides()
{
    this->colour = other.colour;
    this->height = other.height;
    generateSides();
}

Vector<3> Cylinder::getCenter()
{
    return this->orientation->getCenter();
}

void Cylinder::getBorders(Vector<3> &min, Vector<3> &max)
{
    std::vector<Vector<3>> baseVectors = base->getVectors();
    std::vector<Vector<3>> topVectors = top->getVectors();

    Vector<3> first = base->getCenter();
    if (!baseVectors.empty())
        first = baseVectors[0];
    else if (!topVectors.empty())
        first = topVectors[0];

    min = Vector<3>({first[0], first[1], first[2]});
    max = Vector<3>({first[0], first[1], first[2]});

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

    for (int i = 0; i < topVectors.size(); i++)
    {
        Vector<3> v = topVectors[i];
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
}

void Cylinder::acceptVisitor(DrawerVisitor *vis)
{
    vis->Visit(this);
}

#include "Sphere.h"
#include "../../../sceneClasses/drawerVisitor.h"
#include <algorithm>

Sphere::Sphere(Vector<3> centerVec, float rad, int numSectors, int stacks, Colour col)
    : _3DShape(col)
{
    this->radius = rad;
    this->stacks = std::max(2, stacks);
    this->numSectors = std::max(3, numSectors);

    // Keep quads closer to square by ensuring enough horizontal slices for the
    // chosen vertical stack count. This increases side density around the sphere.
    this->numSectors = std::max(this->numSectors, this->stacks * 4);

    this->centerCircle = new Circle(centerVec, rad, this->numSectors, col);

    Vector<3> topVec = centerVec;
    topVec[2] += rad;
    Vector<3> bottomVec = centerVec;
    bottomVec[2] -= rad;
    this->topCenter = new Square(topVec, 0, 0, Colour::Invisible);
    this->bottomCenter = new Square(bottomVec, 0, 0.0, Colour::Invisible);

    this->allSides.push_back(topCenter);
    this->allSides.push_back(bottomCenter);
    DeltaY = radius / stacks;
    this->orientation = new OrientationObject(new Vector<3>(this->topCenter->getCenter()), new Vector<3>(bottomCenter->getCenter()));
    generateSides();
}

Sphere::Sphere(const Sphere &other)
    : _3DShape(Colour::White)
{
    this->setSurface(other.getSurface());
}

void Sphere::generateSides()
{
    for (int i = 0; i < stacks; i++)
    {
        float heightUp = yk(i);
        float tempRad = radY(heightUp);
        Vector<3> tempCen = this->centerCircle->getCenter();
        tempCen[2] += heightUp;
        Circle *tempCircle = new Circle(tempCen, tempRad, numSectors, Colour::Invisible);
        tempCircle->setSurface(this->getSurface());

        circlesTop.push_back(tempCircle);
    }
    for (int i = 0; i < stacks; i++)
    {
        float heightDown = -yk(i);
        float tempRad = radY(heightDown);
        Vector<3> tempCen = this->centerCircle->getCenter();
        tempCen[2] += heightDown;
        Circle *tempCircle = new Circle(tempCen, tempRad, numSectors, Colour::Invisible);
        tempCircle->setSurface(this->getSurface());
        circlesBottom.push_back(tempCircle);
    }

    for (int i = 0; i < stacks; i++)
    {
        int nextCircle = 0;
        if (i + 1 == stacks)
            break;
        else
            nextCircle = i + 1;

        std::vector<Vector<3>> baseSides = circlesTop[i]->getVectors();
        std::vector<Vector<3>> topSides = circlesTop[nextCircle]->getVectors();
        addSides(baseSides, topSides);
    }

    for (int i = 0; i < stacks; i++)
    {
        int nextCircle = 0;
        if (i + 1 == stacks)
            break;
        else
            nextCircle = i + 1;

        std::vector<Vector<3>> baseSides = circlesBottom[i]->getVectors();
        std::vector<Vector<3>> topSides = circlesBottom[nextCircle]->getVectors();
        addSides(baseSides, topSides);
    }

    for (int i = 0; i < stacks; i++)
    {
        int nextCircle = 0;
        if (i + 1 == stacks)
            break;
        else
            nextCircle = i + 1;

        std::vector<Vector<3>> baseSides = circlesTop[i]->getVectors();
        std::vector<Vector<3>> topSides = circlesTop[nextCircle]->getVectors();

        Vector<3> bottomCurrent = baseSides[1];
        Vector<3> bottomNext = baseSides[baseSides.size() - 2];
        Vector<3> topCurrent = topSides[1];
        Vector<3> topNext = topSides[topSides.size() - 2];

        Square *square = new Square(bottomCurrent, topCurrent, topNext, bottomNext, Colour::White);
        square->setSurface(this->getSurface());
        allSides.push_back(square);
    }
    for (int i = 0; i < stacks; i++)
    {
        int nextCircle = 0;
        if (i + 1 == stacks)
            break;
        else
            nextCircle = i + 1;

        std::vector<Vector<3>> baseSides = circlesBottom[i]->getVectors();
        std::vector<Vector<3>> topSides = circlesBottom[nextCircle]->getVectors();

        Vector<3> bottomCurrent = baseSides[1];
        Vector<3> bottomNext = baseSides[baseSides.size() - 2];
        Vector<3> topCurrent = topSides[1];
        Vector<3> topNext = topSides[topSides.size() - 2];

        Square *square = new Square(bottomCurrent, topCurrent, topNext, bottomNext, Colour::White);
        square->setSurface(this->getSurface());
        allSides.push_back(square);
    }
    std::vector<Vector<3>> topSides = circlesTop[circlesTop.size() - 1]->getVectors();
    for (int i = 1; i < numSectors; i++)
    {
        int next;
        if (i + 1 == topSides.size())
            next = 0;
        else
            next = i + 1;

        Vector<3> bottomCurrent = topSides[i];
        Vector<3> bottomNext = topSides[next];

        Triangle *triangle = new Triangle(bottomCurrent, bottomNext, topCenter->getCenter(), Colour::White);
        triangle->setSurface(this->getSurface());
        allSides.push_back(triangle);
    }
    Vector<3> bottomCurrent = topSides[1];
    Vector<3> bottomNext = topSides[topSides.size() - 2];
    Triangle *topCap = new Triangle(bottomCurrent, bottomNext, topCenter->getCenter(), Colour::White);
    topCap->setSurface(this->getSurface());
    allSides.push_back(topCap);

    std::vector<Vector<3>> bottomSides = circlesBottom[circlesBottom.size() - 1]->getVectors();
    for (int i = 1; i < numSectors; i++)
    {
        int next;
        if (i + 1 == bottomSides.size())
            next = 0;
        else
            next = i + 1;

        Vector<3> bottomCurrent = bottomSides[i];
        Vector<3> bottomNext = bottomSides[next];

        Triangle *triangle = new Triangle(bottomCurrent, bottomNext, bottomCenter->getCenter(), Colour::White);
        triangle->setSurface(this->getSurface());
        allSides.push_back(triangle);
    }
    bottomCurrent = bottomSides[1];
    bottomNext = bottomSides[topSides.size() - 2];
    Triangle *bottomCap = new Triangle(bottomCurrent, bottomNext, bottomCenter->getCenter(), Colour::White);
    bottomCap->setSurface(this->getSurface());
    allSides.push_back(bottomCap);
}

void Sphere::addSides(std::vector<Vector<3>> baseSides, std::vector<Vector<3>> topSides)
{
    for (int j = 1; j < numSectors; j++)
    {
        int next;
        if (j + 1 == baseSides.size())
            next = 0;
        else
            next = j + 1;

        Vector<3> bottomCurrent = baseSides[j];
        Vector<3> bottomNext = baseSides[next];
        Vector<3> topCurrent = topSides[j];
        Vector<3> topNext = topSides[next];

        Square *square = new Square(bottomCurrent, topCurrent, topNext, bottomNext, Colour::White);
        square->setSurface(this->getSurface());
        allSides.push_back(square);
    }
}

Vector<3> Sphere::getCenter()
{
    return centerCircle->getCenter();
}

void Sphere::getBorders(Vector<3> &min, Vector<3> &max)
{
    Vector<3> center = centerCircle->getCenter();
    min = Vector<3>({center[0] - radius, center[1] - radius, center[2] - radius});
    max = Vector<3>({center[0] + radius, center[1] + radius, center[2] + radius});
}

void Sphere::acceptVisitor(DrawerVisitor *vis)
{
    vis->Visit(this);
}

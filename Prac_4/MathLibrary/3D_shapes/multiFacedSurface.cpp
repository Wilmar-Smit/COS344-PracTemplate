#include "multiFacedSurface.h"
#include "../../sceneClasses/drawerVisitor.h"

MultiFacedSurface::MultiFacedSurface(Vector<3> center, float width, float height, int numSquares, Colour col)
    : _3DShape(col), numSquaresPside(numSquares), width(width), height(height), center(center)
{
    if (numSquares <= 0)
    {
        throw "Cannot have 0 sqrs";
    }
    if (width <= 0 || height <= 0)
    {
        throw "cannot have width or height of 0";
    }

    this->orientation = nullptr;
    generateSides();
}
void MultiFacedSurface::generateSides()
{
    // if odd numSides then center shares a center with a sqr
    // if even numSides then center is between 4 sqrs for numsides > 2

    for (auto square : squares)
    {
        delete square;
    }
    squares.clear();

    if (this->numSquaresPside % 2 != 0)
    {
        XLoopOdd(true);
        XLoopOdd(false);
    }
    else
    {
        XLoopEven(true);
        XLoopEven(false);
    }

    Vector<3> orientStart = this->center;
    Vector<3> orientEnd = this->center;
    orientStart[0] += width;
    orientEnd[0] -= width;
    this->orientation = new OrientationObject(new Vector<3>(orientStart), new Vector<3>(orientEnd));
}
void MultiFacedSurface::XLoopEven(bool Sign)
{
    float widthOfSquares = width / numSquaresPside;

    int start = 0;
    int signVal = Sign ? 1 : -1;

    for (int i = start; i < numSquaresPside / 2; i++)
    {
        float X = center[0] + (signVal) * ((i + 0.5f) * widthOfSquares);
        YLoopEven(X, true);
        YLoopEven(X, false);
    }
}
void MultiFacedSurface::YLoopEven(float X, bool Sign)
{
    float heightOfSquares = height / numSquaresPside;
    float widthOfSquares = width / numSquaresPside;

    int start = 0;
    int signVal = Sign ? 1 : -1;

    for (int i = start; i < numSquaresPside / 2; i++)
    {
        float Y = center[1] + (signVal) * ((i + 0.5f) * heightOfSquares);

        Square *square = new Square({X, Y, center[2]}, heightOfSquares, widthOfSquares, Colour::White);
        square->setSurface(this->getSurface());
        this->squares.push_back(square);
    }
}

void MultiFacedSurface::XLoopOdd(bool Sign)
{
    float widthOfSquares = width / numSquaresPside;

    int start = Sign ? 0 : 1;
    int signVal = Sign ? 1 : -1;

    for (int i = start; i <= numSquaresPside / 2; i++)
    {
        float X = center[0] + (signVal)*i * (widthOfSquares);
        YLoopOdd(X, true);
        YLoopOdd(X, false);
    }
}
void MultiFacedSurface::YLoopOdd(float X, bool Sign) // x just says along what line are ys being built
{
    float heightOfSquares = height / numSquaresPside;
    float widthOfSquares = width / numSquaresPside;

    int start = Sign ? 0 : 1;
    int signVal = Sign ? 1 : -1;

    for (int i = start; i <= numSquaresPside / 2; i++)
    {
        float Y = center[1] + (signVal)*i * heightOfSquares;

        Square *square = new Square({X, Y, center[2]}, heightOfSquares, widthOfSquares, Colour::White);
        square->setSurface(this->getSurface());
        this->squares.push_back(square);
    }
}

MultiFacedSurface::~MultiFacedSurface()
{
    for (auto square : squares)
    {
        delete square;
    }
    squares.clear();
}

Vector<3> MultiFacedSurface::getCenter()
{
    if (this->orientation)
    {
        return this->orientation->getCenter();
    }
    return this->center;
}

void MultiFacedSurface::acceptVisitor(DrawerVisitor *vis)
{

    vis->Visit(this);
}

void MultiFacedSurface::getBorders(Vector<3> &min, Vector<3> &max)
{

    min = Vector<3>{0.0f, 0.0f, 0.0f};
    max = Vector<3>{0.0f, 0.0f, 0.0f};
}

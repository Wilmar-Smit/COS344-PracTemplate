#include "multiFacedSurface.h"
#include "../../sceneClasses/drawerVisitor.h"

float *MultiFacedSurface::getPoints() const
{
    int totalFloats = getNumPoints();
    float *arr = new float[totalFloats];

    int offset = 0;
    for (Shape *squareShape : squares)
    {
        float *squarePoints = squareShape->getPoints();
        int numFloats = squareShape->getNumPoints();
        for (int i = 0; i < numFloats; i++)
        {
            arr[offset++] = squarePoints[i];
        }

        delete[] squarePoints;
    }

    return arr;
}

float *MultiFacedSurface::exportWireframe()
{
    const int stride = getN() + 4;
    const int totalVertices = getWireframeVertexCount();
    float *retValues = new float[totalVertices * stride];

    int offset = 0;
    for (Shape *squareShape : squares)
    {
        const int squareVerts = squareShape->getWireframeVertexCount();
        float *squareWire = squareShape->exportWireframe();

        for (int i = 0; i < squareVerts * stride; i++)
        {
            retValues[offset++] = squareWire[i];
        }

        delete[] squareWire;
    }

    return retValues;
}

int MultiFacedSurface::getNumPoints() const
{
    int total = 0;
    for (Shape *s : squares)
    {
        total += s->getNumPoints();
    }
    return total;
}

int MultiFacedSurface::getWireframeVertexCount() const
{
    int total = 0;
    for (Shape *squareShape : squares)
    {
        total += squareShape->getWireframeVertexCount();
    }
    return total;
}

int MultiFacedSurface::getNumSides() const
{
    return (int)squares.size();
}

void MultiFacedSurface::print() const
{
}

std::vector<Vector<3>> MultiFacedSurface::getVectors()
{
    std::vector<Vector<3>> vectors;
    vectors.reserve(squares.size() * 4);
    for (Shape *squareShape : squares)
    {
        std::vector<Vector<3>> squareVecs = squareShape->getVectors();
        vectors.insert(vectors.end(), squareVecs.begin(), squareVecs.end());
    }
    return vectors;
}

void MultiFacedSurface::setVectors(std::vector<Vector<3>> vec)
{
    const size_t expected = squares.size() * 4;
    if (vec.size() != expected)
    {
        return;
    }

    size_t offset = 0;
    for (Shape *squareShape : squares)
    {
        std::vector<Vector<3>> squareVecs(4);
        for (int i = 0; i < 4; i++)
        {
            squareVecs[i] = vec[offset + i];
        }
        squareShape->setVectors(squareVecs);
        offset += 4;
    }
}

std::vector<Vector<2>> MultiFacedSurface::calculateUV()
{
    std::vector<Vector<2>> uvs;
    uvs.reserve(getNumPoints() / 3);

    const float minX = center[0] - width / 2.0f;
    const float minY = center[1] - height / 2.0f;

    for (Shape *squareShape : squares)
    {
        float *squarePoints = squareShape->getPoints();

        int numVerts = squareShape->getNumPoints() / 3;
        for (int i = 0; i < numVerts; i++)
        {
            const float x = squarePoints[i * 3 + 0];
            const float y = squarePoints[i * 3 + 1];

            const float u = (width != 0.0f) ? ((x - minX) / width) : 0.0f;
            const float v = (height != 0.0f) ? ((y - minY) / height) : 0.0f;

            uvs.push_back(Vector<2>({u, v}));
        }

        delete[] squarePoints;
    }

    return uvs;
}

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

    if (this->orientation)
        delete this->orientation;
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

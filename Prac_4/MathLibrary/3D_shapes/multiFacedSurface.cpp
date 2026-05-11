#include "multiFacedSurface.h"
#include "../../sceneClasses/drawerVisitor.h"
#include "../../camera/camera.h"

// Bilinear interpolation across a quad defined by tl, tr, br, bl
Vector<3> bilerpQuad(const Vector<3> &tl, const Vector<3> &tr,
                     const Vector<3> &br, const Vector<3> &bl,
                     float u, float v)
{
    Vector<3> p;
    for (int i = 0; i < 3; i++)
    {
        // Each corner contributes with a weight based on (u,v):
        // (1-u)(1-v) → bottom-left
        // u(1-v)     → bottom-right
        // (1-u)v     → top-left
        // uv         → top-right   
        p[i] = tl[i] * ((1.0f - u) * v) +     // top-left contribution
               tr[i] * (u * v) +              // top-right contribution
               bl[i] * ((1.0f - u) * (1.0f - v)) + // bottom-left contribution
               br[i] * (u * (1.0f - v));      // bottom-right contribution
    }
    return p;
}


static void addVertex(float *arr, int &offset, const Vector<3> &v)
{
    for (int k = 0; k < 3; k++)
        arr[offset++] = v[k];
}

float *MultiFacedSurface::getPoints() const
{
    int totalFloats = getNumPoints();
    float *arr = new float[totalFloats];
    int offset = 0;
    int N = numSquaresPside;

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            int rowStart = j * (N + 1);
            int nextRowStart = (j + 1) * (N + 1);

            const Vector<3> &v_tl = grid[rowStart + i];
            const Vector<3> &v_tr = grid[rowStart + i + 1];
            const Vector<3> &v_bl = grid[nextRowStart + i];
            const Vector<3> &v_br = grid[nextRowStart + i + 1];

            // Triangle 1: tl, tr, br
            addVertex(arr, offset, v_tl);
            addVertex(arr, offset, v_tr);
            addVertex(arr, offset, v_br);

            // Triangle 2: tl, br, bl
            addVertex(arr, offset, v_tl);
            addVertex(arr, offset, v_br);
            addVertex(arr, offset, v_bl);
        }
    }
    return arr;
}

float *MultiFacedSurface::exportWireframe()
{
    int N = numSquaresPside;
    int totalVertices = getWireframeVertexCount();
    int stride = getN() + 4;
    float *retValues = new float[totalVertices * stride];
    int offset = 0;
    Vector<4> baseColor = surface.getBaseColor();
    const Matrix<4, 4> &cameraMatrix = Camera::getInstance().getMatrix();

    auto addSegment = [&](int i1, int i2)
    {
        Vector<3> pts[2] = {grid[i1], grid[i2]};
        for (int v = 0; v < 2; v++)
        {
            Vector<4> hp({pts[v][0], pts[v][1], pts[v][2], 1.0f});
            hp = cameraMatrix * ((Matrix<4, 1>)hp);
            float w = hp[3];
            for (int c = 0; c < 3; c++)
                retValues[offset++] = (w != 0.0f) ? (hp[c] / w) : hp[c];
            for (int c = 0; c < 4; c++)
                retValues[offset++] = baseColor[c];
        }
    };

    // Horizontal lines
    for (int j = 0; j <= N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            addSegment(j * (N + 1) + i, j * (N + 1) + i + 1);
        }
    }
    // Vertical lines
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            addSegment(j * (N + 1) + i, (j + 1) * (N + 1) + i);
        }
    }
    return retValues;
}

int MultiFacedSurface::getNumPoints() const
{
    return numSquaresPside * numSquaresPside * 6 * 3;
}

int MultiFacedSurface::getWireframeVertexCount() const
{
    return 4 * numSquaresPside * (numSquaresPside + 1);
}

int MultiFacedSurface::getNumSides() const
{
    return numSquaresPside * numSquaresPside;
}

void MultiFacedSurface::print() const
{
}

std::vector<Vector<3>> MultiFacedSurface::getVectors()
{
    return grid;
}

void MultiFacedSurface::setVectors(std::vector<Vector<3>> vec)
{
    if (vec.size() != grid.size())
        return;
    grid = vec;
    int N = numSquaresPside;
    boundary.tl = grid[0];
    boundary.tr = grid[N];
    boundary.br = grid[(N + 1) * (N + 1) - 1];
    boundary.bl = grid[(N + 1) * N];
    this->center = (boundary.tl + boundary.tr + boundary.br + boundary.bl) * (1 / 4.0f);
}

std::vector<Vector<2>> MultiFacedSurface::calculateUV()
{
    if (cachedUVs.empty())
    {
        rebuildCachedUVs();
    }
    return cachedUVs;
}

void MultiFacedSurface::rebuildCachedUVs()
{
    cachedUVs.clear();
    int N = numSquaresPside;
    cachedUVs.reserve(N * N * 6);

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            float u0 = (float)i / N;
            float u1 = (float)(i + 1) / N;
            float v0 = 1.0f - (float)j / N;
            float v1 = 1.0f - (float)(j + 1) / N;

        
            cachedUVs.push_back(Vector<2>({u0, v0}));
            cachedUVs.push_back(Vector<2>({u1, v0}));
            cachedUVs.push_back(Vector<2>({u1, v1}));

       
            cachedUVs.push_back(Vector<2>({u0, v0}));
            cachedUVs.push_back(Vector<2>({u1, v1}));
            cachedUVs.push_back(Vector<2>({u0, v1}));
        }
    }
}

MultiFacedSurface::MultiFacedSurface(Vector<3> center, float width, float height, int numSquares, Colour col)
    : _3DShape(col), numSquaresPside(numSquares), width(width), height(height), center(center), boundary(center, height, width)
{
    if (numSquares <= 0)
        throw "Cannot have 0 sqrs";
    if (width <= 0 || height <= 0)
        throw "cannot have width or height of 0";

    generateSides();
}

MultiFacedSurface::MultiFacedSurface(const Vector<3> &tl, const Vector<3> &tr,
                                     const Vector<3> &br, const Vector<3> &bl,
                                     int numSquares, Colour col)
    : _3DShape(col), numSquaresPside(numSquares), boundary(tl, tr, br, bl)
{
    if (numSquares <= 0)
        throw "Cannot have 0 sqrs";

    this->center = boundary.getCenter();
    this->width = ((tr - tl).magnitude() + (br - bl).magnitude()) * 0.5f;
    this->height = ((tl - bl).magnitude() + (tr - br).magnitude()) * 0.5f;

    generateSides();
}

void MultiFacedSurface::generateSides()
{
    grid.clear();
    grid.reserve((numSquaresPside + 1) * (numSquaresPside + 1));

    for (int j = 0; j <= numSquaresPside; j++)
    {
        float v = 1.0f - (float)j / numSquaresPside;
        for (int i = 0; i <= numSquaresPside; i++)
        {
            float u = (float)i / numSquaresPside;
            grid.push_back(bilerpQuad(boundary.tl, boundary.tr, boundary.br, boundary.bl, u, v));
        }
    }

    rebuildCachedUVs();

    if (this->orientation)
        delete this->orientation;

    Vector<3> orientStart = this->boundary.tl;
    Vector<3> orientEnd = this->boundary.br;
    this->orientation = new OrientationObject(new Vector<3>(orientStart), new Vector<3>(orientEnd));

}

MultiFacedSurface::~MultiFacedSurface()
{
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
    if (grid.empty())
        return;
    min = grid[0];
    max = grid[0];
    for (const auto &v : grid)
    {
        for (int i = 0; i < 3; i++)
        {
            if (v[i] < min[i])
                min[i] = v[i];
            if (v[i] > max[i])
                max[i] = v[i];
        }
    }
}

#include "borderShape.h"
#include "3D_shapes/3D_Shape.h"
#include "3D_shapes/Cuboid.h"

BorderShape::BorderShape(_3DShape *shape)
    : borderStub(shape) // 3d shapes need a function to return their mins and max each implemented.
{
    this->shape = shape;
    this->shape->attach(new borderObserver(this));
}

Vector<3> *BorderShape::Collision(borderStub *border)
{
    Vector<3> *borderCollisionPoint = borderStub::Collision(border);
    if (!borderCollisionPoint)
        return nullptr;
    Vector<3> overlapPoint = *borderCollisionPoint;

    Vector<3> thisPoints[] = {frontBottomLeft, frontBottomRight, frontTopLeft, frontTopRight,
                              backBottomLeft, backBottomRight, backTopLeft, backTopRight};

    float minX = thisPoints[0][0], maxX = thisPoints[0][0];
    float minY = thisPoints[0][1], maxY = thisPoints[0][1];
    float minZ = thisPoints[0][2], maxZ = thisPoints[0][2];

    for (int i = 1; i < 8; i++)
    {
        minX = std::min(minX, thisPoints[i][0]);
        maxX = std::max(maxX, thisPoints[i][0]);
        minY = std::min(minY, thisPoints[i][1]);
        maxY = std::max(maxY, thisPoints[i][1]);
        minZ = std::min(minZ, thisPoints[i][2]);
        maxZ = std::max(maxZ, thisPoints[i][2]);
    }

    float distToMinX = std::abs(overlapPoint[0] - minX);
    float distToMaxX = std::abs(overlapPoint[0] - maxX);
    float distToMinY = std::abs(overlapPoint[1] - minY);
    float distToMaxY = std::abs(overlapPoint[1] - maxY);
    float distToMinZ = std::abs(overlapPoint[2] - minZ);
    float distToMaxZ = std::abs(overlapPoint[2] - maxZ);

    float smallest = distToMinX;
    int wallAxis = 0;
    float wallValue = minX;

    if (distToMaxX < smallest)
    {
        smallest = distToMaxX;
        wallAxis = 0;
        wallValue = maxX;
    }
    if (distToMinY < smallest)
    {
        smallest = distToMinY;
        wallAxis = 1;
        wallValue = minY;
    }
    if (distToMaxY < smallest)
    {
        smallest = distToMaxY;
        wallAxis = 1;
        wallValue = maxY;
    }
    if (distToMinZ < smallest)
    {
        smallest = distToMinZ;
        wallAxis = 2;
        wallValue = minZ;
    }
    if (distToMaxZ < smallest)
    {
        wallAxis = 2;
        wallValue = maxZ;
    }

    Vector<3> wallPoint(overlapPoint);
    delete borderCollisionPoint;
    wallPoint[wallAxis] = wallValue;

    if (wallPoint[0] < minX)
        wallPoint[0] = minX;
    if (wallPoint[0] > maxX)
        wallPoint[0] = maxX;
    if (wallPoint[1] < minY)
        wallPoint[1] = minY;
    if (wallPoint[1] > maxY)
        wallPoint[1] = maxY;
    if (wallPoint[2] < minZ)
        wallPoint[2] = minZ;
    if (wallPoint[2] > maxZ)
        wallPoint[2] = maxZ;

    return new Vector<3>(wallPoint);
}

BorderShape::~BorderShape()
{
}

_3DShape *BorderShape::getShape()
{
    return this->shape;
}

void BorderShape::notify()
{
    BorderVisitor *vis = new BorderVisitor;
    this->shape->acceptVisitor(vis, this);

    if (obs)
        obs->notify();

    if (vis)
        delete vis;
}
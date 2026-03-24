#include "borderShape.h"
#include "3D shapes/3D_Shape.h"
BorderShape::BorderShape(_3DShape<3> *shape)
    : borderStub(shape) // 3d shapes need a function to return their mins and max each implemented.
{
    this->shape = shape;
}

Vector<3> *BorderShape::Collision(borderStub *border)
{
    Vector<3> *borderCollisionPoint = borderStub::Collision(border);
    if (!borderCollisionPoint)
        return nullptr;

    _3DShape<3> *colShape = border->getShape();
    if (!colShape)
    {
        delete borderCollisionPoint;
        return nullptr;
    }

    Vector<3> center = colShape->getCenter();

    float minX = frontBottomLeft[0];
    float maxX = frontBottomRight[0];
    float minY = frontBottomLeft[1];
    float maxY = frontTopLeft[1];
    float minZ = frontBottomLeft[2];
    float maxZ = backBottomLeft[2];

    float distToMinX = std::abs(center[0] - minX);
    float distToMaxX = std::abs(center[0] - maxX);
    float distToMinY = std::abs(center[1] - minY);
    float distToMaxY = std::abs(center[1] - maxY);
    float distToMinZ = std::abs(center[2] - minZ);
    float distToMaxZ = std::abs(center[2] - maxZ);

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

    Vector<3> wallPoint(*borderCollisionPoint);
    delete borderCollisionPoint;
    wallPoint[wallAxis] = wallValue;

    return new Vector<3>(wallPoint);
}

BorderShape::~BorderShape()
{
}

_3DShape<3> *BorderShape::getShape()
{
    return this->shape;
}

#include "borderStub.h"

borderStub::borderStub(Vector<3> minVals, Vector<3> maxVals)
{
    initiateValues(minVals, maxVals);
}
void borderStub::initiateValues(Vector<3> minVals, Vector<3> maxVals)
{
    frontBottomLeft = Vector<3>({minVals[0], minVals[1], minVals[2]});
    frontBottomRight = Vector<3>({maxVals[0], minVals[1], minVals[2]});
    frontTopLeft = Vector<3>({minVals[0], maxVals[1], minVals[2]});
    frontTopRight = Vector<3>({maxVals[0], maxVals[1], minVals[2]});

    backBottomLeft = Vector<3>({minVals[0], minVals[1], maxVals[2]});
    backBottomRight = Vector<3>({maxVals[0], minVals[1], maxVals[2]});
    backTopLeft = Vector<3>({minVals[0], maxVals[1], maxVals[2]});
    backTopRight = Vector<3>({maxVals[0], maxVals[1], maxVals[2]});
}

borderStub::borderStub(borderStub &stub)
{
    frontBottomLeft = stub.frontBottomLeft;
    frontBottomRight = stub.frontBottomRight;
    frontTopLeft = stub.frontTopLeft;
    frontTopRight = stub.frontTopRight;

    backBottomLeft = stub.backBottomLeft;
    backBottomRight = stub.backBottomRight;
    backTopLeft = stub.backTopLeft;
    backTopRight = stub.backTopRight;
}

borderStub::~borderStub() {}

void borderStub::addContainer(borderStub *border)
{
    delete border;
    throw "this should not run";
}

Vector<3> *borderStub::Collision(borderStub *other)
{
    float thisMinX = frontBottomLeft[0];
    float thisMaxX = frontBottomRight[0];
    float thisMinY = frontBottomLeft[1];
    float thisMaxY = frontTopLeft[1];
    float thisMinZ = frontBottomLeft[2];
    float thisMaxZ = backBottomLeft[2];

    float otherMinX = other->frontBottomLeft[0];
    float otherMaxX = other->frontBottomRight[0];
    float otherMinY = other->frontBottomLeft[1];
    float otherMaxY = other->frontTopLeft[1];
    float otherMinZ = other->frontBottomLeft[2];
    float otherMaxZ = other->backBottomLeft[2];

    bool overlapX = (thisMinX <= otherMaxX && thisMaxX >= otherMinX);
    bool overlapY = (thisMinY <= otherMaxY && thisMaxY >= otherMinY);
    bool overlapZ = (thisMinZ <= otherMaxZ && thisMaxZ >= otherMinZ);

    if (overlapX && overlapY && overlapZ)
    {
        float colX = (std::max(thisMinX, otherMinX) + std::min(thisMaxX, otherMaxX)) * 0.5f;
        float colY = (std::max(thisMinY, otherMinY) + std::min(thisMaxY, otherMaxY)) * 0.5f;
        float colZ = (std::max(thisMinZ, otherMinZ) + std::min(thisMaxZ, otherMaxZ)) * 0.5f;

        return new Vector<3>({colX, colY, colZ});
    }

    return nullptr; // no collision
}

_3DShape<3> *borderStub::getShape() // likely to be only the golf ball
{
    return nullptr;
}

borderStub::borderStub(_3DShape<3> *shape)
{
    Vector<3> min;
    Vector<3> max;
    shape->getBorders(min, max);
    initiateValues(min, max);
}
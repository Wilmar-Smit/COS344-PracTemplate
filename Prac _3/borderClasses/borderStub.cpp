#include "borderStub.h"
#include "3D_shapes/3D_Shape.h"
#include "../shapeObservers/borderObserver.h"
#include "3D_shapes/Cuboid.h"

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
    Vector<3> thisPoints[] = {frontBottomLeft, frontBottomRight, frontTopLeft, frontTopRight,
                              backBottomLeft, backBottomRight, backTopLeft, backTopRight};
    Vector<3> otherPoints[] = {other->frontBottomLeft, other->frontBottomRight, other->frontTopLeft, other->frontTopRight,
                               other->backBottomLeft, other->backBottomRight, other->backTopLeft, other->backTopRight};

    float thisMinX = thisPoints[0][0], thisMaxX = thisPoints[0][0];
    float thisMinY = thisPoints[0][1], thisMaxY = thisPoints[0][1];
    float thisMinZ = thisPoints[0][2], thisMaxZ = thisPoints[0][2];

    float otherMinX = otherPoints[0][0], otherMaxX = otherPoints[0][0];
    float otherMinY = otherPoints[0][1], otherMaxY = otherPoints[0][1];
    float otherMinZ = otherPoints[0][2], otherMaxZ = otherPoints[0][2];

    for (int i = 1; i < 8; i++)
    {
        thisMinX = std::min(thisMinX, thisPoints[i][0]);
        thisMaxX = std::max(thisMaxX, thisPoints[i][0]);
        thisMinY = std::min(thisMinY, thisPoints[i][1]);
        thisMaxY = std::max(thisMaxY, thisPoints[i][1]);
        thisMinZ = std::min(thisMinZ, thisPoints[i][2]);
        thisMaxZ = std::max(thisMaxZ, thisPoints[i][2]);

        otherMinX = std::min(otherMinX, otherPoints[i][0]);
        otherMaxX = std::max(otherMaxX, otherPoints[i][0]);
        otherMinY = std::min(otherMinY, otherPoints[i][1]);
        otherMaxY = std::max(otherMaxY, otherPoints[i][1]);
        otherMinZ = std::min(otherMinZ, otherPoints[i][2]);
        otherMaxZ = std::max(otherMaxZ, otherPoints[i][2]);
    }

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

_3DShape *borderStub::getShape() // likely to be only the golf ball
{
    return nullptr;
}

borderStub::borderStub(_3DShape *shape)
{
    Vector<3> min;
    Vector<3> max;
    shape->getBorders(min, max);
    initiateValues(min, max);
}
borderStub::borderStub(Cuboid *shape)
{
    frontBottomLeft = shape->base->bl;
    frontBottomRight = shape->base->br;
    frontTopLeft = shape->base->tl;
    frontTopRight = shape->base->tr;

    backBottomLeft = shape->top->bl;
    backBottomRight = shape->top->br;
    backTopLeft = shape->top->tl;
    backTopRight = shape->top->tr;
}

void borderStub::attach(borderObserver *obs)
{
    this->obs = obs;
}
void borderStub::notify()
{
    if (obs)
        obs->notify();
}
void borderStub::recalculateCol(_3DShape *shape)
{
    if (shape)
    {
        Vector<3> min;
        Vector<3> max;
        shape->getBorders(min, max);
        initiateValues(min, max);
    }
}
void borderStub::recalculateCol(Cuboid *shape)
{
    frontBottomLeft = shape->base->bl;
    frontBottomRight = shape->base->br;
    frontTopLeft = shape->base->tl;
    frontTopRight = shape->base->tr;

    backBottomLeft = shape->top->bl;
    backBottomRight = shape->top->br;
    backTopLeft = shape->top->tl;
    backTopRight = shape->top->tr;
}

Cuboid *borderStub::exportShape()
{
    Square<3> tempBase({0.0f, 0.0f, 0.0f}, 0.1f, 0.1f, Colour::Black);
    Cuboid *boundingBox = new Cuboid(tempBase, 0.1f, Colour::Black);

    boundingBox->base->bl = frontBottomLeft;
    boundingBox->base->br = frontBottomRight;
    boundingBox->base->tl = frontTopLeft;
    boundingBox->base->tr = frontTopRight;

    boundingBox->top->bl = backBottomLeft;
    boundingBox->top->br = backBottomRight;
    boundingBox->top->tl = backTopLeft;
    boundingBox->top->tr = backTopRight;

    boundingBox->front->tl = frontTopLeft;
    boundingBox->front->tr = frontTopRight;
    boundingBox->front->bl = frontBottomLeft;
    boundingBox->front->br = frontBottomRight;

    boundingBox->back->tl = backTopLeft;
    boundingBox->back->tr = backTopRight;
    boundingBox->back->bl = backBottomLeft;
    boundingBox->back->br = backBottomRight;

    boundingBox->leftSide->tl = frontTopLeft;
    boundingBox->leftSide->tr = backTopLeft;
    boundingBox->leftSide->bl = frontBottomLeft;
    boundingBox->leftSide->br = backBottomLeft;

    boundingBox->rightSide->tl = frontTopRight;
    boundingBox->rightSide->tr = backTopRight;
    boundingBox->rightSide->bl = frontBottomRight;
    boundingBox->rightSide->br = backBottomRight;

    return boundingBox;
}
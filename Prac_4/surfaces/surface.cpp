#include "surface.h"

Surface::Surface()
{
}

Surface::Surface(const Surface &other)
{
    this->ambientK = other.ambientK;
    this->baseColor = other.baseColor;
    this->diffuseK = other.diffuseK;
    this->shininess = other.shininess;
    this->specularK = other.specularK;
}

Vector<3> Surface::calculateNormal(
    const Vector<3> &A,
    const Vector<3> &B,
    const Vector<3> &C)
{

    Vector<3> dir = (B + (A * -1)).crossProduct((C - (A * -1)));
    this->normal = (dir.unitVector());
    return this->normal;
}

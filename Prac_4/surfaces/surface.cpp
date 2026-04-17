#include "surface.h"

Surface::Surface()
{
}

Surface::Surface(Surface &other)
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
    const Vector<3> &C) const
{

    Vector<3> dir = (B + (A * -1)).crossProduct((C - (A * -1)));
    return dir.unitVector();
}

/*
// Source - https://stackoverflow.com/a/1966605
// Posted by Frank Krueger, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-17, License - CC BY-SA 2.5

Dir = (B - A) x (C - A)
Norm = Dir / len(Dir)

*/
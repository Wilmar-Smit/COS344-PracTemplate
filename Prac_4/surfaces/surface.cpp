#include "surface.h"

Surface::Surface()
{
    this->baseColor = Vector<4>({1.0f, 1.0f, 1.0f, 1.0f});
    this->ambientK = 0.2f;
    this->diffuseK = 0.7f;
    this->specularK = 0.0f;
    this->shininess = 1.0f;
    this->normal = Vector<3>({0.0f, 0.0f, 1.0f});
}

Surface::Surface(const Surface &other)
{
    this->ambientK = other.ambientK;
    this->baseColor = other.baseColor;
    this->diffuseK = other.diffuseK;
    this->shininess = other.shininess;
    this->specularK = other.specularK;
    this->normal = other.normal;
    this->affectedByLight = other.affectedByLight;

    colorTexID = other.colorTexID;
    displacementTexID = other.displacementTexID;
    alphaTexID = other.alphaTexID;
    useColorTex = other.useColorTex;
    useDisplacementTex = other.useDisplacementTex;
    useAlphaTex = other.useAlphaTex;
}

Vector<3> Surface::calculateNormal(
    const Vector<3> &A,
    const Vector<3> &B,
    const Vector<3> &C)
{
    Vector<3> dir = (B - A).crossProduct(C - A);
    this->normal = (dir.unitVector());
    return this->normal;
}

Vector<3> Surface::calculateNormal(
    const Vector<3> &A,
    const Vector<3> &B,
    const Vector<3> &C,
    const Vector<3> &center)
{
    Vector<3> dir = (B - A).crossProduct(C - A);
    Vector<3> unitNormal = dir.unitVector();

    // Ensure normal points away from center
    Vector<3> toPoint = A - center;
    if (toPoint * unitNormal < 0)
    {
        unitNormal = unitNormal * -1.0f;
    }

    this->normal = unitNormal;
    return this->normal;
}

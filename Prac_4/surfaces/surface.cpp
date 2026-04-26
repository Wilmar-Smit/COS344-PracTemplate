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
    this->flipNormal = other.flipNormal;

    colorTexID = other.colorTexID;
    displacementTexID = other.displacementTexID;
    alphaTexID = other.alphaTexID;
    useColorTex = other.useColorTex;
    useDisplacementTex = other.useDisplacementTex;
    useAlphaTex = other.useAlphaTex;
    useCenter = other.useCenter;
}

Vector<3> Surface::calculateNormal(
    const Vector<3> &A,
    const Vector<3> &B,
    const Vector<3> &C)
{
    Vector<3> dir = (B - A).crossProduct(C - A);
    float mag = dir.magnitude();
    if (mag < 1e-6f)
    {
        return this->normal;
    }
    this->normal = dir * (1.0f / mag);
    if (this->flipNormal)
        this->normal = this->normal * -1.0f;
    return this->normal;
}

Vector<3> Surface::calculateNormal(
    const Vector<3> &A,
    const Vector<3> &B,
    const Vector<3> &C,
    const Vector<3> &center)
{
    Vector<3> dir = (B - A).crossProduct(C - A);
    float mag = dir.magnitude();
    if (mag < 1e-6f)
    {
        return this->normal;
    }

    Vector<3> n = dir * (1.0f / mag);
    Vector<3> faceCenter = (A + B + C) * (1.0f / 3.0f);
    Vector<3> outward = faceCenter - center;

    if (outward.magnitude() > 1e-6f && (n * outward) < 0.0f)
    {
        n = n * -1.0f;
    }

    if (this->flipNormal)
        n = n * -1.0f;

    this->normal = n;
    return this->normal;
}


#include "pointLight.h"

PointLight::PointLight(Colour col, Vector<3> position, float intensity) : Light(col)
{
    this->position = position;
    this->intensity = intensity;

    this->sphere = new Sphere(position, 0.2, 10, 5, Colour::Invisible);
}

// Return position
Vector<3> PointLight::getPosition()
{
    return this->position;
}

// Calculate illumination at collision point X for a given surface
Vector<4> PointLight::calculateIlluminations(Vector<3> X, Surface surface)
{
    // x is the v3 in exportValues
    Vector<3> dis = this->position - X;
    float r = dis.magnitude();
    if (r < 0.0001f)
    {
        r = 0.0001f;
    }


    Vector<3> L = dis * (1.0f / r);
    Vector<3> n = surface.getNormal();
    float nDotL = n * L;
    float diffuseFactor = std::max(0.0f, nDotL);

    Vector<4> retVec;
    Vector<4> base = surface.getBaseColor();
    float attenuation = intensity / (r * r);

    for (int i = 0; i < 3; i++)
    {
        float ambient = base[i] * surface.getAmbientK();
        float diffuse = base[i] * surface.getDiffuseK() * this->colour[i] * diffuseFactor * attenuation;
        retVec[i] = ambient + diffuse;

        if (retVec[i] > 1.0f)
        {
            retVec[i] = 1.0f;
        }
        if (retVec[i] < 0.0f)
        {
            retVec[i] = 0.0f;
        }
    }

    retVec[3] = base[3];

    retVec.print();
    return retVec;
}

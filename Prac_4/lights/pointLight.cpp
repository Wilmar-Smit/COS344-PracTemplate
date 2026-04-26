
#include "pointLight.h"

PointLight::PointLight(Colour col, Vector<3> position, float intensity) : Light(col)
{
    this->position = position;
    this->intensity = intensity;

    this->sphere = new Sphere(position, 0.05, 10, 5, col);
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
    if (surface.getAffectedLight())
    {
        Vector<3> dis = this->position - X;
        float r = dis.magnitude();


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

            Vector<3> eye = Camera::getInstance().getEye();
            Vector<3> v = (eye - X).unitVector();
            Vector<3> h = (L + v).unitVector();

            float nDotH = std::max(0.0f, n * h);
            float specular = surface.getSpecularK() * this->colour[i] *
                             pow(nDotH, surface.getShininess()) * attenuation;

            retVec[i] = ambient + diffuse + specular;

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

        return retVec;
    }
    else
    {
        return surface.getBaseColor();
    }
}
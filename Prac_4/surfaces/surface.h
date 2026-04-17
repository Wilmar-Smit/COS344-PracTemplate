#ifndef SURFACE_H
#define SURFACE_H

#include "Vector.h"

class Surface
{
private:
    Vector<4> baseColor;
    float ambientK;  // Ka: Ambient coefficient
    float diffuseK;  // Kd: Diffuse coefficient
    float specularK; // Ks: Specular coefficient
    float shininess; // n:  Specular exponent

public:
    Surface(); // updated by builder
    Surface(Surface &other);

    Vector<3> calculateNormal(
        const Vector<3> &v1,
        const Vector<3> &v2,
        const Vector<3> &v3) const;

    Vector<4> getBaseColor() const { return baseColor; }
    float getAmbientK() const { return ambientK; }
    float getDiffuseK() const { return diffuseK; }
    float getSpecularK() const { return specularK; }
    float getShininess() const { return shininess; }

    void setBaseColor(const Vector<4> &color) { baseColor = color; }
    void setAmbientK(float k) { ambientK = k; }
    void setDiffuseK(float k) { diffuseK = k; }
    void setSpecularK(float k) { specularK = k; }
    void setShininess(float s) { shininess = s; }
};

#endif
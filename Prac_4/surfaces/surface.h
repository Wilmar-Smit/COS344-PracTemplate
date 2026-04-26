#ifndef SURFACE_H
#define SURFACE_H

#include "Vector.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Surface
{
private:
    Vector<4> baseColor; // Material base color (RGBA)
    float ambientK;      // Ka: Ambient coefficient
    float diffuseK;      // Kd: Diffuse coefficient
    float specularK;     // Ks: Specular coefficient
    float shininess;     // n: Specular exponent (Phong)

    Vector<3> normal;
    bool affectedByLight = false;

    GLuint colorTexID = 0;
    GLuint displacementTexID = 0;
    GLuint alphaTexID = 0;

    bool useColorTex = false;
    bool useDisplacementTex = false;
    bool useAlphaTex = false;

public:
    Surface();
    Surface(const Surface &other);

    Vector<3> calculateNormal(
        const Vector<3> &v1,
        const Vector<3> &v2,
        const Vector<3> &v3);

    Vector<3> calculateNormal(
        const Vector<3> &v1,
        const Vector<3> &v2,
        const Vector<3> &v3,
        const Vector<3> &center);

    Vector<4> getBaseColor() const { return baseColor; }
    float getAmbientK() const { return ambientK; }
    float getDiffuseK() const { return diffuseK; }
    float getSpecularK() const { return specularK; }
    float getShininess() const { return shininess; }
    Vector<3> getNormal() const { return normal; }
    bool getAffectedLight() { return this->affectedByLight; }

    void setBaseColor(const Vector<4> &color) { baseColor = color; }
    void setAmbientK(float k) { ambientK = k; }
    void setDiffuseK(float k) { diffuseK = k; }
    void setSpecularK(float k) { specularK = k; }
    void setShininess(float s) { shininess = s; }
    void setAffectedLight(bool val) { this->affectedByLight = val; }

    void setColorTexture(GLuint tex)
    {
        colorTexID = tex;
        this->enableColorTexture(true);
    }
    void setDisplacementTexture(GLuint tex) { displacementTexID = tex; }
    void setAlphaTexture(GLuint tex) { alphaTexID = tex; }

    GLuint getColorTexture() const { return colorTexID; }
    GLuint getDisplacementTexture() const { return displacementTexID; }
    GLuint getAlphaTexture() const { return alphaTexID; }

    void enableColorTexture(bool enable) { useColorTex = enable; }
    void enableDisplacementTexture(bool enable) { useDisplacementTex = enable; }
    void enableAlphaTexture(bool enable) { useAlphaTex = enable; }

    bool isColorTextureEnabled() const { return useColorTex; }
    bool isDisplacementTextureEnabled() const { return useDisplacementTex; }
    bool isAlphaTextureEnabled() const { return useAlphaTex; }
};

#endif

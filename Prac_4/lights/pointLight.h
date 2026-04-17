#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"
#include "../MathLibrary/3D_shapes/Sphere.h"
class PointLight : public Light // template method
{
private:
    Vector<3> position;
    float intensity;
    Sphere *sphere;

public:
    PointLight(Colour col, Vector<3> position, float intensity); // for light colour use the static builder function
    virtual Vector<4> calculateIlluminations(Vector<3> X, Surface Surface);
    virtual Vector<3> getPosition();
    virtual Vector<4> getColour() { return this->colour; };
    virtual Sphere* getShape() { return sphere; }
};

#endif

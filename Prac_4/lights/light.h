#ifndef LIGHT_H
#define LIGHT_H

#include "../MathLibrary/Vector.h"
#include "../surfaces/surface.h"
#include "../MathLibrary/3D_shapes/Sphere.h"
#include "../surfaces/surfaceBuilder.h"

class Light // template method
{
protected:
    Vector<4> colour = {1, 1, 1, 1};
    Colour colEnum;

public:
    Light(Colour col) : colEnum(col) { this->colour = SurfaceBuilder::buildColour(col); }; // for light colour use the static builder function
    virtual Vector<4> calculateIlluminations(Vector<3> X, Surface Surface) = 0;
    virtual Vector<3> getPosition() = 0;
    virtual void setPosition(Vector<3> pos) = 0;
    virtual void setColour(Colour col) = 0;
    virtual Colour getColourEnum() const { return this->colEnum; }
    virtual Vector<4> getColour() { return this->colour; };
    virtual Sphere *getShape() = 0;
};

#endif

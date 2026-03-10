#ifndef GOLF_SHAPE_H
#define GOLF_SHAPE_H

#include "Shape.h"
#include "Vector.h"

enum class Colour
{
    Red,
    Green,
    Blue,
    Yellow,
    Cyan,
    Magenta,
    Orange,
    Purple,
    White,
    Grey,
    Maroon,
    Pink,
    Brown,
    DarkBrown
};

class GolfShape
{
private:
    Shape<2> *shape;
    Vector<4> colour;

public:
    GolfShape(Shape<2> *shape, Colour chosenColour);
    float *exportValues();
    Vector<4> getColourVec(Colour col);


    Vector<4> Red{1.0f, 0.0f, 0.0f, 1.0f};
    Vector<4> Green{0.0f, 1.0f, 0.0f, 1.0f};
    Vector<4> Blue{0.0f, 0.0f, 1.0f, 0.5f};
    Vector<4> Yellow{1.0f, 1.0f, 0.0f, 1.0f};
    Vector<4> Cyan{0.0f, 1.0f, 1.0f, 1.0f};
    Vector<4> Magenta{1.0f, 0.0f, 1.0f, 1.0f};
    Vector<4> Orange{1.0f, 0.5f, 0.0f, 1.0f};
    Vector<4> Purple{0.5f, 0.0f, 0.5f, 1.0f};
    Vector<4> White{1.0f, 1.0f, 1.0f, 1.0f};
    Vector<4> Grey{0.5f, 0.5f, 0.5f, 1.0f};
    Vector<4> Maroon{0.5f, 0.0f, 0.0f, 1.0f};
    Vector<4> Pink{1.0f, 0.75f, 0.8f, 1.0f};
    Vector<4> Brown{0.6f, 0.3f, 0.0f, 1.0f};
    Vector<4> DarkBrown{0.4f, 0.2f, 0.0f, 1.0f};
};

#endif

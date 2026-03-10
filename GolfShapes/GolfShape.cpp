#include "GolfShape.h"

GolfShape::GolfShape(Shape<2> *shape, Colour chosenColour)
    : shape(shape)
{
    this->colour = getColourVec(chosenColour);
}

float *GolfShape::exportValues()
{
    int shapeSides = shape->getNumPoints() / shape->getN();
    int totalValues = shapeSides * (shape->getN() + 4);
    float *retValues = new float[totalValues];
    float *ShapeCoords = shape->getPoints();

    int offset = 0;
    int count = 0;
    for (int row = 0; row < shapeSides; row++)
    {
        for (int i = 0; i < shape->getN(); i++)
        {
            retValues[offset++] = ShapeCoords[count++];
        }
        for (int i = 0; i < 4; i++) // 4 is for colour values
        {
            retValues[offset++] = colour[i];
        }
    }
    delete[] ShapeCoords;
    return retValues;
}
Vector<4> GolfShape::getColourVec(Colour col)
{
    if (col == Colour::Red)
        return this->Red;
    else if (col == Colour::Green)
        return this->Green;
    else if (col == Colour::Blue)
        return this->Blue;
    else if (col == Colour::Yellow)
        return this->Yellow;
    else if (col == Colour::Cyan)
        return this->Cyan;
    else if (col == Colour::Magenta)
        return this->Magenta;
    else if (col == Colour::Orange)
        return this->Orange;
    else if (col == Colour::Purple)
        return this->Purple;
    else if (col == Colour::White)
        return this->White;
    else if (col == Colour::Grey)
        return this->Grey;
    else if (col == Colour::Maroon)
        return this->Maroon;
    else if (col == Colour::Pink)
        return this->Pink;
    else if (col == Colour::Brown)
        return this->Brown;
    else if (col == Colour::DarkBrown)
        return this->DarkBrown;

    // Default fallback
    return this->White;
}

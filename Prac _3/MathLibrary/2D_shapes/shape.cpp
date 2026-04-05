#include "Shape.h"

float *Shape::exportValues()
{
    int shapeSides = getNumPoints() / getN();
    int totalValues = shapeSides * (getN() + 4);
    float *retValues = new float[totalValues];
    float *ShapeCoords = getPoints();

    int offset = 0;
    int count = 0;

    for (int row = 0; row < shapeSides; row++)
    {
        for (int i = 0; i < getN(); i++)
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
float *Shape::exportWireframe()
{
    int shapeSides = getNumPoints() / getN();
    float *ShapeCoords = getPoints();

    // Each side contributes 2 vertices (start + end)
    int totalValues = shapeSides * 2 * (getN() + 4);
    float *retValues = new float[totalValues];

    int offset = 0;
    int count = 0;

    for (int row = 0; row < shapeSides; row++)
    {

        for (int i = 0; i < getN(); i++)
            retValues[offset++] = ShapeCoords[count + i];
        for (int i = 0; i < 4; i++)
            retValues[offset++] = colour[i];

        int next = ((row + 1) % shapeSides) * getN();
        for (int i = 0; i < getN(); i++)
            retValues[offset++] = ShapeCoords[next + i];
        for (int i = 0; i < 4; i++)
            retValues[offset++] = colour[i];

        count += getN();
    }

    delete[] ShapeCoords;
    return retValues;
}

Vector<4> Shape::getColourVec(Colour col)
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
    else if (col == Colour::Black)
        return this->Black;
    else if (col == Colour::Invisible)
        return this->invisible;
    // Default fallback
    return this->White;
}
Shape::Shape(Colour col)
{
    this->colour = getColourVec(col);
}
Vector<4> Shape::getColourPas()
{
    Vector<4> ret;
    float mixFactor = 0.3f;
    for (int i = 0; i < 4; i++)
    {
        if (i < 3)
        {
            ret[i] = (this->colour[i] * (1.0f - mixFactor)) + (1.0f * mixFactor);
        }
        else
        {
            ret[i] = this->colour[i];
        }
    }
    return ret;
}
Vector<4> Shape::dePastel(Vector<4> pastelCol)
{
    Vector<4> ret;
    float mixFactor = 0.3f;
    for (int i = 0; i < 3; i++)
    {
        ret[i] = (pastelCol[i] - mixFactor) / (1.0f - mixFactor);
    }
    ret[3] = pastelCol[3];
    return ret;
}

std::vector<Vector<4>> Shape::getHomogeneousVectors()
{
    auto originalPoints = getVectors();
    std::vector<Vector<4>> homogeneousPoints;
    homogeneousPoints.reserve(originalPoints.size());

    for (auto &point : originalPoints)
    {
        Vector<4> homogeneousPoint;
        for (int i = 0; i < this->n; i++)
            homogeneousPoint[i] = point[i];
        homogeneousPoint[this->n] = 1.0f;

        homogeneousPoints.push_back(homogeneousPoint);
    }
    return homogeneousPoints;
}

void Shape::applyMatrix(const Matrix<4, 4> &transformationMatrix, bool per)
{
    auto originalPoints = getVectors();

    for (auto &point : originalPoints)
    {
        Vector<4> homogeneousPoint;
        for (int i = 0; i < this->n; i++)
            homogeneousPoint[i] = point[i];
        homogeneousPoint[this->n] = 1.0f;

        // Apply transformation
        homogeneousPoint = transformationMatrix * ((Matrix<4, 1>)homogeneousPoint);

        if (per) // only do perspective divide if flagged
        {
            if (homogeneousPoint[3] != 0.0f)
            {
                for (int i = 0; i < this->n; i++)
                    point[i] = homogeneousPoint[i] / homogeneousPoint[3];
            }
        }
        else
        {
            for (int i = 0; i < this->n; i++)
                point[i] = homogeneousPoint[i];
        }
    }

    setVectors(originalPoints);
}

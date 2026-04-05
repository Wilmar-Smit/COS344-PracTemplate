#ifndef SHAPE_H
#define SHAPE_H

#include "Matrix.h"
#include <vector>
#include <iostream>

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
    DarkBrown,
    Black,
    Invisible
};

class Shape
{
protected:
    int n = 3;


public:



    Vector<4> colour;
    Shape(Colour col = Colour::White);
    virtual Shape &operator*=(const Matrix<3, 3> &) = 0;
    virtual Shape *operator*(const Matrix<3, 3> &) const = 0;
    virtual float *getPoints() const = 0;
    virtual int getNumPoints() const = 0;
    virtual int getNumSides() const = 0;
    virtual void print() const = 0;
    virtual Vector<3> getCenter() = 0;
    virtual ~Shape() = default;
    int getN() { return n; };

    const Vector<4> Red{0.65f, 0.18f, 0.18f, 1.0f};
    const Vector<4> Green{0.24f * 0.7, 0.8f * 0.7, 0.24f * 0.7, 1.0f};
    const Vector<4> Blue{0.12f, 0.24f, 0.7f, 1.0f};
    const Vector<4> Yellow{0.72f, 0.65f, 0.20f, 1.0f};
    const Vector<4> Cyan{0.18f, 0.45f, 0.45f, 1.0f};
    const Vector<4> Magenta{0.48f, 0.20f, 0.48f, 1.0f};
    const Vector<4> Orange{0.68f, 0.40f, 0.16f, 1.0f};
    const Vector<4> Purple{0.32f, 0.20f, 0.42f, 1.0f};
    const Vector<4> White{0.90f, 0.90f, 0.86f, 1.0f};
    const Vector<4> Grey{0.38f, 0.38f, 0.38f, 1.0f};
    const Vector<4> Maroon{0.38f, 0.10f, 0.10f, 1.0f};
    const Vector<4> Pink{0.68f, 0.50f, 0.54f, 1.0f};
    const Vector<4> Brown{0.40f, 0.25f, 0.12f, 1.0f};
    const Vector<4> DarkBrown{0.25f, 0.16f, 0.08f, 1.0f};
    const Vector<4> Black{0.05f, 0.05f, 0.05f, 1.0f};
    const Vector<4> invisible{0.90f, 0.90f, 0.86f, 0.0f};

    virtual float *exportValues();
    float *exportWireframe();
    int getWireframeVertexCount() { return this->getNumSides() * (getN() + 4); }

    void setCoulourVec(Vector<4> col) { this->colour = col; };
    Vector<4> getColourVec(Colour col);
    Vector<4> getColourPas();
    Vector<4> dePastel(Vector<4> pastelCol);
    Vector<4> getColourVec() { return this->colour; };
    virtual std::vector<Vector<3>> getVectors() = 0;
    virtual void setVectors(std::vector<Vector<3>>) = 0;

    virtual std::vector<Vector<4>> getHomogeneousVectors();
    void applyMatrix(const Matrix<4, 4> &transformationMatrix);
};
#endif
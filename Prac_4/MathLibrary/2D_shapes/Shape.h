#ifndef SHAPE_H
#define SHAPE_H

#include "Matrix.h"
#include <vector>
#include <iostream>
#include "../../surfaces/surfaceBuilder.h"

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
    Peach,
    Brown,
    DarkBrown,
    Black,
    Invisible
};

class Shape
{
protected:
    int n = 3;

private:
    static Surface buildSurfaceFromColour(Colour col);

public:
    Surface surface;
    Shape();
    Shape(Colour col);
    virtual Shape &operator*=(const Matrix<3, 3> &) = 0;
    virtual Shape *operator*(const Matrix<3, 3> &) const = 0;
    virtual float *getPoints() const = 0;
    virtual int getNumPoints() const = 0;
    virtual int getNumSides() const = 0;
    virtual void print() const = 0;
    virtual Vector<3> getCenter() = 0;
    virtual ~Shape() = default;
    int getN() const { return n; };



    virtual float *exportValues();
    float *exportWireframe();
    int getWireframeVertexCount() const;

    void setCoulourVec(Vector<4> col)
    {
        this->surface.setBaseColor(col);
    };
    Vector<4> getColourVec(Colour col);
    Vector<4> getColourPas();
 
    Vector<4> getColourVec() { return this->surface.getBaseColor(); };
    Surface &getSurface() { return this->surface; }
    const Surface &getSurface() const { return this->surface; }
    void setSurface(const Surface &newSurface)
    {
        this->surface = newSurface;
    }
    virtual std::vector<Vector<3>> getVectors() = 0;
    virtual void setVectors(std::vector<Vector<3>>) = 0;

    virtual std::vector<Vector<4>> getHomogeneousVectors();
    void applyMatrix(const Matrix<4, 4> &transformationMatrix, bool per = false);
};
#endif
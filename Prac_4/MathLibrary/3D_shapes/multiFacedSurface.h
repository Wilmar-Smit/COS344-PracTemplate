#ifndef MULTIFACEDSURFACE_H
#define MULTIFACEDSURFACE_H

#include "3D_Shape.h"
#include "2D_shapes/Square.h"
class MultiFacedSurface : public _3DShape
{
    friend class DrawerVisitor;

private:
    float width = 0;
    float height = 0;
    // used to change the number of squares in the shape initially 0
    int numSquaresPside = 0;

    // builds the surface out of squares.
    std::vector<Shape *> squares;
    std::vector<Vector<2>> cachedUVs;
    Vector<3> center;

    void generateSides();
    void rebuildCachedUVs();
    // the + will draw the center line squares  (if false will check if center == calcCenter)
    void XLoopOdd(bool Sign); // true == + : false == -
    void YLoopOdd(float X, bool Sign);

    void XLoopEven(bool Sign); // true == + : false == -
    void YLoopEven(float X, bool Sign);

public:
    // center is constant,
    // the width is total width and is constant
    // heaght is the shapes total height and is constant
    MultiFacedSurface(Vector<3> center, float width, float height, int numSquares = 1, Colour col = Colour::Black);
    MultiFacedSurface(const Vector<3> &tl, const Vector<3> &tr,
                      const Vector<3> &br, const Vector<3> &bl,
                      int numSquares = 1, Colour col = Colour::White);


    virtual float *getPoints() const override;
    virtual float *exportWireframe() override;
    
    virtual int getNumPoints() const override;
    virtual int getWireframeVertexCount() const override;
    virtual int getNumSides() const override;
    virtual void print() const override;
    virtual std::vector<Vector<3>> getVectors() override;
    virtual void setVectors(std::vector<Vector<3>>) override;

    virtual Vector<3> getCenter() override;

    virtual void acceptVisitor(DrawerVisitor *vis) override;

    virtual void getBorders(Vector<3> &min, Vector<3> &max) override;

    virtual ~MultiFacedSurface();

    void setSides(int n)
    {
        if (n > 0)
            this->numSquaresPside = n;

        generateSides();

        Vector<3> orientStart = this->center;
        Vector<3> orientEnd = this->center;
        orientStart[0] += width;
        orientEnd[0] -= width;
       
    }

protected:
    virtual std::vector<Vector<2>> calculateUV() override;
};

#endif

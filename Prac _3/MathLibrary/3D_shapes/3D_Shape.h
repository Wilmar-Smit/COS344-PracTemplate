#ifndef THREE_DSHAPE_H
#define THREE_DSHAPE_H

#include "../Matrix.h"
#include "../Vector.h"
#include <vector>
#include "../2D_shapes/Shape.h"
#include "../2D_shapes/circle.h"
#include "../shapeObservers/borderObserver.h"
#include "../borderClasses/borderVisitor.h"
class DrawerVisitor;
class OrientationObject;
class _3DShape : public Shape
{
protected:
    OrientationObject *orientation = nullptr;

private:
    borderObserver *observer = nullptr;

public:
    Colour colour;
    Vector<4> colVec;

    _3DShape(Colour col) : Shape(col)
    {
        this->colour = col;
        this->colVec = Shape::getColourVec(col);
    };

    virtual _3DShape &operator*=(const Matrix<3, 3> &) override { return *this; }
    virtual _3DShape *operator*(const Matrix<3, 3> &) const override { return nullptr; }
    virtual float *getPoints() const override { return nullptr; }
    virtual int getNumPoints() const override { return 0; }
    virtual int getNumSides() const override { return 0; }
    virtual void print() const override {}
    virtual float *exportValues() override { return nullptr; }
    virtual Vector<3> getCenter() = 0;
    virtual std::vector<Vector<3>> getVectors() override { return {}; }
    virtual void setVectors(std::vector<Vector<3>>) override {}

    virtual ~_3DShape()
    {
        if (observer)
            delete observer;
        if (orientation)
            delete orientation;
    }

    virtual void acceptVisitor(DrawerVisitor *) = 0;

    virtual void getBorders(Vector<3> &min, Vector<3> &max) = 0;

    virtual void attach(borderObserver *obs)
    {
        if (this->observer)
        {
            delete obs;
        }
        this->observer = obs;
    }

    virtual void notify()
    {
        if (observer)
            observer->notify();
    }

    virtual OrientationObject *getOrientation()
    {
        return this->orientation;
    }
    virtual void acceptVisitor(BorderVisitor *vis, borderStub *border)
    {
        vis->visitRun(this, border);
    }
};

#endif /* THREE_DSHAPE_H */
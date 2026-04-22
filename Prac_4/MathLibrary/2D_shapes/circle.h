#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <cmath>

class Circle : public Shape
{
private:
    int numVertices;
    std::vector<Vector<3>> vertices;
    Vector<3> &center;
    float radius;

    void generateVertices();

public:
    Circle(const Vector<3> &center, float radius, int numVertices, Colour col = Colour::White);
    Circle(const Circle &other);
    virtual Circle &operator*=(const Matrix<3, 3> &m) override;
    virtual Circle *operator*(const Matrix<3, 3> &m) const override;
    virtual float *getPoints() const override;
    virtual int getNumPoints() const override { return this->vertices.size() * 3; }
    virtual int getNumSides() const override { return vertices.size(); }
    virtual void print() const override;
    virtual Vector<3> getCenter() override { return center; }

    virtual std::vector<Vector<3>> getVectors() override { return vertices; }
    virtual void setVectors(std::vector<Vector<3>> v) override;
    virtual std::vector<Vector<2>> calculateUV();
    Circle operator=(const Circle &other)
    {
        if (this != &other)
        {
            this->numVertices = other.numVertices;
            this->vertices = other.vertices;
            this->center = this->vertices.front();
            this->radius = other.radius;
            this->setSurface(other.getSurface());
        }

        return *this;
    }
};

#endif /* CIRCLE_H */

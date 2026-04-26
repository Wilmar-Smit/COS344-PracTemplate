#ifndef SPHERE_H
#define SPHERE_H

#include "../Matrix.h"
#include "../Vector.h"
#include <vector>
#include "../2D_shapes/circle.h"
#include "3D_Shape.h"
#include "../2D_shapes/Triangle.h"
#include "../2D_shapes/Square.h"

class Sphere : public _3DShape
{
    friend class DrawerVisitor;

private:
    int numSectors;
    int stacks;
    float radius;
    float DeltaY;
    const int numSquaresPerSurface;
    std::vector<Shape *> allSides;
    std::vector<Shape *> circlesTop;
    std::vector<Shape *> circlesBottom;
    Square *topCenter;
    Square *bottomCenter;
    Circle *centerCircle;
    void generateSides();

    void addSides(std::vector<Vector<3>> baseSides, std::vector<Vector<3>> topSides, bool flipNormals = false);

    float radY(float y)
    {
        return std::sqrt(std::pow(radius, 2) - std::pow(y, 2));
    }
    float yk(int k)
    {
        return k * DeltaY;
    }

public:
    Sphere(Vector<3> centerVec, float rad, int numSectors, int stacks, Colour col, int numSquaresPerSurface = 1);
    Sphere(const Sphere &other);
    virtual Vector<3> getCenter() override;
    virtual void getBorders(Vector<3> &min, Vector<3> &max) override;
    virtual void acceptVisitor(DrawerVisitor *vis) override;

    virtual ~Sphere()
    {
        delete centerCircle;
        for (int i = 0; i < circlesTop.size(); i++)
        {
            if (circlesTop[i])
                delete circlesTop[i];
        }
        for (int i = 0; i < circlesBottom.size(); i++)
        {
            if (circlesBottom[i])
                delete circlesBottom[i];
        }
        for (int i = 0; i < allSides.size(); i++)
        {
            if (allSides[i])
                delete allSides[i];
        }
    }
};

#endif /* SPHERE_H */

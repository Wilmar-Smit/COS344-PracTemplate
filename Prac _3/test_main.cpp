#include <iostream>
#include "3D_shapes/3D_Shape.h"
#include "3D_shapes/Sphere.h"
#include "3D_shapes/Cuboid.h"
#include "3D_shapes/Cone.h"
#include "3D_shapes/Cylinder.h"
#include "3D_shapes/SquarePyramid.h"
#include "3D_shapes/TriangularPrism.h"
#include "2D_shapes/Square.h"
#include "2D_shapes/circle.h"
#include "assets.h"

int main()
{
    Square squareBase({0.0f, 0.0f, 0.0f}, 0.50f, 0.50f, Colour::Blue);
    Circle circleBase({0.0f, 0.0f, 0.0f}, 0.25f, 16, Colour::Green);
    Square prismBase({0.0f, 0.0f, 0.0f}, 0.40f, 0.40f, Colour::Yellow);

    _3DShape *sphere = new Sphere({0.0f, 0.0f, 0.0f}, 0.10f, 10, 10, Colour::Red);
    _3DShape *cuboid = new Cuboid(squareBase, 0.15f, Colour::Blue);
    _3DShape *cone = new Cone(circleBase, 0.30f, Colour::Magenta);
    _3DShape *cylinder = new Cylinder(circleBase, 0.30f, Colour::Cyan);
    _3DShape *squarePyramid = new SquarePyramid(squareBase, 0.25f, Colour::Orange);
    _3DShape *triangularPrism = new TriangularPrism(prismBase, 0.20f, Colour::Purple);
    Vector<3> vsc = cylinder->getCenter();

    delete sphere;
    delete cuboid;
    delete cone;
    delete cylinder;
    delete squarePyramid;
    delete triangularPrism;

    std::cout << "constructed and deleted all 3D shapes" << std::endl;

    return 0;
}

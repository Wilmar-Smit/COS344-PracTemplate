#include <iostream>
#include "sceneClasses/drawerVisitor.h"
#include "3D shapes/3D_Shape.h"
#include "3D shapes/Sphere.h"
#include "3D shapes/Cuboid.h"
#include "3D shapes/Cone.h"
#include "3D shapes/Cylinder.h"
#include "3D shapes/SquarePyramid.h"
#include "3D shapes/TriangularPrism.h"
#include "2D shapes/Square.h"
#include "2D shapes/circle.h"

int main()
{
    Square<3> squareBase({0.0f, 0.0f, 0.0f}, 0.50f, 0.50f, Colour::Blue);
    Circle<3> circleBase({0.0f, 0.0f, 0.0f}, 0.25f, 16, Colour::Green);
    Square<3> prismBase({0.0f, 0.0f, 0.0f}, 0.40f, 0.40f, Colour::Yellow);

    _3DShape<3> *sphere = new Sphere<3>({0.0f, 0.0f, 0.0f}, 0.10f, 10, 10, Colour::Red);
    _3DShape<3> *cuboid = new Cuboid<3>(squareBase, 0.15f, Colour::Blue);
    _3DShape<3> *cone = new Cone<3>(circleBase, 0.30f, Colour::Magenta);
    _3DShape<3> *cylinder = new Cylinder<3>(circleBase, 0.30f, Colour::Cyan);
    _3DShape<3> *squarePyramid = new SquarePyramid<3>(squareBase, 0.25f, Colour::Orange);
    _3DShape<3> *triangularPrism = new TriangularPrism<3>(prismBase, 0.20f, Colour::Purple);

    delete sphere;
    delete cuboid;
    delete cone;
    delete cylinder;
    delete squarePyramid;
    delete triangularPrism;

    std::cout << "constructed and deleted all 3D shapes" << std::endl;

    return 0;
}

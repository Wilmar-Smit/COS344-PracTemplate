#include "assets.h"

complexSceneHolder *WindMillFan()
{
    Vector<3> center;
    DrawerVisitor *exchangeableVis = nullptr;
    complexSceneHolder *windMillFan = new complexSceneHolder();
    _3DShape *exchangeableShape = nullptr;
    OrientationObject *orient = nullptr;


    exchangeableShape = new Cylinder(Circle<3>({0.0f, 0.0f, -0.01f}, 0.04f, 10, Colour::DarkBrown), 0.5, Colour::DarkBrown);
    orient = exchangeableShape->getOrientation();
    windMillFan->SetMyOrientation(orient);

    center = exchangeableShape->getCenter();
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    windMillFan->addScene(exchangeableVis);

    //  cyl base

    // center cube
    exchangeableShape = new Cuboid(Square<3>({0, 0, 0}, 0.25, 0.25, Colour::Brown), 0.1, Colour::Brown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    windMillFan->addScene(exchangeableVis);
    // center Cube

    // arms

    exchangeableShape = new Cuboid(Square<3>({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(90, orient);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(180, orient);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(270, orient);
    windMillFan->addScene(exchangeableVis);
    // arms

    // bar things
    exchangeableShape = new Cuboid(Square<3>({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(90, orient);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(180, orient);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(270, orient);
    windMillFan->addScene(exchangeableVis);
    // bar things
    windMillFan->Translation(Direction::forward, 0.2);
    windMillFan->RotateZ(45, orient);

    return windMillFan;
}
complexSceneHolder *WindMillTower()
{

    Vector<3> center;
    DrawerVisitor *exchangeableVis = nullptr;
    complexSceneHolder *windMill = new complexSceneHolder();
    _3DShape *exchangeableShape = nullptr;
    OrientationObject *orient = nullptr;
    float moveCenter = 0.55;
    // base
    exchangeableShape = new Cone(Circle<3>({0, 0, 0}, 0.7, 15, Colour::DarkBrown), 1.5, Colour::DarkBrown);
    center = exchangeableShape->getCenter();
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    orient = exchangeableShape->getOrientation();
    windMill->SetMyOrientation(orient);

    exchangeableVis->RotateX(270);
    exchangeableVis->Translation(Direction::down, 1);
    exchangeableVis->Translation(Direction::forward, moveCenter);

    windMill->addScene(exchangeableVis);
    //  base
    exchangeableShape = new Cone(Circle<3>({0, 0, 0}, 0.6, 15, Colour::Red), 1.5, Colour::Red);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(270);
    exchangeableVis->Translation(Direction::down, 0.8);
    exchangeableVis->Translation(Direction::forward, moveCenter);

    windMill->addScene(exchangeableVis);

    exchangeableShape = new Cone(Circle<3>({0, 0, 0}, 0.5, 15, Colour::White), 1.5, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(270);
    exchangeableVis->Translation(Direction::down, 0.6);
    exchangeableVis->Translation(Direction::forward, moveCenter);

    windMill->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0, 0, 0}, 2, 0.3, Colour::DarkBrown), 0.5, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 0.5);
    exchangeableVis->Translation(Direction::forward, 0.48);

    windMill->addScene(exchangeableVis);

    exchangeableShape = new TriangularPrism(Square<3>({0, 0, 0}, 0.7, 0.7, Colour::Red), 0.6, Colour::Red);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(270);
    exchangeableVis->RotateY(90);
    exchangeableVis->Translation(Direction::up, 0.5);
    exchangeableVis->Translation(Direction::forward, 0.5);

    windMill->addScene(exchangeableVis);

    return windMill;
}

complexSceneHolder *GolfCourse()
{
    complexSceneHolder *totalScene = new complexSceneHolder;
    totalScene->addScene(WindMillFan());
    totalScene->SetMyOrientation(totalScene->getIndex(0)->getMyOrientation());
    totalScene->addScene(WindMillTower());
    return totalScene;
}
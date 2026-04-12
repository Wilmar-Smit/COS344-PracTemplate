#include "assets.h"

complexSceneHolder *WindMillFan()
{
    Vector<3> center;
    DrawerVisitor *exchangeableVis = nullptr;
    complexSceneHolder *windMillFan = new complexSceneHolder();
    _3DShape *exchangeableShape = nullptr;
    OrientationObject *orient = nullptr;

    exchangeableShape = new Cylinder(Circle({0.0f, 0.0f, -0.01f}, 0.04f, 10, Colour::DarkBrown), 0.5, Colour::DarkBrown);
    orient = exchangeableShape->getOrientation();
    windMillFan->SetMyOrientation(orient);
    center = exchangeableShape->getCenter();
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    windMillFan->addScene(exchangeableVis);

    //  cyl base

    // center cube
    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.25, 0.25, Colour::Brown), 0.1, Colour::Brown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    windMillFan->addScene(exchangeableVis);
    // center Cube

    // arms

    exchangeableShape = new Cuboid(Square({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(90, orient);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(180, orient);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(270, orient);
    windMillFan->addScene(exchangeableVis);
    // arms

    // bar things
    exchangeableShape = new Cuboid(Square({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(90, orient);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(180, orient);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);

    exchangeableVis->Rotate(270, orient);
    windMillFan->addScene(exchangeableVis);
    // bar things
    windMillFan->Translation(Direction::forward, 0.2);
    windMillFan->Translation(Direction::up, 0.3);
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
    float moveCenter = 0.2;
    // base
    exchangeableShape = new Cone(Circle({0, 0, 0}, 0.7, 15, Colour::DarkBrown), 1.5, Colour::DarkBrown);
    center = exchangeableShape->getCenter();
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    orient = exchangeableShape->getOrientation();
    windMill->SetMyOrientation(orient);
    exchangeableVis->RotateX(270);
    exchangeableVis->Translation(Direction::down, 1);
    exchangeableVis->Translation(Direction::forward, moveCenter);
    windMill->addScene(exchangeableVis);

    exchangeableShape = new Cone(Circle({0, 0, 0}, 0.6, 15, Colour::Brown), 1.5, Colour::Brown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(270);
    exchangeableVis->Translation(Direction::down, 0.8);
    exchangeableVis->Translation(Direction::forward, moveCenter);
    windMill->addScene(exchangeableVis);

    exchangeableShape = new Cone(Circle({0, 0, 0}, 0.5, 15, Colour::DarkBrown), 1.5, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(270);
    exchangeableVis->Translation(Direction::down, 0.6);
    exchangeableVis->Translation(Direction::forward, moveCenter);
    windMill->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 2, 0.5, Colour::DarkBrown), 0.5, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 0.5);
    exchangeableVis->Translation(Direction::forward, 0.7);

    windMill->addScene(exchangeableVis);

    exchangeableShape = new Cone(Circle({0, 0, 0}, 0.5, 15, Colour::Brown), 0.5, Colour::Brown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(270);
    exchangeableVis->RotateY(90);
    exchangeableVis->Translation(Direction::up, 0.6);
    exchangeableVis->Translation(Direction::forward, 0.7);

    windMill->addScene(exchangeableVis);
    windMill->Translation(Direction::up, 0.3);

    return windMill;
}

complexSceneHolder *grounds()
{
    Vector<3> center;
    DrawerVisitor *exchangeableVis = nullptr;
    complexSceneHolder *grounds = new complexSceneHolder();
    _3DShape *exchangeableShape = nullptr;
    OrientationObject *orient = nullptr;
    float moveCenter = 0.2;
    float scaleValue = 2;

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 1, Colour::Green), 4.4, Colour::Green);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.8);
    exchangeableVis->Translation(Direction::back, 2.2);
    exchangeableVis->Translation(Direction::left, 0.8);
    grounds->addScene(exchangeableVis);
    orient = exchangeableShape->getOrientation();
    grounds->SetMyOrientation(orient);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 1, Colour::Green), 4.4, Colour::Green);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.8);
    exchangeableVis->Translation(Direction::back, 2.2);
    exchangeableVis->Translation(Direction::right, 0.8);
    grounds->addScene(exchangeableVis);
    orient = exchangeableShape->getOrientation();
    grounds->SetMyOrientation(orient);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 0.6, Colour::Blue), 4.4, Colour::Blue);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.8);
    exchangeableVis->Translation(Direction::back, 2.2);

    grounds->addScene(exchangeableVis);
    orient = exchangeableShape->getOrientation();
    grounds->SetMyOrientation(orient);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 0.05, Colour::Grey), 4, Colour::Grey);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.6);
    exchangeableVis->Translation(Direction::back, 2);
    exchangeableVis->Translation(Direction::left, 1 - 0.025);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 0.05, Colour::Grey), 2, Colour::Grey);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.6);
    exchangeableVis->Translation(Direction::forward, 1 - 0.025);
    exchangeableVis->RotateY(90);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 0.05, Colour::Grey), 4, Colour::Grey);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.6);
    exchangeableVis->Translation(Direction::back, 2);
    exchangeableVis->Translation(Direction::right, 1 - 0.025);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 0.05, Colour::Grey), 2, Colour::Grey);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.6);
    exchangeableVis->Translation(Direction::back, (3 - 0.025));
    exchangeableVis->RotateY(90);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 0.05, Colour::Grey), 2, Colour::Grey);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.6);
    exchangeableVis->Translation(Direction::back, (3 - 0.025));
    exchangeableVis->RotateY(90);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 0.8, Colour::DarkBrown), 0.3, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::forward, 1.4);
    exchangeableVis->Translation(Direction::down, 1.795);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 0.8, Colour::DarkBrown), 0.3, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::back, 1.4);
    exchangeableVis->Translation(Direction::down, 1.795);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.2, 0.8, Colour::DarkBrown), 1, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::back, 0.3);
    exchangeableVis->Translation(Direction::down, 1.795);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.07, 0.4, Colour::DarkBrown), 0.5, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.5);
    exchangeableVis->Translation(Direction::forward, 0.35);
    exchangeableVis->RotateX(90);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.07, 0.4, Colour::DarkBrown), 0.5, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.5);
    exchangeableVis->Translation(Direction::back, 0.42);
    exchangeableVis->RotateX(90);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cylinder(Circle({0, 0, 0}, 0.1, 10, Colour::Black), 0.2, Colour::Black);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(90);
    exchangeableVis->Translation(Direction::down, 1.795);
    exchangeableVis->Translation(Direction::right, 0.6);
    exchangeableVis->Translation(Direction::forward, 1.4);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new TriangularPrism(Square({0, 0, 0}, 0.1, 0.2, Colour::Red), 0.2, Colour::Red);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.6);
    exchangeableVis->Translation(Direction::forward, 1.8);
    exchangeableVis->Translation(Direction::right, 0.9);
    exchangeableVis->RotateY(90);
    exchangeableVis->RotateX(90);
    exchangeableVis->RotateY(60);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new TriangularPrism(Square({0, 0, 0}, 0.1, 0.2, Colour::Red), 0.2, Colour::Red);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.6);
    exchangeableVis->Translation(Direction::back, 2);
    exchangeableVis->Translation(Direction::left, 0.9);
    exchangeableVis->RotateY(90);
    exchangeableVis->RotateX(90);
    exchangeableVis->RotateY(60);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new TriangularPrism(Square({0, 0, 0}, 0.1, 0.2, Colour::Red), 0.2, Colour::Red);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.6);
    exchangeableVis->Translation(Direction::back, 2);
    exchangeableVis->Translation(Direction::right, 0.9);
    exchangeableVis->RotateY(90);
    exchangeableVis->RotateX(90);
    exchangeableVis->RotateY(120);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new TriangularPrism(Square({0, 0, 0}, 0.1, 0.2, Colour::Red), 0.2, Colour::Red);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.6);
    exchangeableVis->Translation(Direction::forward, 1.8);
    exchangeableVis->Translation(Direction::left, 0.9);
    exchangeableVis->RotateY(90);
    exchangeableVis->RotateX(90);
    exchangeableVis->RotateY(120);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square({0, 0, 0}, 0.1, 0.3, Colour::Magenta), 0.5, Colour::Magenta);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->Translation(Direction::down, 1.695);
    exchangeableVis->Translation(Direction::left, 0.7);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Cylinder(Circle({0, 0, 0}, 0.1, 10, Colour::Brown), 0.5, Colour::Brown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(90);
    exchangeableVis->Translation(Direction::down, 1.5);
    exchangeableVis->Translation(Direction::right, 1);
    exchangeableVis->Translation(Direction::forward, 1.8);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Sphere({0, 0, 0}, 0.2, 10, 10, Colour::Green);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(90);
    exchangeableVis->Translation(Direction::down, 1.2);
    exchangeableVis->Translation(Direction::right, 1);
    exchangeableVis->Translation(Direction::forward, 2.05);
    grounds->addScene(exchangeableVis);



    exchangeableShape = new Cylinder(Circle({0, 0, 0}, 0.1, 10, Colour::Brown), 0.5, Colour::Brown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(90);
    exchangeableVis->Translation(Direction::down, 1.5);
    exchangeableVis->Translation(Direction::right, 1);
    exchangeableVis->Translation(Direction::back, 2.4);
    grounds->addScene(exchangeableVis);

    exchangeableShape = new Sphere({0, 0, 0}, 0.2, 10, 10, Colour::Green);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->RotateX(90);
    exchangeableVis->Translation(Direction::down, 1.2);
    exchangeableVis->Translation(Direction::right, 1);
    exchangeableVis->Translation(Direction::back, 2.15);
    grounds->addScene(exchangeableVis);

    grounds->Scale(scaleValue);
    return grounds;
}

complexSceneHolder *GolfCourse()
{
    complexSceneHolder *totalScene = new complexSceneHolder;
    totalScene->addScene(WindMillFan());
    totalScene->SetMyOrientation(totalScene->getIndex(0)->getMyOrientation());

    totalScene->addScene(WindMillTower());
    totalScene->RotateY(90);
    totalScene->Translation(Direction::left, 0.5);
    totalScene->Scale(1.3);
    totalScene->Translation(Direction::up, 1);

    totalScene->addScene(grounds());

    return totalScene;
}

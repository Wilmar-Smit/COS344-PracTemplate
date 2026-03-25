#include "assets.h"
complexSceneHolder *WindMillFan()
{
    Vector<3> center;
    DrawerVisitor *exchangeableVis = nullptr;
    complexSceneHolder *windMillFan = new complexSceneHolder();
    _3DShape *exchangeableShape = nullptr;

    // cyl base
    exchangeableShape = new Cylinder(Circle<3>({0.0f, 0.0f, -0.01f}, 0.04f, 10, Colour::DarkBrown), 0.15, Colour::DarkBrown);
    center = exchangeableShape->getCenter();
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    windMillFan->addScene(exchangeableVis);
    //  cyl base

    // center cube
    exchangeableShape = new Cuboid(Square<3>({0, 0, 0}, 0.25, 0.25, Colour::Brown), 0.1, Colour::Brown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    windMillFan->addScene(exchangeableVis);
    // center Cube

    // arms

    exchangeableShape = new Cuboid(Square<3>({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    exchangeableVis->Rotate(90);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    exchangeableVis->Rotate(180);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0, 0}, 0.25, 0.8, Colour::White), 0.1, Colour::White);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    exchangeableVis->Rotate(270);
    windMillFan->addScene(exchangeableVis);
    // arms

    exchangeableShape = new Cuboid(Square<3>({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    exchangeableVis->Rotate(0);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    exchangeableVis->Rotate(90);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    exchangeableVis->Rotate(180);
    windMillFan->addScene(exchangeableVis);

    exchangeableShape = new Cuboid(Square<3>({0.525, 0.1, -0.01}, 0.08, 0.82, Colour::DarkBrown), 0.115, Colour::DarkBrown);
    exchangeableVis = new DrawerVisitor(exchangeableShape);
    exchangeableVis->setGivenCenter(center);
    exchangeableVis->Rotate(270);
    windMillFan->addScene(exchangeableVis);

    return windMillFan;
}
complexSceneHolder *WindMillTower()
{
}

TotalScene *GolfCourse()
{
    TotalScene *totalScene = new TotalScene();
    totalScene->addScene(WindMillFan());
    return totalScene;
}
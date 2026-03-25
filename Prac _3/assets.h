#ifndef ASSETS_H
#define ASSETS_H
#include "2D shapes/Triangle.h"
#include "Vector.h"
#include "Matrix.h"
#include "2D shapes/Square.h"

#include "2D shapes/circle.h"
#include "3D_shapes/Cylinder.h"
#include "3D_shapes/SquarePyramid.h"
#include "sceneClasses/drawerVisitor.h"
#include "3D_shapes/Sphere.h"
#include "3D_shapes/Cuboid.h"
#include "borderClasses/borderContainer.h"
#include "borderClasses/borderShape.h"
#include "sceneClasses/complexSceneHolder.h"
#include "sceneClasses/TotalScene.h"

complexSceneHolder *WindMillFan();
complexSceneHolder *WindMillTower();
TotalScene *GolfCourse();
#endif
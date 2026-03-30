#ifndef DRAWERVISITOR_H
#define DRAWERVISITOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/MathLibrary/2D shapes/Shape.h"
#include "../include/MathLibrary/Matrix.h"
#include "../include/MathLibrary/3D_shapes/3D_Shape.h"
#include "../include/MathLibrary/3D_shapes/Cone.h"
#include "../include/MathLibrary/3D_shapes/Cuboid.h"
#include "../include/MathLibrary/3D_shapes/Cylinder.h"
#include "../include/MathLibrary/3D_shapes/SquarePyramid.h"
#include "../include/MathLibrary/3D_shapes/TriangularPrism.h"
#include "../include/MathLibrary/3D_shapes/Sphere.h"
#include <vector>
#include "Scene.h"

class DrawerVisitor : public Scene
{

protected:
    _3DShape *shape;
    std::vector<Shape<3> *> shapes;
    std::vector<int> vertexCounts;

    std::vector<GLuint> VAO, VBO;
    GLenum type = GL_TRIANGLE_FAN;

    static const int COLOR_DEPTH = 4;
    static const int VERTEX_DEPTH = 3;

public:
    DrawerVisitor(_3DShape *shape);
    virtual ~DrawerVisitor() override;
    virtual void draw();
    virtual void reloadVertices();
    virtual Shape<3> *getShape() const;
    virtual void addScene(DrawerVisitor *scene) override;
    virtual void Rotate(float degrees);
    virtual void RotateX(float degrees);
    virtual void RotateY(float degrees);
    virtual void RotateZ(float degrees);
    virtual void Scale(float scale);
    virtual void Translation(Direction dir, float step);
    virtual void select();
    virtual void deselect();
    virtual void setWireframeMode();
    virtual void setNormalMode();
    virtual void setParent(DrawerVisitor *parent) {};
    virtual DrawerVisitor *selectNext();
    virtual DrawerVisitor *getIndex(int i);
    virtual void transform(Matrix<4, 4> &trans, bool toCenter);

    void Visit(Cone *cone);
    void Visit(Cuboid *cuboid);
    void Visit(Cylinder *cyl);
    void Visit(SquarePyramid *squarePyramid);
    void Visit(TriangularPrism *triangularPrism);
    void Visit(Sphere *sphere);
    void Visit(_3DShape *shape);
};

#endif

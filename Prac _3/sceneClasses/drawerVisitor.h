#ifndef DRAWERVISITOR_H
#define DRAWERVISITOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/MathLibrary/2D shapes/Shape.h"
#include "../include/MathLibrary/Matrix.h"
#include "../include/MathLibrary/3D shapes/3D_Shape.h"
#include "../include/MathLibrary/3D shapes/Cylinder.h"
#include "drawer.h"
#include <vector>

template <int n>
class DrawerVisitor :public Scene<n>
{
    friend class Cylinder<n>;

protected:
    _3DShape<n> *shape;             // will visit this.
    std::vector<Shape<n> *> shapes; // specific sub-shapes to draw/manage.
    DrawerVisitor<n> *parent = nullptr;

    // this is the original that will bypass the pointer
    // 3D shape will call the visitor and put Visit(this) with its correct 3d pointer basically double d

    std::vector<GLuint> VAO, VBO;  // now vectors
    GLenum type = GL_TRIANGLE_FAN; // the draw typ

    static const int COLOR_DEPTH = 4;
    static const int VERTEX_DEPTH = n;

public:
    DrawerVisitor(_3DShape<n> *shape); // does the visiting on shape
    virtual ~DrawerVisitor() { delete shape; };
    virtual void draw();
    virtual void reloadVertices();
    virtual Shape<n> *getShape() const;
    virtual void addScene(Scene<n> *scene) override;
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
    virtual void setParent(DrawerVisitor *parent) { this->parent = parent; };
    virtual DrawerVisitor<n> *selectNext();
    virtual DrawerVisitor<n> *getIndex(int i);
    virtual void transform(Matrix<n + 1, n + 1> &trans, bool toCenter);
    void Visit(Cylinder<n> *cyl); // visits the cylinder and populates the array
    void Visit(_3DShape<n> *shape);
};

#include "drawerVisitor.cpp"

#endif

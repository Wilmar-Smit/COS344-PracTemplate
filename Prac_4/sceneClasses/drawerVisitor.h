#ifndef DRAWERVISITOR_H
#define DRAWERVISITOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../MathLibrary/2D_shapes/Shape.h"
#include "../MathLibrary/Matrix.h"
#include "../MathLibrary/3D_shapes/3D_Shape.h"

#include "../MathLibrary/3D_shapes/Cuboid.h"
#include "../MathLibrary/3D_shapes/multiFacedSurface.h"
#include "../MathLibrary/3D_shapes/Sphere.h"
#include <vector>
#include "Scene.h"
#include "../camera/camera.h"
class DrawerVisitor : public Scene
{
protected:
    _3DShape *shape;
    std::vector<Shape *> shapes;
    std::vector<int> vertexCounts;

    std::vector<GLuint> VAO, VBO;
    GLenum type = GL_TRIANGLES;

    static const int COLOR_DEPTH = 4;
    static const int VERTEX_DEPTH = 3;
    static const int UV_DEPTH = 2;
    static const int NORMAL_DEPTH = 3;

private:
    void collectChildShapes();
    void rebuildGpuBuffers();

public:
    DrawerVisitor(_3DShape *shape);
    virtual ~DrawerVisitor() override;

    virtual void draw();
    virtual void reloadVertices();
    virtual Shape *getShape() const;
    virtual void addScene(Scene *scene) override;

    // Transform operations with optional orientation
    virtual void Rotate(float degrees, OrientationObject *orient = nullptr);
    virtual void RotateX(float degrees, OrientationObject *orient = nullptr);
    virtual void RotateY(float degrees, OrientationObject *orient = nullptr);
    virtual void RotateZ(float degrees, OrientationObject *orient = nullptr);
    virtual void Scale(float scale, OrientationObject *orient = nullptr);
    virtual void Translation(Direction dir, float step, OrientationObject *orient = nullptr);
    virtual Matrix<4, 4> transform(Matrix<4, 4> &trans, bool toCenter, OrientationObject *orient = nullptr);

    virtual void setWireframeMode();
    virtual void setNormalMode();
    virtual void setParent(DrawerVisitor *parent) {};
    virtual DrawerVisitor *selectNext();
    virtual DrawerVisitor *getIndex(int i);
    virtual void RotateArbitrary(float degrees, OrientationObject *orient = nullptr);
    void setShape(_3DShape *s) { this->shape = s; this->Visit(s); }

    void Visit(Cuboid *cuboid);
    void Visit(Sphere *sphere);
    void Visit(_3DShape *shape);
    void Visit(MultiFacedSurface *shape);
    void registerShape(Shape *shape);
};

#endif

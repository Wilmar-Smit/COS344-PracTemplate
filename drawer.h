#ifndef DRAWER_H
#define DRAWER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shape.h"
#include "GolfShapes/GolfShape.h"

class Drawer
{
private:
    int numVertices; // number of vertices
    int vertexDepth; // number of floats per position (2 for 2D, 3 for 3D)
    GLuint VAO, VBO;
    GLenum type;

    static const int COLOR_DEPTH = 4; // always RGBA

    GolfShape *golfShape; // reference to the shape being drawn

public:
    Drawer(GolfShape *shape, int vertexDepth, int numVertices, GLenum type);

    void draw();

    void reloadVertices();
    GolfShape *getShape() const;
};

#endif

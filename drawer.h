#ifndef DRAWER_H
#define DRAWER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Drawer
{
private:
    int numVertices;   // number of vertices
    int vertexDepth;   // number of floats per position (2 for 2D, 3 for 3D)
    GLuint VAO, VBO;
    GLenum type;

    static const int COLOR_DEPTH = 4; // always RGBA

public:
    Drawer(float *vertices, int vertexDepth, int numVertices, GLenum type);
    void draw();
};

#endif

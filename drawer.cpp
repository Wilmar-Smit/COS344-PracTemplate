#include "drawer.h"

Drawer::Drawer(GolfShape *shape, int vertexDepth, int numVertices, GLenum type)
    : golfShape(shape), vertexDepth(vertexDepth), numVertices(numVertices), type(type)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float *vertices = shape->exportValues();

    glBufferData(GL_ARRAY_BUFFER, numVertices * (vertexDepth + COLOR_DEPTH) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    delete[] vertices;

    glVertexAttribPointer(0, vertexDepth, GL_FLOAT, GL_FALSE, (vertexDepth + COLOR_DEPTH) * sizeof(GLfloat), (const void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, COLOR_DEPTH, GL_FLOAT, GL_FALSE, (vertexDepth + COLOR_DEPTH) * sizeof(GLfloat), (const void *)(vertexDepth * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Drawer::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(type, 0, numVertices);
}
void Drawer::reloadVertices()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float *vertices = golfShape->exportValues();
    glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * (vertexDepth + COLOR_DEPTH) * sizeof(float), vertices);
    delete[] vertices;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GolfShape *Drawer::getShape() const
{
    return golfShape;
}
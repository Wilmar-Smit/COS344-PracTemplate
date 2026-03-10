#include "drawer.h"

Drawer::Drawer(float *vertices, int vertexDepth, int numVertices, GLenum type)
    : vertexDepth(vertexDepth), numVertices(numVertices), type(type)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * (vertexDepth + COLOR_DEPTH) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, vertexDepth, GL_FLOAT, GL_FALSE, (vertexDepth + COLOR_DEPTH) * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, COLOR_DEPTH, GL_FLOAT, GL_FALSE, (vertexDepth + COLOR_DEPTH) * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); 
}

void Drawer::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(type, 0, numVertices);
}

#include "drawer.h"

template <int n>
Drawer<n>::Drawer(Shape<n> *shape, GLenum type) : shape(shape), numVertices(shape->getNumSides()), type(type)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float *vertices = shape->exportValues();

    glBufferData(GL_ARRAY_BUFFER, numVertices * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    delete[] vertices;

    // position attribute (location 0)
    glVertexAttribPointer(0, VERTEX_DEPTH, GL_FLOAT, GL_FALSE, (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), (const void *)0);
    glEnableVertexAttribArray(0);

    // colour attribute (location 1)
    glVertexAttribPointer(1, COLOR_DEPTH, GL_FLOAT, GL_FALSE, (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), (const void *)(VERTEX_DEPTH * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

template <int n>
void Drawer<n>::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(type, 0, numVertices);
    glBindVertexArray(0);
}

template <int n>
void Drawer<n>::reloadVertices()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float *vertices = shape->exportValues();
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    numVertices * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(float),
                    vertices);
    delete[] vertices;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <int n>
Shape<n> *Drawer<n>::getShape() const
{
    return shape;
}

template <int n>
void Drawer<n>::addScene(Scene<n> *scene)
{
    (void)scene;
}

template <int n>
Drawer<n>::~Drawer()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    delete shape;
}
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

void Drawer<n>::setWireframeMode()
{
    float *vertices = shape->exportWireframe();
    numVertices = shape->getNumSides() * 2;
    type = GL_LINES;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    delete[] vertices;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <int n>
void Drawer<n>::setNormalMode()
{
    float *vertices = shape->exportValues();
    numVertices = shape->getNumSides();
    type = GL_TRIANGLE_FAN;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    delete[] vertices;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    if (type == GL_TRIANGLE_FAN)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float *vertices = shape->exportValues();
        glBufferSubData(GL_ARRAY_BUFFER, 0,
                        numVertices * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(float),
                        vertices);
        delete[] vertices;
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float *vertices = shape->exportWireframe();
        glBufferSubData(GL_ARRAY_BUFFER, 0,
                        shape->getNumSides() * 2 * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(float),
                        vertices);
        delete[] vertices;
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
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
template <int n>
void Drawer<n>::Rotate(float degrees)
{
    float radians = degrees * (std::acos(-1.0f) / 180.0f);
    float cosTheta = std::cos(radians);
    float sinTheta = std::sin(radians);

    Matrix<n + 1, n + 1> rotationMatrix;
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n + 1; j++)
            rotationMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

    rotationMatrix[0][0] = cosTheta;
    rotationMatrix[0][1] = -sinTheta;
    rotationMatrix[1][0] = sinTheta;
    rotationMatrix[1][1] = cosTheta;

    transform(rotationMatrix, true);
}

template <int n>
void Drawer<n>::Scale(float scaleFactor)
{
    Matrix<n + 1, n + 1> scaleMatrix;
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n + 1; j++)
            scaleMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

    for (int i = 0; i < n; i++)
        scaleMatrix[i][i] = scaleFactor;

    transform(scaleMatrix, true);
}

template <int n>
void Drawer<n>::Translation(Direction direction, float stepSize)
{
    float dx = 0.0f, dy = 0.0f;
    if (direction == Direction::up)
        dy = stepSize;
    if (direction == Direction::down)
        dy = -stepSize;
    if (direction == Direction::left)
        dx = -stepSize;
    if (direction == Direction::right)
        dx = stepSize;

    Matrix<n + 1, n + 1> translationMatrix;
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n + 1; j++)
            translationMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

    translationMatrix[0][n] = dx;
    translationMatrix[1][n] = dy;

    transform(translationMatrix, false);
}

template <int n>
void Drawer<n>::select()
{
    if (!this->selected)
    {
        shape->setCoulourVec(shape->getColourPas());
    }
    else
    {
        shape->setCoulourVec(shape->dePastel(shape->getColourVec()));
    }
    this->selected = !this->selected;
    reloadVertices();
}

template <int n>
void Drawer<n>::deselect()
{
    if (this->selected)
    {
        this->select();
    }
}
template <int n>
void Drawer<n>::transform(Matrix<n + 1, n + 1> &localTransform, bool relativeToCenter)
{
    Matrix<n + 1, n + 1> fullTransform = localTransform;

    if (relativeToCenter)
    {
        Vector<n> center = shape->getCenter();

        Matrix<n + 1, n + 1> toCenter, backToOrigin;
        for (int i = 0; i < n + 1; i++)
            for (int j = 0; j < n + 1; j++)
            {
                toCenter[i][j] = (i == j) ? 1.0f : 0.0f;
                backToOrigin[i][j] = (i == j) ? 1.0f : 0.0f;
            }

        for (int i = 0; i < n; i++)
        {
            toCenter[i][n] = -center[i];
            backToOrigin[i][n] = center[i];
        }

        fullTransform = backToOrigin * localTransform * toCenter;
    }

    shape->applyMatrix(fullTransform);

    reloadVertices();
}

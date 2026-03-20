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
    float c = std::cos(radians);
    float s = std::sin(radians);

    Matrix<n, n> rot;

    for (int i = 0; i < n; i++)
    {
        rot[i][i] = 1;
    }
    rot[0][0] = c;
    rot[0][1] = -s;
    rot[1][0] = s;
    rot[1][1] = c;

    Vector<n> center = this->shape->getCenter();
    std::vector<Vector<n>> points = this->shape->getVectors();

    for (int i = 0; i < points.size(); i++)
    {
        points[i] = points[i] - center;
    }

    this->shape->setVectors(points);

    *(this->shape) *= rot;

    points = this->shape->getVectors();
    for (int i = 0; i < points.size(); i++)
    {
        points[i] = points[i] + center;
    }
    this->shape->setVectors(points);

    reloadVertices();
}
template <int n>
void Drawer<n>::Scale(float scale)
{
    Matrix<n, n> scaleMat;
    for (int i = 0; i < n; i++)
        scaleMat[i][i] = scale;

    Vector<n> center = this->shape->getCenter();
    std::vector<Vector<n>> points = this->shape->getVectors();

    // Move points relative to center
    for (auto &p : points)
        p = p - center;

    // Scale points
    for (auto &p : points)
        p = scaleMat * (Matrix<n, 1>)p;

    // Move points back
    for (auto &p : points)
        p = p + center;

    this->shape->setVectors(points);

    reloadVertices();
}

template <int n>
void Drawer<n>::Translation(Direction dir, float step)
{
    float dx = 0, dy = 0;

    if (dir == Direction::up)
        dy = step;
    if (dir == Direction::down)
        dy = -step;
    if (dir == Direction::left)
        dx = -step;
    if (dir == Direction::right)
        dx = step;

    if (n == 2)
    {

        std::vector<Vector<n>> points = this->shape->getVectors();

        for (int i = 0; i < points.size(); i++)
        {
            points[i][0] += dx;
            points[i][1] += dy;
        }

        this->shape->setVectors(points);
    }
    else
    {

        Matrix<n, n> transMat;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                transMat[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }

        transMat[0][n - 1] = dx;
        transMat[1][n - 1] = dy;

        *(this->shape) *= transMat;
    }

    reloadVertices();
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
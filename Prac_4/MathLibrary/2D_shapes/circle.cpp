#include "circle.h"

Circle::Circle(const Vector<3> &c, float r, int vCount, Colour col)
    : Shape(col),
      numVertices(vCount),
      vertices(vCount + 2, c),
      center(vertices.front()),
      radius(r)
{
    generateVertices();
}
Circle::Circle(const Circle &other)
    : Shape(other),
      numVertices(other.numVertices),
      vertices(other.vertices),
      center(vertices.front()),
      radius(other.radius)
{
    this->colour = other.colour;
}

void Circle::generateVertices()
{
    const double PI = std::acos(-1.0);
    for (int i = 0; i <= numVertices; i++)
    {
        double angle = 2.0 * PI * i / numVertices;
        Vector<3> p = center;
        p[0] = center[0] + radius * std::cos(angle);
        p[1] = center[1] + radius * std::sin(angle);
        vertices[i + 1] = p;
    }
}

Circle &Circle::operator*=(const Matrix<3, 3> &m)
{
    // 1. Transform the vertices
    for (auto &v : vertices)
    {
        v = m * (Matrix<3, 1>)v;
    }

    return *this;
}

Circle *Circle::operator*(const Matrix<3, 3> &m) const
{
    Circle *result = new Circle(*this);

    *result *= m;

    return result;
}
float *Circle::getPoints() const
{

    int totalElements = vertices.size() * this->n;
    float *arr = new float[totalElements];
    int count = 0;
    for (size_t i = 0; i < vertices.size(); i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            arr[count++] = vertices[i][j];
        }
    }
    return arr;
}

void Circle::setVectors(std::vector<Vector<3>> v)
{
    if (v.size() != vertices.size())
    {
        return;
    }

    for (size_t i = 0; i < vertices.size(); i++)
    {
        vertices[i] = v[i];
    }
}

void Circle::print() const
{
}

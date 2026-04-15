#include "Triangle.h"
// n >=
Triangle::Triangle(const Vector<3> &p1, const Vector<3> &p2, const Vector<3> &p3, Colour col) : Shape(col)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Triangle::Triangle(const Triangle &other, Colour col) : Shape(col)
{
    this->p1 = other.p1;
    this->p2 = other.p2;
    this->p3 = other.p3;
}
Triangle::Triangle(const Vector<3> &p1, const Vector<3> &p2, const Vector<3> &p3) : Shape()
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}



Triangle::Triangle(const Triangle &other) : Shape()
{
    this->colour = other.colour;
    this->p1 = other.p1;
    this->p2 = other.p2;
    this->p3 = other.p3;
}

Triangle &Triangle::operator*=(const Matrix<3, 3> &m)
{
    // Build a matrix with 3 columns, each column is one vertex
    Matrix<3, 3> triMat;
    for (int i = 0; i < this->n; i++)
    {
        triMat[i][0] = p1[i];
        triMat[i][1] = p2[i];
        triMat[i][2] = p3[i];
    }

    // Multiply transformation matrix by triangle matrix
    Matrix<3, 3> result = m * triMat;

    // Translate back into Vectors
    Vector<3> newP1;
    Vector<3> newP2;
    Vector<3> newP3;
    for (int i = 0; i < this->n; i++)
    {
        newP1[i] = result[i][0];
        newP2[i] = result[i][1];
        newP3[i] = result[i][2];
    }

    // Update the triangle
    p1 = newP1;
    p2 = newP2;
    p3 = newP3;

    return *this;
}

Triangle *Triangle::operator*(const Matrix<3, 3> &m) const
{

    Matrix<3, 3> triMat;
    for (int i = 0; i < this->n; i++)
    {
        triMat[i][0] = p1[i];
        triMat[i][1] = p2[i];
        triMat[i][2] = p3[i];
    }

    Matrix<3, 3> result = m * triMat;

    Vector<3> newP1;
    Vector<3> newP2;
    Vector<3> newP3;

    for (int i = 0; i < this->n; i++)
    {
        newP1[i] = result[i][0];
        newP2[i] = result[i][1];
        newP3[i] = result[i][2];
    }

    Triangle *newTriangle = new Triangle(newP1, newP2, newP3);
    newTriangle->colour = this->colour;
    return newTriangle;
}

float *Triangle::getPoints() const
{
    float *arr = new float[this->n * 3];
    for (int i = 0; i < this->n; i++)
    {
        arr[i] = p1[i];
        arr[i + this->n] = p2[i];
        arr[i + 2 * this->n] = p3[i];
    }
    return arr;
}

int Triangle::getNumPoints() const
{

    return this->n * 3;
}
Triangle::Triangle(const Vector<3> &center, float sideLength, Colour col) : Shape(col)
{
    // makes an equilateral triangle
    float R = sideLength / std::sqrt(3);
    const double PI = std::acos(-1); // gives pi

    p1[0] = center[0] + R * std::cos(0 * PI / 3);
    p1[1] = center[1] + R * std::sin(0 * PI / 3);

    p2[0] = center[0] + R * std::cos(2 * PI / 3);
    p2[1] = center[1] + R * std::sin(2 * PI / 3);

    p3[0] = center[0] + R * std::cos(4 * PI / 3);
    p3[1] = center[1] + R * std::sin(4 * PI / 3);

    for (int i = 2; i < this->n; i++)
    {
        p1[i] = center[i];
        p2[i] = center[i];
        p3[i] = center[i];
    }
}
std::vector<Vector<3>> Triangle::getVectors()
{
    std::vector<Vector<3>> retVec;
    retVec.push_back(p1);
    retVec.push_back(p2);
    retVec.push_back(p3);
    return retVec;
}
Vector<3> Triangle::getCenter()
{
    Vector<3> center;
    for (int i = 0; i < this->n; i++)
    {
        float sum = 0;

        sum += p1[i];
        sum += p2[i];
        sum += p3[i];

        center[i] = sum / 3;
    }
    return center;
}

void Triangle::setVectors(std::vector<Vector<3>> vec)
{
    p1 = vec[0];
    p2 = vec[1];
    p3 = vec[2];
}
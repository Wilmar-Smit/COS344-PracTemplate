#include "Vector.h"
#include <iostream>

template <int n>
Vector<n>::Vector()
{
    arr = new float[n]();
}

template <int n>
Vector<n>::Vector(std::initializer_list<float> list)
{
    arr = new float[n]; // allocate memory for the vector

    int i = 0;
    for (auto it = list.begin(); it != list.end() && i < n; ++it, ++i)
    {
        arr[i] = *it;
    }
}

template <int n>
Vector<n>::Vector(float *arr)
{
    this->arr = arr;
}

template <int n>
Vector<n>::~Vector()
{
    if (arr)
        delete[] arr;
}

template <int n>
Vector<n>::Vector(const Vector<n> &other)
{
    arr = new float[n];

    for (int i = 0; i < n; i++)
    {
        this->arr[i] = other.arr[i];
    }
}

template <int n>
Vector<n>::Vector(const Matrix<n, 1> &mat)
{
    arr = new float[n];
    for (int i = 0; i < n; i++)
    {
        this->arr[i] = mat[i][0];
    }
}

template <int n>
Vector<n> &Vector<n>::operator=(const Vector<n> &other)
{
    if (&other == this)
    {
        return *this;
    }

    if (arr)
        delete[] this->arr;

    this->arr = new float[n];

    for (int i = 0; i < n; i++)
    {
        this->arr[i] = other.arr[i];
    }
    return *this;
}

template <int n>
Vector<n> Vector<n>::operator+(const Vector<n> other) const
{
    Vector<n> retVec(*this);
    for (int i = 0; i < n; i++)
    {
        retVec.arr[i] += other.arr[i];
    }
    return retVec;
}

template <int n>
Vector<n> Vector<n>::operator-(const Vector<n> other) const
{
    Vector<n> retVec(*this);
    for (int i = 0; i < n; i++)
    {
        retVec.arr[i] -= other.arr[i];
    }
    return retVec;
}
template <int n>
Vector<n> Vector<n>::operator*(const float scalar) const
{
    Vector<n> retVec(*this);
    for (int i = 0; i < n; i++)
    {
        retVec.arr[i] *= scalar;
    }
    return retVec;
}
template <int n>
float Vector<n>::operator*(const Vector<n> other) const
{
    float retVal = 0;
    for (int i = 0; i < n; i++)
    {
        retVal += this->arr[i] * other.arr[i];
    }
    return retVal;
}

template <int n>
float Vector<n>::magnitude() const
{
    float retVal = 0;
    for (int i = 0; i < n; i++)
    {
        retVal += (this->arr[i] * this->arr[i]);
    }
    return std::sqrt(retVal);
}

template <int n>
Vector<n>::operator Matrix<n, 1>() const
{
    Matrix<n, 1> retMat;
    for (int i = 0; i < n; i++)
    {
        retMat[i][0] = this->arr[i];
    }
    return retMat;
}

template <int n>
Vector<n> Vector<n>::crossProduct(const Vector<n> other) const
{
    if (n != 3)
        return Vector<n>();

    Vector<n> retVec;

    retVec.arr[0] = (this->arr[1] * other.arr[2] - this->arr[2] * other.arr[1]);
    retVec.arr[1] = -(this->arr[0] * other.arr[2] - this->arr[2] * other.arr[0]);
    retVec.arr[2] = (this->arr[0] * other.arr[1] - this->arr[1] * other.arr[0]);

    return retVec;
}

template <int n>
Vector<n> Vector<n>::unitVector() const
{
    Vector<n> retVec(*this);

    retVec = retVec * (1 / retVec.magnitude());
    return retVec;
}

template <int n>
int Vector<n>::getN() const
{
    return n;
}

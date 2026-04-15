#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <sstream>
#include "Matrix.h"
#include <cmath>
template <int n, int m>
class Matrix;

template <int n> // size of the vector
class Vector
{
private:
    float *arr; // array containing the elements in the vector
    // 1 d array of pointers memory managed inside

public:
    Vector();
    Vector(std::initializer_list<float>);
    Vector(float *);
    ~Vector();
    Vector(const Vector<n> &);
    Vector(const Matrix<n, 1> &);
    Vector<n> &operator=(const Vector<n> &);
    Vector<n> operator+(const Vector<n>) const;
    Vector<n> operator-(const Vector<n>) const;
    Vector<n> operator*(const float) const;

    float operator*(const Vector<n>) const;
    float &operator[](int index) const
    {
        if (index < 0 || index >= n)
        {
            throw "Invalid Index";
        }
        return arr[index];
    }
    float magnitude() const;
    operator Matrix<n, 1>() const;
    Vector<n> crossProduct(const Vector<n>) const;
    Vector<n> unitVector() const;
    int getN() const;
    void print() const
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << arr[i] << "\n";
        }
        std::cout << std::endl;
    };
};

template <int n>
std::string vec_to_string(const Vector<n> &vec)
{
    std::stringstream ss;
    for (int i = 0; i < n; ++i)
    {
        ss << vec[i] << "\n";
    }

    return ss.str();
}

#include "Vector.cpp"

#endif /*VECTOR_H*/
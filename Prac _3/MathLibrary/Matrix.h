#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <iomanip>

#include "Vector.h"

template <int n>
class Vector;

template <int n, int m>
class Matrix
{
protected:
    float **arr;

public:
    Matrix();
    Matrix(float **);
    Matrix(const Matrix<n, m> &);

    // makes m== 1
    virtual ~Matrix();
    float *&operator[](int index) const
    {
        if (index >= n || index < 0)
        {
            throw "Invalid index";
        }

        return arr[index];
    }

    Matrix<n, m> &operator=(const Matrix<n, m> &);
    template <int a>
    Matrix<n, a> operator*(const Matrix<m, a>) const;
    Matrix<n, m> operator*(const float) const;
    Matrix<n, m> operator+(const Matrix<n, m>) const;
    Matrix<m, n> operator~() const;
    void print() const
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                std::cout << (*this)[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    int getM() const;
    int getN() const;
    void identity();
    float determinant() const;
};

template <int n, int m, int a>
float multiplyHelper(const Matrix<n, m> &lhs, const Matrix<m, a> &rhs, int row, int col);
// Global helper function for determinant calculation
template <int n, int m>
float determinantHelper(const Matrix<n, m> &mat);
template <int n, int m>
float **matrixReducer(const Matrix<n, m> &mat, int row, int col);

template <int n, int m>
std::string mat_to_string(const Matrix<n, m> &mat)
{
    std::stringstream ss;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            ss << mat[i][j] << " ";
        }
        ss << "\n";
    }
    return ss.str();
}

#include "Matrix.cpp"

#endif /*MATRIX_H*/
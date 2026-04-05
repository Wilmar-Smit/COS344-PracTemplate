#include "Matrix.h"

template <int n, int m>
Matrix<n, m>::Matrix()
{

    arr = new float *[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new float[m]();
    }
}

template <int n, int m>
Matrix<n, m>::Matrix(float **data)
{

    arr = data;
}

template <int n, int m>
Matrix<n, m>::Matrix(const Matrix<n, m> &other)
{
    arr = new float *[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new float[m]();
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            this->arr[i][j] = other[i][j];
        }
    }
}

template <int n, int m>
Matrix<n, m>::~Matrix()
{
    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

template <int n, int m>
Matrix<n, m> &Matrix<n, m>::operator=(const Matrix<n, m> &other)
{
    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    arr = new float *[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new float[m]();
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            this->arr[i][j] = other[i][j];
        }
    }
    return *this;
}

template <int n, int m>
template <int a>
Matrix<n, a> Matrix<n, m>::operator*(const Matrix<m, a> other) const
{

    Matrix<n, a> retMat;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < a; col++)
        {
            retMat[row][col] = multiplyHelper(*this, other, row, col);
        }
    }
    return retMat;
}

template <int n, int m, int a>
float multiplyHelper(const Matrix<n, m> &lhs, const Matrix<m, a> &rhs, int row, int col)
{ // n is the number of rows in lhs
    // m is the number of cols in lhs
    float result = 0;
    for (int lhsRhsIndex = 0; lhsRhsIndex < m; lhsRhsIndex++)
    { // iterate through the cols of row (given row)
        result += lhs[row][lhsRhsIndex] * rhs[lhsRhsIndex][col];
    }
    return result;
}

template <int n, int m>
Matrix<n, m> Matrix<n, m>::operator*(const float scalar) const
{
    Matrix<n, m> retMat(*this);

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            retMat[row][col] *= scalar;
        }
    }
    return retMat;
}

template <int n, int m>
Matrix<n, m> Matrix<n, m>::operator+(const Matrix<n, m> other) const
{
    Matrix<n, m> retMat(*this);

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            retMat[row][col] += other[row][col];
        }
    }
    return retMat;
}

template <int n, int m>
Matrix<m, n> Matrix<n, m>::operator~() const
{
    Matrix<m, n> retMat;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            retMat[col][row] = (*this)[row][col];
        }
    }
    return retMat;
}

template <int n, int m>
int Matrix<n, m>::getM() const
{

    return m;
}

template <int n, int m>
int Matrix<n, m>::getN() const
{

    return n;
}

template <int n, int m>
float Matrix<n, m>::determinant() const
{
    if (n != m)
        throw "Matrix is not square";

    return determinantHelper(*this);
}

template <int n, int m>
float determinantHelper(const Matrix<n, m> &mat)
{

    float result = 0;
    for (int cols = 0; cols < m; cols++)
    {
        int sign = (cols % 2 == 0) ? 1 : -1;

        Matrix<n - 1, m - 1> subMatrix(matrixReducer(mat, 0, cols));

        result += sign * mat[0][cols] * determinantHelper(subMatrix);
    }
    return result;
}

template <>
inline float determinantHelper<1, 1>(const Matrix<1, 1> &mat)
{
    return mat[0][0];
}

template <>
inline float determinantHelper<2, 2>(const Matrix<2, 2> &mat)
{
    return (mat[0][0] * mat[1][1] - (mat[0][1] * mat[1][0]));
}

template <>
inline float determinantHelper<3, 3>(const Matrix<3, 3> &mat)
{
    float left = ((mat[0][0] * mat[1][1] * mat[2][2]) + (mat[0][1] * mat[1][2] * mat[2][0]) + (mat[0][2] * mat[1][0] * mat[2][1]));
    float right = ((mat[0][2] * mat[1][1] * mat[2][0]) + (mat[0][0] * mat[1][2] * mat[2][1]) + (mat[0][1] * mat[1][0] * mat[2][2]));
    return (left - right);
}

template <int n, int m>
float **matrixReducer(const Matrix<n, m> &mat, int row, int col)
{

    int rowSize = n - 1;
    int colSize = m - 1;
    float **arr = new float *[rowSize];

    for (int rows = 0; rows < n; rows++)
    {
        int rowModifier = 0;
        if (rows < row)
            rowModifier = 0;
        else if (rows > row)
            rowModifier = 1;
        else
            continue;

        if (rows != row)
        {
            arr[rows - rowModifier] = new float[colSize];
            for (int cols = 0; cols < m; cols++)
            {
                if (cols < col)
                {
                    arr[rows - rowModifier][cols] = mat[rows][cols];
                }
                else if (cols > col)
                {
                    arr[rows - rowModifier][cols - 1] = mat[rows][cols];
                }
                else
                    continue;
            }
        }
    }

    return arr;
}
template <int n, int m>
void Matrix<n, m>::identity()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = 0;
            if (i == j)
            {
                arr[i][j] = 1;
            }
        }
    }
}
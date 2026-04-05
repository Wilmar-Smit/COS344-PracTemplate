#include "Matrix.h"
#include "Vector.h"
#include "2D_shapes/Shape.h"
#include "2D_shapes/Triangle.h"
#include "2D_shapes/Square.h"

#include <iostream>
#include <sstream>
#include <cmath>
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

bool compareStrings(const std::string &testStr, const std::string &memoStr, bool printResult);
void printResult(bool condition, const std::string &passText);

void VectorTesting();
void MatrixTesitng();
void TriangleTesting();
void SquareTesting();

void VectorTesting()
{
    Vector<3> T0;
    printResult(compareStrings(vec_to_string(T0), "0\n0\n0\n", false), "Testing vector base constructor");
    Vector<3> T1({1, 2, 3});
    printResult(compareStrings(vec_to_string(T1), "1\n2\n3\n", false), "Testing vector list constructor");
    float *arr = new float[]{1, 2, 4};
    Vector<3> T2(arr);
    printResult(compareStrings(vec_to_string(T2), "1\n2\n4\n", false), "Testing vector array constructor");
    Vector<3> T3(T2);
    printResult(compareStrings(vec_to_string(T3), vec_to_string(T2), false), "Testing vector copy constructor");

    Vector<3> T4 = T1;
    printResult(compareStrings(vec_to_string(T4), vec_to_string(T1), false), "Testing vector assignment operator");
    Vector<3> T5 = T4 = T3;
    printResult(compareStrings(vec_to_string(T5), vec_to_string(T3), false), "Testing vector assignment operator (chained assignment)");
    Vector<3> T6 = T5 = T5;
    printResult(compareStrings(vec_to_string(T5), vec_to_string(T3), false), "Testing vector assignment operator (self assignment)");

    printResult(compareStrings(vec_to_string(T1 + T1), vec_to_string(Vector<3>({2, 4, 6})), false), "Testing vector addition ");

    printResult(compareStrings(vec_to_string(T1 - T1), vec_to_string(Vector<3>({0, 0, 0})), false), "Testing vector subtraction ");

    printResult(compareStrings(vec_to_string(T1 * 2), vec_to_string(Vector<3>({2, 4, 6})), false), "Testing vector scalar multiplication ");

    printResult((T1.magnitude()) == std::sqrtf(14), "Testing vector magnitude");

    printResult(compareStrings(vec_to_string(T1.crossProduct(T3)), vec_to_string(Vector<3>({2, -1, 0})), false), "Testing vector cross product  ");
    printResult((T1.crossProduct(T3) * T1) == 0, "Testing cross product math  (orthogonal {1,2,3})");
    printResult((T1.crossProduct(T3) * T3) == 0, "Testing cross product math (orthogonal {1,2,4})");
    const float mag = T1.magnitude();
    printResult(compareStrings(vec_to_string(T1.unitVector()), vec_to_string(Vector<3>({1 / mag, 2 / mag, 3 / mag})), false), "Testing vector unit vector");
    printResult(std::round(T1.unitVector().magnitude()) == 1, "Testing unit vector math ");
    printResult(std::round(T1.getN()) == 3, "Testing vector get n ");

    Matrix<3, 1> VmatrixCon;
    Vector<3> Vmat(VmatrixCon);

    printResult(compareStrings(vec_to_string(Vmat), vec_to_string(Vector<3>({0, 0, 0})), false), "Testing vector constructor with matrix ");

    Vector<3> VmatOp({1, 2, 3});
    Matrix<3, 1> VmatrixConversion;
    VmatOp = VmatrixConversion;
    VmatrixConversion = T1;
    printResult(compareStrings(mat_to_string(VmatrixConversion), "1 \n2 \n3 \n", false), "Testing vector constructor with matrix ");
}
void MatrixTesitng()
{

    float **idArr = new float *[4];
    for (int i = 0; i < 4; i++)
    {
        idArr[i] = new float[4]{0, 0, 0, 0};
        idArr[i][i] = 1;
    }

    Matrix<4, 4> Identity(idArr);
    printResult(compareStrings(mat_to_string(Identity),
                               "1 0 0 0 \n0 1 0 0 \n0 0 1 0 \n0 0 0 1 \n", false),
                "Testing Matrix<4,4> identity construction");

    // Construct a 4x4 with sequential values
    float **seqArr = new float *[4];
    for (int i = 0; i < 4; i++)
    {
        seqArr[i] = new float[4];
        for (int j = 0; j < 4; j++)
        {
            seqArr[i][j] = i * 4 + j + 1; // 1..16
        }
    }
    Matrix<4, 4> Sequential(seqArr);
    printResult(compareStrings(mat_to_string(Sequential),
                               "1 2 3 4 \n5 6 7 8 \n9 10 11 12 \n13 14 15 16 \n", false),
                "Testing Matrix<4,4> sequential construction");

    // Copy constructor
    Matrix<4, 4> CopySeq(Sequential);
    printResult(compareStrings(mat_to_string(CopySeq),
                               mat_to_string(Sequential), false),
                "Testing Matrix<4,4> copy constructor");

    // Assignment operator
    Matrix<4, 4> AssignSeq;
    AssignSeq = Sequential;
    printResult(compareStrings(mat_to_string(AssignSeq),
                               mat_to_string(Sequential), false),
                "Testing Matrix<4,4> assignment operator");

    // Scalar multiplication
    Matrix<4, 4> DoubleSeq = Sequential * 2.0f;
    printResult(compareStrings(mat_to_string(DoubleSeq),
                               "2 4 6 8 \n10 12 14 16 \n18 20 22 24 \n26 28 30 32 \n", false),
                "Testing Matrix<4,4> scalar multiplication");

    // Addition
    Matrix<4, 4> SumSeq = Sequential + Sequential;
    printResult(compareStrings(mat_to_string(SumSeq),
                               "2 4 6 8 \n10 12 14 16 \n18 20 22 24 \n26 28 30 32 \n", false),
                "Testing Matrix<4,4> addition");

    // Transpose
    Matrix<4, 4> TransSeq = ~Sequential;
    printResult(compareStrings(mat_to_string(TransSeq),
                               "1 5 9 13 \n2 6 10 14 \n3 7 11 15 \n4 8 12 16 \n", false),
                "Testing Matrix<4,4> transpose");

    // getM / getN
    printResult(Sequential.getM() == 4, "Testing Matrix<4,4> getM()");
    printResult(Sequential.getN() == 4, "Testing Matrix<4,4> getN()");

    // Determinant(identity should be 1)
    try
    {
        printResult(Identity.determinant() == 1.0f, "Testing Matrix<4,4> determinant of identity");

        // Determinant(sequential matrix — expected to be 0 since rows are linearly dependent)
        printResult(Sequential.determinant() == 0.0f, "Testing Matrix<4,4> determinant of sequential matrix");

        float **arr = new float *[5];
        arr[0] = new float[5]{1, 2, 3, 4, 5};
        arr[1] = new float[5]{0, 1, 4, 2, 3};
        arr[2] = new float[5]{2, 0, 1, 3, 4};
        arr[3] = new float[5]{3, 1, 0, 2, 1};
        arr[4] = new float[5]{4, 2, 1, 0, 3};

        Matrix<5, 5> M(arr);
        printResult(M.determinant() == -214, "Testing Matrix<5,5> determinant");

        float **arr2 = new float *[6];
        arr2[0] = new float[6]{1, 1, 1, 1, 1, 1};
        arr2[1] = new float[6]{1, 2, 3, 4, 5, 6};
        arr2[2] = new float[6]{1, 3, 6, 10, 15, 21};
        arr2[3] = new float[6]{1, 4, 10, 20, 35, 56};
        arr2[4] = new float[6]{1, 5, 15, 35, 70, 126};
        arr2[5] = new float[6]{1, 6, 21, 56, 126, 252};

        Matrix<6, 6> M2(arr2);
        printResult(M2.determinant() == 1, "Testing Matrix<6,6> determinant");
    }
    catch (char *e)
    {
        std::cout << e << std::endl;
    }
}
void TriangleTesting()
{
    // Base triangle in 2D
    Vector<3> p1({0.0f, 0.0f, 0.0f});
    Vector<3> p2({1.0f, 0.0f, 0.0f});
    Vector<3> p3({0.0f, 1.0f, 0.0f});

    Triangle tri(p1, p2, p3);
    printResult(compareStrings(tri_to_str(tri), "0\n0\n0\n1\n0\n0\n0\n1\n0\n", false),
                "Testing triangle base constructor");

    // Copy constructor
    Triangle triCopy(tri);
    printResult(compareStrings(tri_to_str(triCopy), "0\n0\n0\n1\n0\n0\n0\n1\n0\n", false),
                "Testing triangle copy constructor");

    printResult(tri.getNumPoints() == 9, "Testing getNumPoints (2D triangle)");

    float *pts = tri.getPoints();
    std::string expectedPts = "0\n0\n0\n1\n0\n0\n0\n1\n0\n";
    std::stringstream ss;
    for (int i = 0; i < tri.getNumPoints(); i++)
    {
        ss << pts[i] << "\n";
    }
    delete[] pts;
    printResult(compareStrings(ss.str(), expectedPts, false),
                "Testing getPoints linearisation");

    // Transformation matrix (identity)
    Matrix<3, 3> identity;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            identity[i][j] = (i == j ? 1.0f : 0.0f);
        }
    }

    tri *= identity;
    printResult(compareStrings(tri_to_str(tri), "0\n0\n0\n1\n0\n0\n0\n1\n0\n", false),
                "Testing operator*= with identity");


    tri *identity;
    std::cout << "we got here post tri * identity" << std::endl;

    Triangle *triNew = tri * identity;

    printResult(compareStrings(tri_to_str(*triNew), "0\n0\n0\n1\n0\n0\n0\n1\n0\n", false),
                "Testing operator* with identity");
    delete triNew;

    Matrix<3, 3> scale;
    scale[0][0] = 2.0f;
    scale[0][1] = 0.0f;
    scale[0][2] = 0.0f;
    scale[1][0] = 0.0f;
    scale[1][1] = 2.0f;
    scale[1][2] = 0.0f;
    scale[2][0] = 0.0f;
    scale[2][1] = 0.0f;
    scale[2][2] = 1.0f;

    tri *= scale;
    printResult(compareStrings(tri_to_str(tri), "0\n0\n0\n2\n0\n0\n0\n2\n0\n", false),
                "Testing operator*= with scale by 2");

    Triangle *triScaled = tri * scale;
    printResult(compareStrings(tri_to_str(*triScaled), "0\n0\n0\n4\n0\n0\n0\n4\n0\n", false),
                "Testing operator* with scale by 2");
    delete triScaled;
}
void SquareTesting()
{

    Vector<3> center({0, 0, 0});
    Square sq(center, 2, 2);

    std::string expectedBase = "-1\n1\n0\n1\n1\n0\n1\n-1\n0\n-1\n-1\n0\n";
    printResult(compareStrings(sqr_to_str(sq), expectedBase, false),
                "Testing square base constructor");

    Square sqCopy(sq);
    printResult(compareStrings(sqr_to_str(sqCopy), expectedBase, false),
                "Testing square copy constructor");

    printResult(sq.getNumPoints() == 12, "Testing getNumPoints (2D square)");

    float *pts = sq.getPoints();
    std::stringstream ss;
    for (int i = 0; i < sq.getNumPoints(); i++)
    {
        ss << pts[i] << "\n";
    }
    delete[] pts;
    printResult(compareStrings(ss.str(), expectedBase, false),
                "Testing getPoints linearisation");

    Matrix<3, 3> identity;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            identity[i][j] = (i == j ? 1.0f : 0.0f);
        }
    }

    sq *= identity;
    printResult(compareStrings(sqr_to_str(sq), expectedBase, false),
                "Testing operator*= with identity");

    Square *sqNew = sq * identity;
    printResult(compareStrings(sqr_to_str(*sqNew), expectedBase, false),
                "Testing operator* with identity");
    delete sqNew;

    Matrix<3, 3> scale;
    scale[0][0] = 2;
    scale[0][1] = 0;
    scale[0][2] = 0;
    scale[1][0] = 0;
    scale[1][1] = 2;
    scale[1][2] = 0;
    scale[2][0] = 0;
    scale[2][1] = 0;
    scale[2][2] = 1;

    sq *= scale;
    std::string expectedScaled = "-2\n2\n0\n2\n2\n0\n2\n-2\n0\n-2\n-2\n0\n";
    printResult(compareStrings(sqr_to_str(sq), expectedScaled, false),
                "Testing operator*= with scale by 2");

    Square *sqScaled = sq * scale;
    std::string expectedScaledTwice = "-4\n4\n0\n4\n4\n0\n4\n-4\n0\n-4\n-4\n0\n";
    printResult(compareStrings(sqr_to_str(*sqScaled), expectedScaledTwice, false),
                "Testing operator* with scale by 2");
    delete sqScaled;
}

bool compareStrings(const std::string &testStr, const std::string &memoStr, bool printResult)
{
    bool equal = (testStr == memoStr);
    if (printResult)
    {

        std::cout << "Comparison string:\n";

        for (size_t i = 0; i < testStr.size(); ++i)
        {
            if (i < memoStr.size() && testStr[i] == memoStr[i])
            {
                std::cout << GREEN << testStr[i] << RESET;
            }
            else
            {
                std::cout << RED << testStr[i] << RESET;
            }
        }
        if (!equal)
        {
            std::cout << GREEN << memoStr << RESET << std::endl;
            std::cout << RED << testStr << RESET << std::endl;
        }
        std::cout << std::endl;
    }
    return equal;
}

void printResult(bool condition, const std::string &passText)
{
    if (condition)
    {
        std::cout << GREEN << passText << RESET << std::endl;
    }
    else
    {
        std::cout << RED << passText << RESET << std::endl;
    }
}
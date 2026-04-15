#include "Square.h"

Square::Square(const Vector<3> &center, float height, float width) : Shape()
{
    float left = center[0] - width / 2;
    float right = center[0] + width / 2;
    float top = center[1] + height / 2;
    float bottom = center[1] - height / 2;

    float *tlArr = new float[this->n];
    float *trArr = new float[this->n];
    float *brArr = new float[this->n];
    float *blArr = new float[this->n];

    tlArr[0] = left;
    tlArr[1] = top;
    trArr[0] = right;
    trArr[1] = top;
    brArr[0] = right;
    brArr[1] = bottom;
    blArr[0] = left;
    blArr[1] = bottom;

    for (int i = 2; i < this->n; i++)
    {
        tlArr[i] = center[i];
        trArr[i] = center[i];
        brArr[i] = center[i];
        blArr[i] = center[i];
    }

    tl = Vector<3>(tlArr);
    tr = Vector<3>(trArr);
    br = Vector<3>(brArr);
    bl = Vector<3>(blArr);
}
Square::Square(const Vector<3> &center, float height, float width, Colour col) : Shape(col)
{
    float left = center[0] - width / 2;
    float right = center[0] + width / 2;
    float top = center[1] + height / 2;
    float bottom = center[1] - height / 2;

    float *tlArr = new float[this->n];
    float *trArr = new float[this->n];
    float *brArr = new float[this->n];
    float *blArr = new float[this->n];

    tlArr[0] = left;
    tlArr[1] = top;
    trArr[0] = right;
    trArr[1] = top;
    brArr[0] = right;
    brArr[1] = bottom;
    blArr[0] = left;
    blArr[1] = bottom;

    for (int i = 2; i < this->n; i++)
    {
        tlArr[i] = center[i];
        trArr[i] = center[i];
        brArr[i] = center[i];
        blArr[i] = center[i];
    }

    tl = Vector<3>(tlArr);
    tr = Vector<3>(trArr);
    br = Vector<3>(brArr);
    bl = Vector<3>(blArr);
}

Square::Square(const Vector<3> &tl, const Vector<3> &tr,
                  const Vector<3> &br, const Vector<3> &bl) : Shape()
{
    this->tl = tl;
    this->bl = bl;
    this->tr = tr;
    this->br = br;
}
Square::Square(const Vector<3> &tl, const Vector<3> &tr,
                  const Vector<3> &br, const Vector<3> &bl, Colour col) : Shape(col)
{
    this->tl = tl;
    this->bl = bl;
    this->tr = tr;
    this->br = br;
}

Square::Square(const Square &other)
{
    this->colour = other.colour;
    this->tl = other.tl;
    this->bl = other.bl;
    this->tr = other.tr;
    this->br = other.br;
}

Square &Square::operator*=(const Matrix<3, 3> &m)
{

    Matrix<3, 4> sqMat;
    for (int i = 0; i < this->n; i++)
    {
        sqMat[i][0] = tl[i];
        sqMat[i][1] = tr[i];
        sqMat[i][2] = br[i];
        sqMat[i][3] = bl[i];
    }

    Matrix<3, 4> result = m * sqMat;

    Vector<3> newTL, newTR, newBR, newBL;
    for (int i = 0; i < this->n; i++)
    {
        newTL[i] = result[i][0];
        newTR[i] = result[i][1];
        newBR[i] = result[i][2];
        newBL[i] = result[i][3];
    }

    tl = newTL;
    tr = newTR;
    br = newBR;
    bl = newBL;

    return *this;
}

Square *Square::operator*(const Matrix<3, 3> &m) const
{

    Matrix<3, 4> sqMat;
    for (int i = 0; i < this->n; i++)
    {
        sqMat[i][0] = tl[i];
        sqMat[i][1] = tr[i];
        sqMat[i][2] = br[i];
        sqMat[i][3] = bl[i];
    }

    Matrix<3, 4> result = m * sqMat;

    Vector<3> newTL, newTR, newBR, newBL;
    for (int i = 0; i < this->n; i++)
    {
        newTL[i] = result[i][0];
        newTR[i] = result[i][1];
        newBR[i] = result[i][2];
        newBL[i] = result[i][3];
    }

    Square *newSquare = new Square(newTL, newTR, newBR, newBL);
    newSquare->colour = this->colour;
    return newSquare;
}

float *Square::getPoints() const
{
    // Allocate array for 4 corners, each with n components
    float *arr = new float[this->n * 4];

    for (int i = 0; i < this->n; i++)
    {
        arr[i] = tl[i];         // top-left
        arr[i + this->n] = tr[i];     // top-right
        arr[i + 2 * this->n] = br[i]; // bottom-right
        arr[i + 3 * this->n] = bl[i]; // bottom-left
    }

    return arr;
}

int Square::getNumPoints() const
{
    // 4 vertices, each with n components
    return this->n * 4;
}
std::vector<Vector<3>> Square::getVectors()
{
    std::vector<Vector<3>> retVec;
    retVec.push_back(tl);
    retVec.push_back(tr);
    retVec.push_back(bl);
    retVec.push_back(br);
    return retVec;
}
Vector<3> Square::getCenter()
{
    Vector<3> center;
    for (int i = 0; i < this->n; i++)
    {
        float sum = 0;

        sum += tl[i];
        sum += tr[i];
        sum += br[i];
        sum += bl[i];

        center[i] = sum / 4;
    }
    return center;
}
void Square::setVectors(std::vector<Vector<3>> vec)
{
    tl = vec[0];
    tr = vec[1];
    bl = vec[2];
    br = vec[3];
}
#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"
#include "Matrix.h"
#include "Vector.h"

class Square : public Shape
{
private:
public:
    Vector<3> tl;
    Vector<3> tr;
    Vector<3> br;
    Vector<3> bl;

    Square(Colour col = Colour::White);
    Square(const Vector<3> &center, float height, float width);
    Square(const Vector<3> &tl, const Vector<3> &tr, const Vector<3> &br, const Vector<3> &bl);
    Square(const Vector<3> &center, float height, float width, Colour col);
    Square(const Vector<3> &tl, const Vector<3> &tr, const Vector<3> &br, const Vector<3> &bl, Colour col);
    Square(const Square &);
    virtual int getNumSides() const { return 4; }
    virtual Square &operator*=(const Matrix<3, 3> &);
    virtual Square *operator*(const Matrix<3, 3> &) const;
    virtual float *getPoints() const;
    virtual int getNumPoints() const;
    virtual Vector<3> getCenter();
    virtual ~Square() {}
    std::vector<Vector<3>> getVectors();
    virtual void setVectors(std::vector<Vector<3>>);
    Square operator=(const Square &other)
    {
        if (this != &other)
        {
            this->tl = other.tl;
            this->tr = other.tr;
            this->br = other.br;
            this->bl = other.bl;
            this->setSurface(other.getSurface());
        }
        return *this;
    }

    virtual void print() const
    {
        std::cout << "_ P1 _ " << std::endl;
        tl.print();
        std::cout << "_ P2 _ " << std::endl;
        tr.print();
        std::cout << "_ P3 _ " << std::endl;
        br.print();
        std::cout << "_ P4 _ " << std::endl;
        bl.print();
    }
};
inline std::string sqr_to_str(Square sqr)
{
    std::stringstream str;
    float *arr = sqr.getPoints();
    for (int i = 0; i < sqr.getNumPoints(); i++)
    {
        str << arr[i] << "\n";
    }

    delete[] arr;
    return str.str();
}
inline Square::Square(Colour col ) : Shape(col) {

}

#endif /*SQUARE_H*/

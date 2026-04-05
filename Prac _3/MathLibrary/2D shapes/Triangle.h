#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include "Vector.h"
#include <vector>
class Triangle : public Shape
{
private:
public:
    Vector<3> p1;
    Vector<3> p2;
    Vector<3> p3;

    Triangle() : Shape(Colour::White) {}

    Triangle(const Vector<3> &p1, const Vector<3> &p2, const Vector<3> &p3, Colour col);
    Triangle(const Triangle &, Colour col);

    Triangle(const Vector<3> &p1, const Vector<3> &p2, const Vector<3> &p3);

    Triangle(const Vector<3> &center, float sideLength, Colour col);

    Triangle(const Triangle &);
    virtual int getNumSides() const { return 3; }
    virtual Triangle &operator*=(const Matrix<3, 3> &);
    virtual Triangle *operator*(const Matrix<3, 3> &) const;
    virtual float *getPoints() const;
    virtual int getNumPoints() const;
    virtual ~Triangle() {}
    virtual Vector<3> getCenter();
    std::vector<Vector<3>> getVectors();
    virtual void setVectors(std::vector<Vector<3>>);
    virtual void print() const
    {
        std::cout << "_ P1 _ " << std::endl;
        p1.print();
        std::cout << "_ P2 _ " << std::endl;
        p2.print();
        std::cout << "_ P3 _ " << std::endl;
        p3.print();
    }

    Triangle &operator=(const Triangle &other)
    {
        if (this != &other)
        {
            this->p1 = other.p1;
            this->p2 = other.p2;
            this->p3 = other.p3;
            this->colour = other.colour;
        }
        return *this;
    }
};
inline std::string tri_to_str(Triangle tri)
{
    std::stringstream str;
    float *arr = tri.getPoints();
    for (int i = 0; i < tri.getNumPoints(); i++)
    {
        str << arr[i] << "\n";
    }
    delete[] arr;
    return str.str();
}

#endif /*TRIANGLE_H*/

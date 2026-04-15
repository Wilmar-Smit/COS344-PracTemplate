#ifndef CAMERA_H
#define CAMERA_H

#include "../MathLibrary/Matrix.h"

class Camera
{
private:
    Vector<3> e, w, v, u;

    Matrix<4, 4> Mcam;
    Matrix<4, 4> Mper;
    Matrix<4, 4> Mtotal;

    const float near = 1;
    const float far = 10.0f;
    const float left = -1.0f;
    const float right = 1.0f;
    const float top = 1.0f;
    const float bottom =-1.0f;

    Camera(Vector<3> e, Vector<3> top, Vector<3> gaze);

    void constructMcam();
    void constructMper();
    void constructTotalM();

    Camera(const Camera &) = delete;
    Camera &operator=(const Camera &) = delete;

public:
    static Camera &getInstance(Vector<3> e = {0, 0, 0}, Vector<3> top = {0, 0, 0}, Vector<3> gaze = {0, 0, 0});

    const Matrix<4, 4> &
    getMcam() const
    {
        return Mcam;
    }
    const Matrix<4, 4> &getMper() const
    {
        return Mper;
    }

    const Matrix<4, 4> &getMatrix() const
    {
        return Mtotal;
    }
};

#endif

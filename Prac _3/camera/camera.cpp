#include "camera.h"

Camera::Camera(Vector<3> e, Vector<3> top, Vector<3> gaze)
{
    this->e = e;
    w = (gaze * -1).unitVector(); // w points opposite to gaze direction only

    u = (top.crossProduct(w)).unitVector();

    this->v = w.crossProduct(u);

    constructMcam();
    constructMper();
    constructTotalM();
}

void Camera::constructMcam()
{
    int n = 3;                    
    Matrix<4, 4> xyzMat, multMat; 

    for (int i = 0; i < n; i++)
    {
        xyzMat[0][i] = u[i];
    }

    for (int i = 0; i < n; i++)
    {
        xyzMat[1][i] = v[i];
    }
    for (int i = 0; i < n; i++)
    {
        xyzMat[2][i] = w[i];
    }
    xyzMat[3][3] = 1;

    multMat[0][0] = 1;
    multMat[1][1] = 1;
    multMat[2][2] = 1;
    for (int i = 0; i < n; i++)
    {
        multMat[i][3] = -e[i];
    }
    multMat[3][3] = 1;

    Mcam = xyzMat * multMat;
}

void Camera::constructMper()
{
    Matrix<4, 4> Mp;

    Mp[0][0] = (2.0f * near) / (right - left);
    Mp[0][2] = (right + left) / (right - left);

    Mp[1][1] = (2.0f * near) / (top - bottom);
    Mp[1][2] = (top + bottom) / (top - bottom);

    Mp[2][2] = -(far + near) / (far - near);
    Mp[2][3] = -(2.0f * far * near) / (far - near);

    Mp[3][2] = -1.0f;

    this->Mper = Mp;
}

void Camera::constructTotalM()
{
    this->Mtotal = Mper * Mcam;
}

Camera &Camera::getInstance(Vector<3> e, Vector<3> top, Vector<3> gaze)
{
    static Camera instance(e, top, gaze);
    return instance;
}

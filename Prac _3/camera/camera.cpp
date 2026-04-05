#include "camera.h"

Camera::Camera(Vector<3> e, Vector<3> top, Vector<3> gaze)
{
	this->e = e;
	w = (e + (gaze * -1)).unitVector();

	u = (top.crossProduct(w)).unitVector();

	this->v = w.crossProduct(u);
	constructMcam();
	constructMper();
	constructTotalM();
}

void Camera::constructMcam()
{
	int n = 3;                    // dimensions of the vecs
	Matrix<4, 4> xyzMat, multMat; // 4th coord already 0

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
		xyzMat[1][i] = w[i];
	}

	for (int i = 0; i < n; i++)
	{

		multMat[i][3] = -e[i]; // negative eye
	}
	multMat[3][3] = 1;

	Mcam = xyzMat * multMat;
}

void Camera::constructMper()
{
	Matrix<4, 4> Morth, Mp;

	Morth[0][0] = 2 / (this->right - this->left);
	Morth[1][1] = 2 / (this->top - this->bottom);
	Morth[2][2] = 2 / (this->near - this->far);
	Morth[3][3] = 1;

	Morth[0][3] = -1 * (right + left) / (right - left);
	Morth[1][3] = -1 * (top + bottom) / (top - bottom);
	Morth[2][3] = -1 * (near + far) / (near - far);

	Mp[0][0] = near;
	Mp[1][1] = near;
	Mp[2][2] = near + far;
	Mp[2][3] = -1 * (far * near);
	Mp[3][2] = 1;
	this->Mper = Morth * Mp;
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

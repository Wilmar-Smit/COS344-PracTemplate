#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.hpp"
#include "2D shapes/Triangle.h"
#include "Vector.h"
#include "Matrix.h"
#include "2D shapes/Square.h"
#include "sceneClasses/drawer.h"
#include "sceneClasses/SceneHolder.h"
#include "2D shapes/circle.h"
#include "3D shapes/Cylinder.h"
#include "3D shapes/SquarePyramid.h"
#include "sceneClasses/drawerVisitor.h"
#include "3D shapes/Sphere.h"
#include "3D shapes/Cuboid.h"
#include "borderClasses/borderShape.h"
void VectorTesting();
void MatrixTesitng();
void TriangleTesting();
void SquareTesting();

void libraryTesting()
{
	VectorTesting();
	std::cout << std::endl;
	MatrixTesitng();
	std::cout << std::endl;
	TriangleTesting();
	std::cout << std::endl;
	SquareTesting();
}

int main()
{
#ifdef COVERAGE_RUN
	libraryTesting();
	return 0;
#endif

	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const char *baseWindowTitle = "u24584216";
	const int windowWidth = 1200;
	const int windowHeight = 800;
	GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, baseWindowTitle, NULL, NULL);

	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowAspectRatio(window, windowWidth, windowHeight);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	int nx, ny;
	glfwGetFramebufferSize(window, &nx, &ny);
	glViewport(0, 0, nx, ny);

	glClearColor(0.18f, 0.45f, 0.45f, 1.0f);
	GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	Sphere<3> *sph = new Sphere<3>({0, 0, 0}, 0.5, 10, 10, Colour::Red);
	Square<3> cubeBase({0, 0, 0}, 1.0f, 1.0f, Colour::Blue);
	Cuboid<3> *cube = new Cuboid<3>(cubeBase, 1.0f, Colour::Blue);

	BorderShape sphereBorder(sph);
	BorderShape cubeBorder(cube);
	Vector<3> *collisionPoint = sphereBorder.Collision(&cubeBorder);
	if (collisionPoint)
	{
		std::cout << "collision detected" << std::endl;
		delete collisionPoint;
	}
	else
	{
		std::cout << "no collision" << std::endl;
	}

	DrawerVisitor<3> *sphereVis = new DrawerVisitor<3>(sph);
	DrawerVisitor<3> *cubeVis = new DrawerVisitor<3>(cube);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		sphereVis->draw();
		cubeVis->draw();

		sphereVis->RotateX(0.5);
		sphereVis->RotateY(0.3);
		sphereVis->RotateZ(0.3);

		cubeVis->RotateX(0.2);
		cubeVis->RotateY(0.2);
		// Check for Enter key press
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			sphereVis->setWireframeMode();
			cubeVis->setWireframeMode();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 !glfwWindowShouldClose(window));

	delete sphereVis;
	delete cubeVis;
	glfwTerminate();

	return 0;
}

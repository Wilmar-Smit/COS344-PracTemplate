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

#include "2D shapes/circle.h"
#include "3D_shapes/Cylinder.h"
#include "3D_shapes/SquarePyramid.h"
#include "sceneClasses/drawerVisitor.h"
#include "3D_shapes/Sphere.h"
#include "3D_shapes/Cuboid.h"
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

	glClearColor(1, 1, 1, 1.0f);
	GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	Square<3> cubeBaseA({0.0f, 0.0f, 0.0f}, 0.50f, 0.50f, Colour::Blue);
	Cuboid *cubeA = new Cuboid(cubeBaseA, 0.15f, Colour::Blue);
	Sphere *sph = new Sphere({0.4f, 0.0f, 0.0f}, 0.08f, 10, 3, Colour::Red);

	BorderShape cubeABorder(cubeA);
	BorderShape sphereBorder(sph);

	DrawerVisitor *cubeAVis = new DrawerVisitor(cubeA);
	DrawerVisitor *sphereVis = new DrawerVisitor(sph);

	do
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		cubeAVis->draw();
		sphereVis->draw();

		cubeAVis->RotateZ(0.5);

		Vector<3> *collisionPoint = cubeABorder.Collision(&sphereBorder);
		if (collisionPoint)
		{
			std::cout << "collision detected" << std::endl;

			Sphere *collisionDot = new Sphere(*collisionPoint, 0.01f, 8, 3, Colour::Black);
			DrawerVisitor *collisionDotVis = new DrawerVisitor(collisionDot);
			collisionDotVis->draw();
			delete collisionDotVis;
		}
		else if (!collisionPoint)
		{
			std::cout << "no collision" << std::endl;
		}

		if (collisionPoint)
		{
			delete collisionPoint;
			collisionPoint = nullptr;
		}

		// Check for Enter key press
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			cubeAVis->setWireframeMode();
			sphereVis->setWireframeMode();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();


	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 !glfwWindowShouldClose(window));

	delete cubeAVis;
	delete sphereVis;
	glfwTerminate();

	return 0;
}

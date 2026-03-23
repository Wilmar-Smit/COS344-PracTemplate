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
	GLFWwindow *window = glfwCreateWindow(1200, 800, baseWindowTitle, NULL, NULL);

	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

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

	Circle<3> baseCircle(Vector<3>({-0.18f, -0.10f, -0.25f}), 0.35f, 24, Colour::Red);
	Cylinder<3> *cylinder = new Cylinder<3>(baseCircle, 0.6f, Colour::Red);
	DrawerVisitor<3> *test = new DrawerVisitor<3>(cylinder);

	Square<3> pyramidBase(Vector<3>({0.55f, 0.0f, -0.35f}), 0.35f, 0.35f, Colour::Blue);
	SquarePyramid<3> *pyramid = new SquarePyramid<3>(pyramidBase, 0.45f, Colour::Blue);
	DrawerVisitor<3> *test2 = new DrawerVisitor<3>(pyramid);

	

	glEnable(GL_DEPTH_TEST);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		test->draw();
		test2->draw();
		test->RotateX(0.5);
		test->RotateY(0.5);
		test2->RotateY(-0.35);
		// Check for Enter key press
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			test->setWireframeMode();
			test2->setWireframeMode();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 !glfwWindowShouldClose(window));

	return 0;
}

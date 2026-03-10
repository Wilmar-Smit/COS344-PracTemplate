#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.hpp"
#include "Triangle.h"
#include "Vector.h"
#include "Matrix.h"
#include "Square.h"
#include "drawer.h"
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

	GLFWwindow *window = glfwCreateWindow(1000, 1000, "OpenGL 3.3 Window", NULL, NULL);
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
	GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");
	libraryTesting();
	

	// Border around floor
	const float floorSize = 1.6f;
	const float halfFloorSize = floorSize / 2.0f;
	const float borderThickness = 0.05f;

	// Grass background
	Square<2> grass(Vector<2>{0.0f}, floorSize - borderThickness, floorSize - borderThickness);
	GolfShape grassShape(&grass, Colour::Green);
	Drawer grassDrawer(&grassShape, 2, 4, GL_TRIANGLE_FAN);

	Square<2> topBorder(Vector<2>{0.0f, halfFloorSize}, borderThickness, floorSize);
	GolfShape topBorderShape(&topBorder, Colour::Grey);
	Drawer topBorderDrawer(&topBorderShape, 2, 4, GL_TRIANGLE_FAN);

	Square<2> bottomBorder(Vector<2>{0.0f, -halfFloorSize}, borderThickness, floorSize);
	GolfShape bottomBorderShape(&bottomBorder, Colour::Grey);
	Drawer bottomBorderDrawer(&bottomBorderShape, 2, 4, GL_TRIANGLE_FAN);

	Square<2> leftBorder(Vector<2>{-halfFloorSize, 0.0f}, floorSize + borderThickness, borderThickness);
	GolfShape leftBorderShape(&leftBorder, Colour::Grey);
	Drawer leftBorderDrawer(&leftBorderShape, 2, 4, GL_TRIANGLE_FAN);

	Square<2> rightBorder(Vector<2>{halfFloorSize, 0.0f}, floorSize + borderThickness, borderThickness);
	GolfShape rightBorderShape(&rightBorder, Colour::Grey);
	Drawer rightBorderDrawer(&rightBorderShape, 2, 4, GL_TRIANGLE_FAN);

	Square<2> riverSqr(Vector<2>{0, 0.0f}, 0.3f, 1);
	GolfShape riverGF(&riverSqr, Colour::Blue);
	Drawer RiverDrawer(&riverGF, 2, 4, GL_TRIANGLE_FAN);

	Square<2> orginDot(Vector<2>{0, 0.0f}, 0.01f, 0.01);
	GolfShape originGF(&orginDot, Colour::DarkBrown);
	Drawer DotDwr(&originGF, 2, 4, GL_TRIANGLE_FAN);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);
		grassDrawer.draw();
		topBorderDrawer.draw();
		bottomBorderDrawer.draw();
		leftBorderDrawer.draw();
		rightBorderDrawer.draw();
		RiverDrawer.draw();
		DotDwr.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 !glfwWindowShouldClose(window));

	return 0;
}

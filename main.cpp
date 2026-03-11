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
#include "sceneClasses/drawer.h"
#include "sceneClasses/SceneHolder.h"

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

Scene<2> *BorderScene()
{
	// Borders and axes
	const float floorSize = 1.6f;
	const float halfFloorSize = floorSize / 2.0f;
	const float borderThickness = 0.05f;

	SceneHolder<2> *scene = new SceneHolder<2>();
	SceneHolder<2> *borders = new SceneHolder<2>();
	SceneHolder<2> *axes = new SceneHolder<2>();

	borders->addScene(new Drawer<2>(
		new Square<2>(Vector<2>{0.0f, halfFloorSize}, borderThickness, floorSize, Colour::Grey),

		GL_TRIANGLE_FAN));
	borders->addScene(new Drawer<2>(
		new Square<2>(Vector<2>{0.0f, -halfFloorSize}, borderThickness, floorSize, Colour::Grey),

		GL_TRIANGLE_FAN));
	borders->addScene(new Drawer<2>(
		new Square<2>(Vector<2>{-halfFloorSize, 0.0f}, floorSize + borderThickness, borderThickness, Colour::Grey),

		GL_TRIANGLE_FAN));
	borders->addScene(new Drawer<2>(
		new Square<2>(Vector<2>{halfFloorSize, 0.0f}, floorSize + borderThickness, borderThickness, Colour::Grey),

		GL_TRIANGLE_FAN));

	scene->addScene(borders);
	axes->addScene(new Drawer<2>(new Square<2>(Vector<2>{0, 0.0f}, 0.005f, 20, Colour::Black), GL_TRIANGLE_FAN));
	axes->addScene(new Drawer<2>(new Square<2>(Vector<2>{0, 0.0f}, 20, 0.005f, Colour::Black), GL_TRIANGLE_FAN));
	scene->addScene(axes);
	return scene;
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");
	Scene<2> *borders = BorderScene();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);

		borders->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 !glfwWindowShouldClose(window));

	delete borders;
	return 0;
}

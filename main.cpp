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

	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL 3.3 Window", NULL, NULL);
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

	// VBO
	GLuint triangleVBO[1];
	Triangle<2> *try1 = new Triangle(Vector<2>({1, 2}), Vector<2>({4, 5}), Vector<2>({7, 8}));
	glGenBuffers(1, triangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, try1->getNumPoints() * sizeof(GLfloat), try1->getPoints(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// VBO

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 !glfwWindowShouldClose(window));

	delete try1;
	return 0;
}

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
#include "circle.h"
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
	// Border + concrete floor
	const float borderSize = 2.0f;
	const float floorSize = 1.9f;

	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0, 0.0f}, borderSize, borderSize, Colour::Black), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0, 0.0f}, floorSize, floorSize, Colour::Grey), GL_TRIANGLE_FAN));

	return scene;
}

Scene<2> *AxisScene()
{
	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0, 0.0f}, 0.005f, 2.0f, Colour::Black), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0, 0.0f}, 2.0f, 0.005f, Colour::Black), GL_TRIANGLE_FAN));
	return scene;
}
Scene<2> *GolfBall()
{
	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Circle<2>(Vector<2>({0.5, -0.5}), 0.03, 9, Colour::Pink), GL_TRIANGLE_FAN));
	return scene;
}

Scene<2> *RiverScene()
{
	float riverWidth = 0.3;
	float riverlength = 1.6f;
	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>({0, 0}), riverlength, riverWidth, Colour::Blue), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>({0, 0.5}), 0.2, 0.35, Colour::DarkBrown), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>({0, -0.5}), 0.2, 0.35, Colour::DarkBrown), GL_TRIANGLE_FAN));
	return scene;
}
Scene<2> *GrassScene()
{
	float grassWidth = 1.6;
	float grassheight = 1.6f;
	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>({0, 0}), grassWidth, grassheight, Colour::Green), GL_TRIANGLE_FAN));
	return scene;
}
Scene<2> *ObsticleScene()
{
	float widthSm = 0.1f;
	float widthLg = 0.25f;

	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Triangle<2>(Vector<2>({-0.75, -0.7}), widthSm, Colour::Cyan), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Triangle<2>(Vector<2>({-0.65, 0.6}), widthSm, Colour::Cyan), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Triangle<2>(Vector<2>({-0.25, 0.0}), widthSm, Colour::Cyan), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Triangle<2>(Vector<2>({0.65, 0.2}), widthLg, Colour::Red), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Triangle<2>(Vector<2>({0.65, -0.2}), widthLg, Colour::Red), GL_TRIANGLE_FAN));

	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>({-0.7, 0}), 0.5, 0.05, Colour::Brown), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>({0.3, 0}), 0.05, 1, Colour::Brown), GL_TRIANGLE_FAN));
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

	const char *baseWindowTitle = "OpenGL 3.3 Window";
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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");

	Scene<2> *borders = BorderScene();
	Scene<2> *river = RiverScene();
	Scene<2> *grass = GrassScene();

	Scene<2> *obs = ObsticleScene();
	Scene<2> *golfBall = GolfBall();
	Scene<2> *axes = AxisScene();
	bool eWasDown = false;
	bool qWasDown = false;
	bool plusWasDown = false;
	bool minusWasDown = false;
	bool wWasDown = false;
	bool aWasDown = false;
	bool sWasDown = false;
	bool dWasDown = false;
	bool spaceWasDown = false;
	double fpsTimerStart = glfwGetTime();
	int fpsFrameCount = 0;

	do
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(programID);

		bool eIsDown = (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS);
		if (eIsDown && !eWasDown)
		{
			obs->Rotate(+60.0f);
		}
		eWasDown = eIsDown;

		bool qIsDown = (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
		if (qIsDown && !qWasDown)
		{
			obs->Rotate(-60.0f);
		}
		qWasDown = qIsDown;

		bool plusIsDown = (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS);
		if (plusIsDown && !plusWasDown)
		{
			obs->Scale(1.5);
		}
		plusWasDown = plusIsDown;

		bool minusIsDown = (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS);
		if (minusIsDown && !minusWasDown)
		{
			obs->Scale((2.0f / 3));
		}
		minusWasDown = minusIsDown;

		// 1. WASD Input Detection
		bool wDown = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
		bool aDown = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
		bool sDown = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
		bool dDown = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);

		float moveStep = 0.1f; // Adjust this for speed

		// 2. Trigger Movement on "Press"
		if (wDown && !wWasDown)
			obs->Translation(Direction::up, moveStep);
		if (aDown && !aWasDown)
			obs->Translation(Direction::left, moveStep);
		if (sDown && !sWasDown)
			obs->Translation(Direction::down, moveStep);
		if (dDown && !dWasDown)
			obs->Translation(Direction::right, moveStep);

		// 3. Update States for next frame
		wWasDown = wDown;
		aWasDown = aDown;
		sWasDown = sDown;
		dWasDown = dDown;

		borders->draw();
		grass->draw();
		river->draw();
		obs->draw();
		axes->draw();
		golfBall->draw();

		bool spaceDown = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		if (spaceDown && !spaceWasDown)
			golfBall->select();

		spaceWasDown = spaceDown;

		fpsFrameCount++;
		double now = glfwGetTime();
		double elapsed = now - fpsTimerStart;
		if (elapsed >= 1.0)
		{
			double fps = static_cast<double>(fpsFrameCount) / elapsed;

			std::cout << "FPS: " << fps << std::endl;

			fpsFrameCount = 0;
			fpsTimerStart = now;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 !glfwWindowShouldClose(window));

	delete borders;
	delete river;
	delete axes;
	delete grass;
	delete obs;
	delete golfBall;
	return 0;
}

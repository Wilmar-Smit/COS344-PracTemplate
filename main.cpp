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
	float borderWidth = 0.125;
	float borderlength = 1.6;

	float x = 0.8625;

	SceneHolder<2> *scene = new SceneHolder<2>();

	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{x, 0.0f}, borderlength, borderWidth, Colour::Grey), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{-x, 0.0f}, borderlength, borderWidth, Colour::Grey), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0.0f, -x}, borderWidth, borderlength + 2 * borderWidth, Colour::Grey), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0.0f, x}, borderWidth, borderlength + 2 * borderWidth, Colour::Grey), GL_TRIANGLE_FAN));

	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0.83, 0.0f}, borderlength, borderWidth / 2, Colour::DarkBrown), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{-0.83, 0.0f}, borderlength, borderWidth / 2 + 0.005, Colour::DarkBrown), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0.0f, -0.83}, borderWidth / 2, (borderlength + borderWidth), Colour::DarkBrown), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0.0f, 0.83}, borderWidth / 2, (borderlength + borderWidth), Colour::DarkBrown), GL_TRIANGLE_FAN));
	return scene;
}
Scene<2> *backgroundScene()
{

	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0.0, 0.0f}, 2.2, 2.2, Colour::Cyan), GL_TRIANGLE_FAN));
	return scene;
}

Scene<2> *AxisScene()
{
	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0, 0.0f}, 0.005f, 2.0f, Colour::Black), GL_TRIANGLE_FAN));
	scene->addScene(new Drawer<2>(new Square<2>(Vector<2>{0, 0.0f}, 2.0f, 0.005f, Colour::Black), GL_TRIANGLE_FAN));
	return scene;
}
Scene<2> *GolfHole()
{
	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Circle<2>(Vector<2>({0.7, 0.1}), 0.03, 9, Colour::Pink), GL_TRIANGLE_FAN));
	return scene;
}

Scene<2> *GolfBall()
{
	SceneHolder<2> *scene = new SceneHolder<2>();
	scene->addScene(new Drawer<2>(new Circle<2>(Vector<2>({0.5, -0.5}), 0.015, 100, Colour::White), GL_TRIANGLE_FAN));
	return scene;
}

Scene<2> *RiverScene()
{
	float riverWidth = 0.3;
	float riverlength = 2.26;
	SceneHolder<2> *scene = new SceneHolder<2>();
	Drawer<2> *river = new Drawer<2>(new Square<2>(Vector<2>({0, 0}), riverlength, riverWidth, Colour::Blue), GL_TRIANGLE_FAN);
	river->Rotate(-45);
	scene->addScene(river);

	Drawer<2> *rock = new Drawer<2>(new Square<2>(Vector<2>({-0.105, 0.105}), 2, 0.01, Colour::Grey), GL_TRIANGLE_FAN);
	rock->Rotate(-45);
	scene->addScene(rock);

	rock = new Drawer<2>(new Square<2>(Vector<2>({0.105, -0.105}), 2, 0.01, Colour::Grey), GL_TRIANGLE_FAN);
	rock->Rotate(-45);
	scene->addScene(rock);

	Drawer<2> *bridge = new Drawer<2>(new Square<2>(Vector<2>({0.4, 0.4}), 0.1, 0.4, Colour::DarkBrown), GL_TRIANGLE_FAN);
	bridge->Rotate(135);
	scene->addScene(bridge);

	bridge = new Drawer<2>(new Square<2>(Vector<2>({-0.3, -0.3}), 0.2, 0.4, Colour::DarkBrown), GL_TRIANGLE_FAN);
	bridge->Rotate(135);
	scene->addScene(bridge);

	bridge = new Drawer<2>(new Square<2>(Vector<2>({0.1, 0.1}), 0.05, 0.5, Colour::DarkBrown), GL_TRIANGLE_FAN);
	bridge->Rotate(100);
	scene->addScene(bridge);

	bridge = new Drawer<2>(new Square<2>(Vector<2>({0.6, -0.4}), 0.1, 0.25, Colour::Magenta), GL_TRIANGLE_FAN);
	bridge->Rotate(135);
	scene->addScene(bridge);

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

	float positionx = -0.3;
	float positiony = 0.6;

	SceneHolder<2> *scene = new SceneHolder<2>();
	// Triangles
	Scene<2> *object;

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			object = new Drawer<2>(new Triangle<2>(Vector<2>({positionx, positiony}), widthSm, Colour::Yellow), GL_TRIANGLE_FAN);
			object->Rotate(-45);
			scene->addScene(object);
			positionx -= 0.3;
		}
		positiony -= 0.2;
		positionx = -0.1;
	}

	object = new Drawer<2>(new Triangle<2>(Vector<2>({0.5, 0.080}), widthLg, Colour::Red), GL_TRIANGLE_FAN);
	object->Rotate(0);
	scene->addScene(object);
	object = new Drawer<2>(new Triangle<2>(Vector<2>({0.72, 0.3}), widthLg, Colour::Red), GL_TRIANGLE_FAN);
	object->Rotate(30);
	scene->addScene(object);
	// triangles
	Drawer<2> *bridge = new Drawer<2>(new Square<2>(Vector<2>({0.55, -0.2}), 0.05, 0.8, Colour::Brown), GL_TRIANGLE_FAN);
	bridge->Rotate(135);
	scene->addScene(bridge);

	object = new Drawer<2>(new Square<2>(Vector<2>({-0.75, 0.75}), 0.05, 0.2, Colour::Brown), GL_TRIANGLE_FAN);
	object->Rotate(45);
	scene->addScene(object);

	object = new Drawer<2>(new Square<2>(Vector<2>({0.7, 0.7}), 0.05, 0.4, Colour::Brown), GL_TRIANGLE_FAN);
	object->Rotate(135);
	scene->addScene(object);

	object = new Drawer<2>(new Square<2>(Vector<2>({-0.7, -0.7}), 0.05, 0.4, Colour::Brown), GL_TRIANGLE_FAN);
	object->Rotate(135);
	scene->addScene(object);
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

	glClearColor(0.18f, 0.45f, 0.45f, 1.0f);
	GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");
	Scene<2> *river = RiverScene();
	Scene<2> *borders = BorderScene();

	Scene<2> *grass = GrassScene();
	grass->addScene(river);
	Scene<2> *background = backgroundScene();

	Scene<2> *obs = ObsticleScene();
	Scene<2> *golfhole = GolfHole();
	Scene<2> *axes = AxisScene();
	Scene<2> *golfBall = GolfBall();
	bool eWasDown = false;
	bool qWasDown = false;
	bool plusWasDown = false;
	bool minusWasDown = false;
	bool wWasDown = false;
	bool aWasDown = false;
	bool sWasDown = false;
	bool dWasDown = false;
	bool spaceWasDown = false;
	bool oWasDown = false;

	bool key1WasDown = false;
	bool key2WasDown = false;
	bool key3WasDown = false;
	bool key4WasDown = false;
	double fpsTimerStart = glfwGetTime();
	int fpsFrameCount = 0;
	Scene<2> *selectedScene = nullptr;

	do
	{

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(programID);

		bool key1IsDown = (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS);
		if (key1IsDown && !key1WasDown)
		{
			if (selectedScene)
				selectedScene->deselect();
			obs->deselect();
			selectedScene = nullptr;
			golfhole->select();
			selectedScene = golfhole;
		}
		key1WasDown = key1IsDown;

		bool key2IsDown = (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS);
		if (key2IsDown && !key2WasDown)
		{
			if (selectedScene)
				selectedScene->deselect();
			obs->deselect();
			selectedScene = nullptr;
			obs->getIndex(2)->select();
			selectedScene = obs->getIndex(2);
		}
		key2WasDown = key2IsDown;

		bool key3IsDown = (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS);
		if (key3IsDown && !key3WasDown)
		{
			if (selectedScene)
				selectedScene->deselect();
			obs->deselect();
			selectedScene = nullptr;
			obs->getIndex(4)->select();
			selectedScene = obs->getIndex(4);
		}
		key3WasDown = key3IsDown;

		bool key4IsDown = (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS);
		if (key4IsDown && !key4WasDown)
		{
			if (selectedScene)
				selectedScene->deselect();
			obs->deselect();
			selectedScene = nullptr;
			golfBall->select();
			selectedScene = golfBall;
		}
		key4WasDown = key4IsDown;

		bool spaceDown = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		if (spaceDown && !spaceWasDown)
			selectedScene = obs->selectNext();

		bool oDown = glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
		if (oDown && !oWasDown)
		{
			if (selectedScene )
				selectedScene->deselect();
			obs->deselect();
			selectedScene = nullptr;
		}
		oWasDown = oDown;

		bool eIsDown = (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS);
		if (eIsDown && !eWasDown && selectedScene != nullptr)
		{
			selectedScene->Rotate(+60.0f);
		}
		eWasDown = eIsDown;

		bool qIsDown = (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
		if (qIsDown && !qWasDown && selectedScene != nullptr)
		{
			selectedScene->Rotate(-60.0f);
		}
		qWasDown = qIsDown;

		bool plusIsDown = (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS);
		if (plusIsDown && !plusWasDown && selectedScene != nullptr)
		{
			selectedScene->Scale(1.5);
		}
		plusWasDown = plusIsDown;

		bool minusIsDown = (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS);
		if (minusIsDown && !minusWasDown && selectedScene != nullptr)
		{
			selectedScene->Scale((2.0f / 3));
		}
		minusWasDown = minusIsDown;

		// 1. WASD Input Detection
		bool wDown = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
		bool aDown = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
		bool sDown = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
		bool dDown = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);

		float moveStep = 0.1f; // Adjust this for speed

		// 2. Trigger Movement on "Press"
		if (selectedScene != nullptr)
		{
			if (wDown && !wWasDown)
				selectedScene->Translation(Direction::up, moveStep);
			if (aDown && !aWasDown)
				selectedScene->Translation(Direction::left, moveStep);
			if (sDown && !sWasDown)
				selectedScene->Translation(Direction::down, moveStep);
			if (dDown && !dWasDown)
				selectedScene->Translation(Direction::right, moveStep);
		}

		// 3. Update States for next frame
		wWasDown = wDown;
		aWasDown = aDown;
		sWasDown = sDown;
		dWasDown = dDown;
		background->draw();
		grass->draw();

		obs->draw();
		borders->draw();
		golfBall->draw();
		axes->draw();
		golfhole->draw();

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

	delete axes;
	delete grass;
	delete obs;
	delete golfhole;
	delete golfBall;
	return 0;
}

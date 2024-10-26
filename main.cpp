#include<SDL.h>
#include"WindowHandler.h"
#include"Rasterizer.h"
#include"Matrix.h"
#include"Scene.h"
#include"GameObject.h"
#include"TestCube.h"
#include"EventHandler.h"
#include"DeltaTime.h"
#include"TimerHandler.h"
#undef main

int windowHeight = 480;
int windowWidth = 680;
double cameraPlaneDistance = 200;
double movementSpeed = 1;
using namespace std;

#include <vector>
#include <algorithm>

int main() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "didn't initialize\n";
		return 0;
	}
	TimerHandler timerHandler;
	WindowHandler windowHandler;
	Rasterizer rasterizer(windowHandler);
	EventHandler eventHandler;
	Scene scene1;
	DeltaTime dT;
	timerHandler.addTimers(6);

	scene1.objects.push_back(loadGameObject("objects\\dartmonke.obj", "objects\\dartskin.bmp",400));

	scene1.camera.setPosition(Vector3(0,160,0));

	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (eventHandler.getIsRunning())
	{
		eventHandler.handleEvents();
		scene1.camera.handleMovement(eventHandler.getWSAD(),eventHandler.getVerticalMove(), eventHandler.getMousedX(), eventHandler.getMousedY(), dT.getdT());
		scene1.camera.calculateTranspose();

		//scene1.objects[0].rotate(Matrix::yRotation(0.1));

		dT.start();
		windowHandler.clearScreen();
		rasterizer.cleanzbuffer();
		windowHandler.lockScreenTexture();

		//the graphics pipeline
		vector<Triangle3D> triangles = scene1.objectsToSceneSpace();
		for (int i = 0; i < triangles.size(); i++)
		{
			Triangle3D handledTriangle = triangles[i];
			handledTriangle = scene1.camera.convertToCameraSpace(handledTriangle);
			if (scene1.camera.isTriangleFacingAway(handledTriangle)) continue; 
			if (scene1.camera.isTriangleTooNear(handledTriangle)) continue; 
			handledTriangle = scene1.camera.triangle3Dto2Dz(handledTriangle);
			if (scene1.camera.is2DTriangleOutsideOfScreen(handledTriangle))continue;
			rasterizer.drawTrianglez(handledTriangle);
		}

		//rasterizer.drawScenezWire(triangles);

		windowHandler.unlockScreenTexture();
		windowHandler.updateScreen();
		timerHandler.printFrameRate();
	}

	return 0;
}
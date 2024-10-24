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
		timerHandler.startTimer(0);
		triangles = scene1.camera.convertToCameraSpace(triangles);
		timerHandler.printTimer(0);

		timerHandler.startTimer(1);
		triangles = scene1.camera.backfaceCulling(triangles);
		timerHandler.printTimer(1);

		timerHandler.startTimer(2);
		triangles = scene1.camera.nearClipping(triangles);
		timerHandler.printTimer(2);

		timerHandler.startTimer(3);
		triangles = scene1.camera.triangles3Dto2Dz(triangles);
		timerHandler.printTimer(3);

		timerHandler.startTimer(4);
		triangles = scene1.camera.sideClipping(triangles);
		timerHandler.printTimer(4);

		timerHandler.startTimer(5);
		rasterizer.drawScenez(triangles);
		timerHandler.printTimer(5);


		//rasterizer.drawScenezWire(triangles);

		windowHandler.unlockScreenTexture();
		windowHandler.updateScreen();
		timerHandler.printFrameRate();
	}

	return 0;
}
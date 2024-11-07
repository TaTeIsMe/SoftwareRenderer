#include<SDL2/SDL.h>
#include"WindowHandler.h"
#include"GeometryProcessor.h"
#include"Rasterizer.h"
#include"Scene.h"
#include"GameObject.h"
#include"EventHandler.h"
#include"DeltaTime.h"
#include"TimerHandler.h"
#include"Triangle4.h"
#include"Camera4.h"
#undef main

int windowHeight = 480;
int windowWidth = 680;
double cameraPlaneDistance = 200;
double nearPlane = 1;
double farPlane = 9999;
double movementSpeed = 1;
double fov = 1.5708;
double aspectRatio = windowWidth/windowHeight;
using namespace std;

#include <vector>

int main() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "didn't initialize\n";
		return 0;
	}
	TimerHandler timerHandler;
	WindowHandler windowHandler;
	GeometryProcessor geometryProcessor;
	Rasterizer rasterizer(windowHandler);
	EventHandler eventHandler;
	Scene scene1;
	DeltaTime dT;
	timerHandler.addTimers(6);

	scene1.objects.push_back(loadGameObject("objects/mimi.obj", "objects/mimi1.bmp",400));

	scene1.camera.setPosition(Vector3(0,160,0));

	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (eventHandler.getIsRunning())
	{
		eventHandler.handleEvents();
		scene1.camera.handleMovement(eventHandler.getWSAD(),eventHandler.getVerticalMove(), eventHandler.getMousedX(), eventHandler.getMousedY(), dT.getdT());
		scene1.camera.calculateTranspose();
		scene1.objects[0].rotate(Matrix::yRotation(0.1));

		dT.start();
		windowHandler.clearScreen();
		rasterizer.cleanzbuffer();
		windowHandler.lockScreenTexture();

		vector<Triangle3D> triangles = scene1.objectsToSceneSpace();
		//the graphics pipeline
		Camera4 camera4 = Camera4(scene1.camera);
		camera4.calculateInverse();
		for (int i = 0; i < triangles.size(); i++)
		{
			Triangle4 handledTriangle = Triangle4(triangles[i]);
			handledTriangle = geometryProcessor.convertToCameraSpace(handledTriangle,camera4);
			if(geometryProcessor.isTriangleFacingAway(handledTriangle))continue;
			handledTriangle = geometryProcessor.convertToClipSpace(handledTriangle);
			if(geometryProcessor.isTriangleOutsideOfFrustrum(handledTriangle))continue;
			vector<Triangle4> clippedTriangles = geometryProcessor.clipTriangle(handledTriangle);
			if (clippedTriangles.empty())continue;
			for (int i = 0; i < clippedTriangles.size(); i++)
			{
				handledTriangle = geometryProcessor.clipTriangle(handledTriangle).back();
				Triangle3D testTriangle = Triangle3D(geometryProcessor.mapToScreen(handledTriangle));
				rasterizer.drawTrianglez(testTriangle);
			}
			
		}

		windowHandler.unlockScreenTexture();
		windowHandler.updateScreen();
		timerHandler.printFrameRate();
	}

	return 0;
}
#include<SDL.h>
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
double aspectRatio = windowWidth/(double)windowHeight;
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
	scene1.objects.push_back(loadGameObject("objects/mimi.obj", "objects/mimi1.bmp", 400));
	scene1.objects.push_back(loadGameObject("objects/mimi.obj", "objects/mimi1.bmp", 400));
	scene1.objects.push_back(loadGameObject("objects/mimi.obj", "objects/mimi1.bmp", 400));
	scene1.objects[0].setPosition(Vector3(100,200,123));
	scene1.objects[1].setPosition(Vector3(300, -200, 123));
	scene1.objects[2].setPosition(Vector3(546, 1200, -500));
	scene1.objects[0].setRotation(Matrix::xRotation(0.5)* Matrix::yRotation(0.1)* Matrix::zRotation(0.153));
	scene1.objects[1].setRotation(Matrix::xRotation(0.3) * Matrix::yRotation(0.342) * Matrix::zRotation(0.765));
	scene1.objects[2].setRotation(Matrix::xRotation(0.7) * Matrix::yRotation(0.1123) * Matrix::zRotation(0.1123));

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

		int totaltime0 = 0;
		int totaltime1 = 0;
		int totaltime2 = 0;
		int totaltime3 = 0;
		int totaltime4 = 0;
		int totaltime5 = 0;
		int totaltime6 = 0;

		vector<Triangle3D> triangles = scene1.objectsToSceneSpace();
		//the graphics pipeline
		Camera4 camera4 = Camera4(scene1.camera);
		vector<Triangle4> clippedTriangles = vector<Triangle4>();
		camera4.calculateInverse();
		int j = 0;
		for (int i = 0; i < triangles.size(); i++)
		{
			Triangle4 handledTriangle = Triangle4(triangles[i]);
			timerHandler.startTimer(0);
			geometryProcessor.convertToCameraSpace(handledTriangle,camera4);
			totaltime0 += timerHandler.getTimePassed(0).count();
			timerHandler.startTimer(0);
			if(geometryProcessor.isTriangleFacingAway(handledTriangle))continue;
			totaltime1 += timerHandler.getTimePassed(0).count();
			timerHandler.startTimer(0);
			geometryProcessor.convertToClipSpace(handledTriangle);
			totaltime2 += timerHandler.getTimePassed(0).count();
			timerHandler.startTimer(0);
			if(geometryProcessor.isTriangleOutsideOfFrustrum(handledTriangle))continue;
			totaltime3 += timerHandler.getTimePassed(0).count();
			timerHandler.startTimer(0);
			geometryProcessor.clipTriangle(clippedTriangles,handledTriangle);
			totaltime4 += timerHandler.getTimePassed(0).count();
			if (clippedTriangles.empty())continue;
			for (int i = 0; i < clippedTriangles.size(); i++)
			{
				handledTriangle = clippedTriangles[i];
				timerHandler.startTimer(0);
				Triangle3D testTriangle = Triangle3D(geometryProcessor.mapToScreen(handledTriangle));
				totaltime5 += timerHandler.getTimePassed(0).count();
				timerHandler.startTimer(0);
				rasterizer.drawTrianglez(testTriangle);
				totaltime6 += timerHandler.getTimePassed(0).count();
			}
			j++;
		}
		
		/*for (int i = 0; i < triangles.size(); i++)
		{
			Triangle3D handledTriangle = triangles[i];
			timerHandler.startTimer(0);
			handledTriangle = scene1.camera.convertToCameraSpace(handledTriangle);
			totaltime0 += timerHandler.getTimePassed(0).count();
			timerHandler.startTimer(0);
			if (scene1.camera.isTriangleFacingAway(handledTriangle)) continue;
			totaltime1 += timerHandler.getTimePassed(0).count();
			timerHandler.startTimer(0);
			if (scene1.camera.isTriangleTooNear(handledTriangle)) continue;
			totaltime2 += timerHandler.getTimePassed(0).count();
			timerHandler.startTimer(0);
			handledTriangle = scene1.camera.triangle3Dto2Dz(handledTriangle);
			totaltime3 += timerHandler.getTimePassed(0).count();
			timerHandler.startTimer(0);
			if (scene1.camera.is2DTriangleOutsideOfScreen(handledTriangle))continue;
			totaltime4 += timerHandler.getTimePassed(0).count();
			timerHandler.startTimer(0);
			rasterizer.drawTrianglez(handledTriangle);
			totaltime5 += timerHandler.getTimePassed(0).count();
			j++;
		}*/

		cout << "trianglecount: " << j << "\n";
		cout << "stage 0: " << totaltime0 << "\n";
		cout << "stage 1: " << totaltime1 << "\n";
		cout << "stage 2: " << totaltime2 << "\n";
		cout << "stage 3: " << totaltime3 << "\n";
		cout << "stage 4: " << totaltime4 << "\n";
		cout << "stage 5: " << totaltime5 << "\n";
		cout << "stage 6: " << totaltime6 << "\n";

		windowHandler.unlockScreenTexture();
		windowHandler.updateScreen();
		timerHandler.printFrameRate();
	}

	return 0;
}

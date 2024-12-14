#include<SDL.h>
#include"WindowHandler.h"
#include"GeometryProcessor.h"
#include"RasterizationProcessor.h"
#include"Rasterizer.h"
#include"Scene.h"
#include"GameObject.h"
#include"EventHandler.h"
#include"DeltaTime.h"
#include"TimerHandler.h"
#include"Triangle4.h"
#include"Camera4.h"
#include"Pixel.h"
#include"PixelProcessor.h"
#undef main

int windowHeight = 480;
int windowWidth = 680;
double cameraPlaneDistance = 200;
double nearPlane = 200;
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
	RasterizationProcessor rasterizationProcessor;
	PixelProcessor pixelProcessor(windowHandler);
	Rasterizer rasterizer(windowHandler);
	EventHandler eventHandler;
	Scene scene1;
	DeltaTime dT;
	timerHandler.addTimers(6);

	scene1.objects.push_back(loadGameObject("objects/gato.obj", "objects/gato.bmp",100));
	scene1.objects.push_back(loadGameObject("objects/gato.obj", "objects/gato.bmp", 60));
	scene1.objects.push_back(loadGameObject("objects/gato.obj", "objects/gato.bmp", 130));
	scene1.objects[0].rotate(Matrix::xRotation(3*M_PI/2));
	scene1.objects[0].setPosition(Vector3(100,200,123));
	scene1.objects[1].rotate(Matrix::xRotation(3 * M_PI / 2));
	scene1.objects[1].rotate(Matrix::zRotation(1.5 * M_PI / 2));
	scene1.objects[1].setPosition(Vector3(170, 200, 125));
	scene1.objects[2].rotate(Matrix::xRotation(3 * M_PI / 2));
	scene1.objects[2].rotate(Matrix::yRotation(2 * M_PI / 2));
	scene1.objects[2].setPosition(Vector3(10, 200, 120));

	Triangle3 testTriangle = Triangle3(Vertex3(0,0,0,0.5,0.5),Vertex3(300,0,0,0.75,0.5),Vertex3(0,300,0,0.5,0.75),Vector3(0,0,-1),scene1.objects[0].GetShape()[0].texture);
	Triangle3 testTriangle2 = testTriangle;
	for (int i = 0; i < 3; i++)
	{
		testTriangle2[i] *= Matrix::yRotation(M_PI /2);
	}
	testTriangle2.normal *= Matrix::yRotation(M_PI / 2);
	testTriangle2 = testTriangle2 + Vector3(50,0,0);
	testTriangle2 = testTriangle2 + Vector3(0, 0, 100);

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
		pixelProcessor.cleanZBuffer();
		windowHandler.lockScreenTexture();
		
		int totaltime0 = 0;
		int totaltime1 = 0;
		int totaltime2 = 0;
		int totaltime3 = 0;
		int totaltime4 = 0;
		int totaltime5 = 0;
		int totaltime6 = 0;

		vector<Triangle3> triangles = scene1.objectsToSceneSpace();

		//the graphics pipeline
		Camera4 camera4 = Camera4(scene1.camera);
		vector<Triangle4> clippedTriangles;
		vector<Pixel> pixels;
		Triangle4 handledTriangle;
		camera4.calculateInverse();
		int j = 0;
		for (int i = 0; i < triangles.size(); i++)
		{
			
			handledTriangle = Triangle4(triangles[i]);

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
			for (int i = 0; i < clippedTriangles.size(); i++)
			{
				handledTriangle = clippedTriangles[i];
				geometryProcessor.mapToScreen(handledTriangle);
				timerHandler.startTimer(0);
				rasterizationProcessor.rasterizeTriangle(handledTriangle,pixels);
				totaltime5 += timerHandler.getTimePassed(0).count();
				timerHandler.startTimer(0);
				pixelProcessor.drawPixels(pixels);
				totaltime6 += timerHandler.getTimePassed(0).count();
				j++;
			}
		}

		/*for (int i = 0; i < triangles.size(); i++)
		{
			Triangle3 handledTriangle = triangles[i];
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
			handledTriangle = scene1.camera.triangle3to2Dz(handledTriangle);
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
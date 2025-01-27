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
#include"Fragment.h"
#include"FragmentProcessor.h"
#undef main

int windowHeight = 480;
int windowWidth = 680;
double cameraPlaneDistance = 200;
double nearPlane = 50;
double farPlane = 499999;
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
	FragmentProcessor fragmentProcessor(windowHandler);
	Rasterizer rasterizer(windowHandler);
	EventHandler eventHandler;
	Scene scene1;
	DeltaTime dT;
	timerHandler.addTimers(6);

	scene1.objects.push_back(loadGameObject("objects/floor.obj", "objects/missingtexture.bmp", 50));
	//scene1.objects.push_back(loadGameObject("objects/box.obj", "objects/missingtexture.bmp",50));
	//scene1.objects.push_back(loadGameObject("objects/box.obj", "objects/missingtexture.bmp", 50));
	//scene1.objects.push_back(loadGameObject("objects/box.obj", "objects/missingtexture.bmp", 50));
	//scene1.objects[0].setPosition(Vector3(0,-50,0));
	//scene1.objects[1].setPosition(Vector3(0,100,0));
	//scene1.objects[2].setPosition(Vector3(120, 0, 0));
	//scene1.objects[2].setRotation(Matrix::yRotation(0.3));
	//scene1.camera.setPosition(Vector3(153,377,-384));

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		for (int k = 0; k < 10; k++)
	//		{
	//			scene1.objects.push_back(loadGameObject("objects/box.obj", "objects/missingtexture.bmp", 50));
	//			scene1.objects[i*100+j*10+k].setPosition(Vector3(i*300,j*300,k*300));
	//		}
	//	}
	//}
	//scene1.camera.setPosition(Vector3(400,200,-300));

	Triangle4 demoTriangle = Triangle4(Triangle3(Vertex3(0,0,0), Vertex3(100,0,0), Vertex3(0,100,0), Vector3(0,0,-1),scene1.objects[0].GetShape()[0].texture));
	Triangle4 demoTriangle2 = demoTriangle.transformed(Matrix::xRotation4(M_PI / 2.5) * Matrix::zRotation4(M_PI/2));

	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (eventHandler.getIsRunning())
	{
		scene1.camera.handleMovement(eventHandler.getWSAD(), eventHandler.getVerticalMove(), eventHandler.getMousedX(), eventHandler.getMousedY(), 1);
		scene1.camera.calculateTranspose();
		eventHandler.handleEvents();

		dT.start();
		windowHandler.clearScreen();
		rasterizer.cleanzbuffer();
		fragmentProcessor.cleanZBuffer();
		windowHandler.lockScreenTexture();

		//the graphics pipeline

		vector<Fragment> fragments;
		vector<Triangle4> triangles;
		triangles.push_back(demoTriangle);
		triangles.push_back(demoTriangle2);
		vector<Triangle4> clippedTriangles;
		Camera4 camera4 = Camera4(scene1.camera);
		camera4.calculateInverse();
		Triangle4 handledTriangle;
		for (int i = 0; i < triangles.size(); i++)
		{
			handledTriangle = Triangle4(triangles[i]);
			geometryProcessor.convertToCameraSpace(handledTriangle, camera4);
			if (geometryProcessor.isTriangleFacingAway(handledTriangle))continue;
			geometryProcessor.convertToClipSpace(handledTriangle);
			if (geometryProcessor.isTriangleOutsideOfFrustrum(handledTriangle))continue;
			geometryProcessor.clipTriangle(clippedTriangles, handledTriangle);
			for (int j = 0; j < clippedTriangles.size(); j++)
			{
				handledTriangle = clippedTriangles[j];
				geometryProcessor.convertToScreenSpace(handledTriangle);
				rasterizationProcessor.rasterizeTriangle(handledTriangle, fragments);
				//fragmentProcessor.drawFragments(fragments);
				if(i)rasterizer.drawTriangle(Triangle2D(Triangle3(handledTriangle)),0xFF,0x00,0x00);
				else rasterizer.drawTriangle(Triangle2D(Triangle3(handledTriangle)), 0x00, 0x00, 0xFF);
			}
		}
		

		windowHandler.unlockScreenTexture();
		windowHandler.updateScreen();
		timerHandler.printFrameRate();
	}

	return 0;
}
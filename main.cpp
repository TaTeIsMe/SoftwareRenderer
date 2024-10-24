#include <iostream>
#include<SDL.h>
#include"WindowHandler.h"
#include"Rasterizer.h"
#include"Matrix.h"
#include"Scene.h"
#include"GameObject.h"
#include"TestCube.h"
#include"EventHandler.h"
#include"DeltaTime.h"
#undef main

int windowHeight = 480;
int windowWidth = 680;
double cameraPlaneDistance = 200;
double movementSpeed = 1;
using namespace std;



#include <SDL.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>

void PrintFrameTiming(std::ostream& os = std::cout, float period = 2.0f)
{
	static unsigned int frames = 0;
	frames++;
	static auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();

	float seconds = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
	if (seconds > period)
	{
		float spf = seconds / frames;
		/*os
			<< frames << " frames in "
			<< std::setprecision(1) << std::fixed << seconds << " seconds = "
			<< std::setprecision(1) << std::fixed << 1.0f / spf << " FPS ("
			<< std::setprecision(3) << std::fixed << spf * 1000.0f << " ms/frame)\n";*/
		frames = 0;
		start = end;
	}
}

void PrintPhasesTiming(std::chrono::steady_clock::time_point times[]) {
	int ftimes[6];
	for (int i = 0; i < 6; i++)
	{
		ftimes[i] = std::chrono::duration_cast<std::chrono::microseconds>(times[i + 1] - times[i]).count();
	}
	//std::cout << ftimes[0] << "\n" << ftimes[1] << "\n" << ftimes[2] << "\n" << ftimes[3] << "\n" << ftimes[4] << "\n" << ftimes[5] << "\n";
}

int main() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "didn't initialize\n";
		return 0;
	}

	WindowHandler windowHandler;
	Rasterizer rasterizer(windowHandler);
	EventHandler eventHandler;
	Scene scene1;
	DeltaTime dT;
	std::chrono::steady_clock::time_point times[7];

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
		times[0] =  std::chrono::steady_clock::now();
		triangles = scene1.camera.convertToCameraSpace(triangles);
		times[1] = std::chrono::steady_clock::now();
		triangles = scene1.camera.backfaceCulling(triangles);
		times[2] = std::chrono::steady_clock::now();
		triangles = scene1.camera.nearClipping(triangles);
		times[3] = std::chrono::steady_clock::now();
		triangles = scene1.camera.triangles3Dto2Dz(triangles);
		times[4] = std::chrono::steady_clock::now();
		triangles = scene1.camera.sideClipping(triangles);
		times[5] = std::chrono::steady_clock::now();
		rasterizer.drawScenez(triangles);
		times[6] = std::chrono::steady_clock::now();
		//rasterizer.drawScenezWire(triangles);

		windowHandler.unlockScreenTexture();
		windowHandler.updateScreen();
		PrintFrameTiming();
		PrintPhasesTiming(times);
	}

	return 0;
}
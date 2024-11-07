#include"SDL2/SDL.h"
#include "WindowHandler.h"
#include<iostream>
using namespace std;
extern  int windowWidth;
extern int windowHeight;

WindowHandler::WindowHandler():pitch(windowWidth*4)
{
	pixels = new char[windowHeight*windowWidth*4]();

	window = SDL_CreateWindow("SoftwareRenderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
	

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Unable to create renderer: %s\n", SDL_GetError());
	}

	windowSurface = SDL_GetWindowSurface(window);
	bool isRunning = true;

	frameBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
	if (frameBuffer == NULL)
	{
		printf("Unable to create streamable blank texture! SDL Error: %s\n", SDL_GetError());
	}
}

WindowHandler::~WindowHandler()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void WindowHandler::lockScreenTexture()
{
	if(SDL_LockTexture(frameBuffer,NULL,reinterpret_cast<void**>(&pixels), &pitch)!= 0)
	{
		//printf("Unable to lock texture! %s\n", SDL_GetError());
	}
}

void WindowHandler::unlockScreenTexture()
{
	SDL_UnlockTexture(frameBuffer);
}

void WindowHandler::clearScreen() const {
	for (int i = 0; i < windowHeight * windowWidth * 4; i++)
	{
		pixels[i] = 0xFF;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
};

void WindowHandler::drawPoint(Vector2 point, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
	unsigned int offset = (windowWidth * (-point.y+windowHeight/2) * 4) + (point.x+windowWidth/2) * 4;
	if (abs(-point.y) < windowHeight/2  && abs(point.x) < windowWidth / 2) {
		pixels[offset + 0] = a;
		pixels[offset + 1] = b;
		pixels[offset + 2] = g;
		pixels[offset + 3] = r;
	}
}

void WindowHandler::updateScreen() const {
	SDL_RenderCopy(renderer,frameBuffer,NULL,NULL);
	SDL_RenderPresent(renderer);
}
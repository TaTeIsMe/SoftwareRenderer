#pragma once
#include"SDL2/SDL.h"
#include "Vector2.h"

class WindowHandler
{
private:
	char* pixels;
	SDL_Surface* windowSurface;
	SDL_Renderer* renderer;
	SDL_Texture* frameBuffer;
	int pitch;
public:
	SDL_Window* window;
	WindowHandler();
	~WindowHandler();
	void lockScreenTexture();
	void unlockScreenTexture();
	void drawPoint(Vector2 point, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
	void clearScreen() const;
	void updateScreen() const;
};


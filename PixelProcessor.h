#pragma once
#include "WindowHandler.h"
#include<vector>
#include"Pixel.h"
class PixelProcessor
{
private:
public:
	Uint32 getpixel(SDL_Surface* surface, int x, int y);
	WindowHandler& windowHandler;
	float* zbuffer;
	void drawPixels(const std::vector<Pixel>& pixels);
	void cleanZBuffer();
	PixelProcessor(WindowHandler& windowHandler);
	~PixelProcessor();
};


#pragma once
#include<SDL.h>
struct Pixel
{
	int x;
	int y;
	float uprim;
	float vprim;
	float wprim;
	float z;
	SDL_Surface* texture;
	Pixel(int x, int y, float uprim, float vprim, float wprim, float z, SDL_Surface* texture);
};


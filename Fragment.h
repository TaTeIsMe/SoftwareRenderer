#pragma once
#include<SDL.h>
struct Fragment
{
	int x;
	int y;
	float uprim;
	float vprim;
	float wprim;
	float z;
	SDL_Surface* texture;
	Fragment(int x, int y, float uprim, float vprim, float wprim, float z, SDL_Surface* texture);
};


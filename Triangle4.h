#pragma once
#include<SDL.h>
#include"Vertex4.h"
class Triangle4
{
	Vertex4 vertices[3];
	Vector4 normal;
	SDL_Surface* texture;

	Triangle4();
	Triangle4(Vertex4 vertex1, Vertex4 vertex2, Vertex4 vertex3);
	Triangle4(Vertex4 vertex1, Vertex4 vertex2, Vertex4 vertex3, Vector4 normal, SDL_Surface* texture);
	Vertex4& operator [](int index);
};


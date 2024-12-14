#pragma once
#include<SDL.h>
#include"Vertex4.h"
#include"Triangle3.h"

struct Triangle4
{
	Vertex4 vertices[3];
	Vector4 normal;
	SDL_Surface* texture;

	Triangle4();
	Triangle4(Vertex4 vertex1, Vertex4 vertex2, Vertex4 vertex3);
	Triangle4(Vertex4 vertex1, Vertex4 vertex2, Vertex4 vertex3, Vector4 normal, SDL_Surface* texture);
	explicit Triangle4(const class Triangle3& triangle3);
	Triangle4 transformed(const Matrix&)const;
	Vertex4& operator [](int index);
	const Vertex4& operator [](int index)const;
};


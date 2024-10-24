#pragma once
#include"Vector3.h"
#include"Vertex3.h"
#include<SDL.h>
struct Triangle3D {
	Vertex3 vertices[3];
	Vector3 normal;
	SDL_Surface* texture;

	Triangle3D();
	Triangle3D(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3);
	Triangle3D(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3,Vector3 normal,SDL_Surface* texture);
	Triangle3D(const struct Triangle2D&);
	Vertex3& operator [](const int& index);
	friend const Triangle3D operator +(const Triangle3D& lhs, const Vector3& rhs);
	friend const Triangle3D operator *(const Triangle3D& lhs, const Matrix& rhs);

};
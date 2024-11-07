#pragma once
#include"Vector3.h"
#include"Vertex3.h"
#include"Triangle4.h"
#include<SDL2/SDL.h>
struct Triangle3D {
	Vertex3 vertices[3];
	Vector3 normal;
	SDL_Surface* texture;

	Triangle3D();
	Triangle3D(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3);
	Triangle3D(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3,Vector3 normal,SDL_Surface* texture);

	//removelater
	explicit Triangle3D(const struct Triangle4&);

	Vertex3& operator [](int index) ;
	const Vertex3& operator [](int index)const;
	friend const Triangle3D operator +(const Triangle3D& lhs, const Vector3& rhs);
	friend const Triangle3D operator *(const Triangle3D& lhs, const Matrix& rhs);

};
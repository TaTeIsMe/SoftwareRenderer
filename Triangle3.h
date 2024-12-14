#pragma once
#include"Vector3.h"
#include"Vertex3.h"
#include"Triangle4.h"
#include<SDL.h>
struct Triangle3 {
	Vertex3 vertices[3];
	Vector3 normal;
	SDL_Surface* texture;

	Triangle3();
	Triangle3(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3);
	Triangle3(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3,Vector3 normal,SDL_Surface* texture);
	explicit Triangle3(const struct Triangle4&);
	Vertex3& operator [](int index) ;
	const Vertex3& operator [](int index)const;
	friend const Triangle3 operator +(const Triangle3& lhs, const Vector3& rhs);
	friend const Triangle3 operator *(const Triangle3& lhs, const Matrix& rhs);

};
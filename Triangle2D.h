#pragma once
#include "Vector2.h"

struct Triangle2D
{
	Vector2 vertices[3];
	Triangle2D();
	Triangle2D(const struct Triangle3D&);
	Vector2& operator [](const int& index);
};
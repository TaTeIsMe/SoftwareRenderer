#pragma once
#include "Vector3.h"
struct Vertex3: public Vector3
{
	double u;
	double v;
	Vertex3();
	Vertex3(double x, double y, double z);
	Vertex3(double x, double y, double z, double u, double v);
	Vertex3(const Vector3& vector3,double u, double v);
	explicit Vertex3(const struct Vertex4& vertex4);
};


#pragma once
#include "Vector4.h"
struct Vertex4 : public Vector4
{
	double u;
	double v;
	Vertex4();
	Vertex4(double x, double y, double z, double w = 1, double u = 0, double v = 0);
	Vertex4(Vector4 vector4, double u = 0, double v = 0);
};


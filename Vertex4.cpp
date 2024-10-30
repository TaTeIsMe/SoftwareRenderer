#include "Vertex4.h"
Vertex4::Vertex4() :u(), v(), Vector4()
{
}

Vertex4::Vertex4(double x, double y, double z, double w, double u, double v) :Vector4(x, y, z, w), u(u), v(v)
{
}

Vertex4::Vertex4(Vector4 vector4, double u, double v) :Vector4(vector4), u(u), v(v)
{
}

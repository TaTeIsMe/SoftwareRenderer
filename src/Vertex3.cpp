#include "Vertex3.h"
#include "Vertex4.h"
Vertex3::Vertex3():u(),v(), Vector3()
{
}

Vertex3::Vertex3(double x, double y, double z):Vector3(x,y,z),u(0),v(0)
{
}

Vertex3::Vertex3(double x, double y, double z, double u, double v):Vector3(x,y,z),u(u),v(v)
{
}

Vertex3::Vertex3(const Vector3& vector3, double u, double v):Vector3(vector3), u(u), v(v)
{
}

Vertex3::Vertex3(const Vertex4& vertex4):Vector3(vertex4),u(vertex4.u),v(vertex4.v)
{
}

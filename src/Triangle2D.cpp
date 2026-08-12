#include "Triangle2D.h"
#include "Triangle3.h"
#include <algorithm>
Triangle2D::Triangle2D()
{
}
Triangle2D::Triangle2D(const Triangle3& tri3D) :vertices{tri3D.vertices[0],tri3D.vertices[1] ,tri3D.vertices[2] }
{
}
Vector2& Triangle2D::operator [](int index)
{
	return vertices[index];
}

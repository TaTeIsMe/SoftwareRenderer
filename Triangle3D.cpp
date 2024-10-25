#include "Triangle3D.h"
#include "Vector3.h"
#include "Triangle2D.h"

Triangle3D::Triangle3D() :vertices{ Vertex3(),Vertex3(),Vertex3() }, normal(Vector3()), texture(NULL)
{
}

Triangle3D::Triangle3D(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3) :vertices{vertex1,vertex2,vertex3}, normal(Vector3()), texture(NULL)
{
}

Triangle3D::Triangle3D(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3,Vector3 normal,SDL_Surface* texture) :vertices{ vertex1,vertex2,vertex3 }, normal(normal), texture(texture)
{
}

Triangle3D::Triangle3D(const Triangle2D& tri2D) :vertices{Vertex3(tri2D.vertices[0]),Vertex3(tri2D.vertices[1]),Vertex3(tri2D.vertices[2]) } , normal(Vector3()) , texture(NULL)
{
}

Vertex3& Triangle3D::operator [](int index)
{
	return vertices[index];
}

const Triangle3D operator +(const Triangle3D& lhs, const Vector3& rhs) {
	Triangle3D tempTriangle(lhs);
	for (int i = 0; i < 3; i++)
	{
		tempTriangle[i] += rhs;
	}
	return tempTriangle;
};

const Triangle3D operator *(const Triangle3D& lhs, const Matrix& rhs) {
	Triangle3D tempTriangle(lhs);
	for (int i = 0; i < 3; i++)
	{
		tempTriangle[i] *= rhs;
	}
	return tempTriangle;
};
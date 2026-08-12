#include "Triangle3.h"
#include "Vector3.h"
#include "Triangle2D.h"

Triangle3::Triangle3() :vertices{ Vertex3(),Vertex3(),Vertex3() }, normal(Vector3()), texture(NULL)
{
}

Triangle3::Triangle3(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3) :vertices{vertex1,vertex2,vertex3}, normal(Vector3()), texture(NULL)
{
}

Triangle3::Triangle3(Vertex3 vertex1, Vertex3 vertex2, Vertex3 vertex3,Vector3 normal,SDL_Surface* texture) :vertices{ vertex1,vertex2,vertex3 }, normal(normal), texture(texture)
{
}



Triangle3::Triangle3(const Triangle4& triangle4) : vertices{ Vertex3(triangle4[0].x,triangle4[0].y,triangle4[0].z,triangle4[0].u,triangle4[0].v),Vertex3(triangle4[1].x,triangle4[1].y,triangle4[1].z,triangle4[1].u,triangle4[1].v),Vertex3(triangle4[2].x,triangle4[2].y,triangle4[2].z,triangle4[2].u,triangle4[2].v) }, normal(Vector3(triangle4.normal.x, triangle4.normal.y, triangle4.normal.z)), texture(triangle4.texture)
{
}

Vertex3& Triangle3::operator [](int index)
{
	return vertices[index];
}

const Vertex3& Triangle3::operator[](int index) const
{
	return vertices[index];
}

const Triangle3 operator +(const Triangle3& lhs, const Vector3& rhs) {
	Triangle3 tempTriangle(lhs);
	for (int i = 0; i < 3; i++)
	{
		tempTriangle[i] += rhs;
	}
	return tempTriangle;
};

const Triangle3 operator *(const Triangle3& lhs, const Matrix& rhs) {
	Triangle3 tempTriangle(lhs);
	for (int i = 0; i < 3; i++)
	{
		tempTriangle[i] *= rhs;
	}
	return tempTriangle;
};
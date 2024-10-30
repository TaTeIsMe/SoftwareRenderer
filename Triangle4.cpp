#include "Triangle4.h"
Triangle4::Triangle4() :vertices{ Vertex4(),Vertex4(),Vertex4() }, normal(Vector4()), texture(NULL)
{
	normal.w = 0;
}

Triangle4::Triangle4(Vertex4 vertex1, Vertex4 vertex2, Vertex4 vertex3) :vertices{ vertex1,vertex2,vertex3 }, normal(Vector4()), texture(NULL)
{
	normal.w = 0;
}

Triangle4::Triangle4(Vertex4 vertex1, Vertex4 vertex2, Vertex4 vertex3, Vector4 normal, SDL_Surface* texture) :vertices{ vertex1,vertex2,vertex3 }, normal(normal), texture(texture)
{
	normal.w = 0;
}

Triangle4::Triangle4(Triangle3D triangle3) : vertices{ Vertex4(triangle3[0]),Vertex4(triangle3[1]),Vertex4(triangle3[2]) }, normal(Vector4(triangle3.normal)), texture(triangle3.texture)
{
	normal.w = 0;
}


Vertex4& Triangle4::operator [](int index)
{
	return vertices[index];
}
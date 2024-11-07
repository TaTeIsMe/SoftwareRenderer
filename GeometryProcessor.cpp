#include "GeometryProcessor.h"
#include"iostream"
extern double fov;
extern double aspectRatio;
extern double nearPlane;
extern double farPlane;

Triangle4 GeometryProcessor::convertToCameraSpace(Triangle4 worldTriangle, Camera4 camera4) const
{
    worldTriangle = worldTriangle.transformed(camera4.inverse);
	worldTriangle.normal *= camera4.inverse;
    return worldTriangle;
}

Triangle4 GeometryProcessor::convertToClipSpace(Triangle4 cameraTriangle) const
{
	double c = 1/tan(fov/2);
	Matrix projectionMatrix = Matrix(Matrix::identityMatrix(4));
	projectionMatrix[0][0] = c/aspectRatio;
	projectionMatrix[1][1] = c;
	projectionMatrix[2][2] = (farPlane+ nearPlane)/(farPlane-nearPlane);
	projectionMatrix[3][3] = 0;
	projectionMatrix[2][3] = -2*farPlane*nearPlane/(farPlane-nearPlane);
	projectionMatrix[3][2] = 1;

	for (size_t i = 0; i < 3; i++)
	{
		cameraTriangle[i] *= projectionMatrix;
	}
	return cameraTriangle;
}

std::vector<Triangle4> GeometryProcessor::clipTriangle(Triangle4 clipTriangle) const
{

	return { clipTriangle };
}

bool GeometryProcessor::isTriangleOutsideOfFrustrum(Triangle4 clipTriangle) const{
	if(
		(clipTriangle[0].x > clipTriangle[0].w && clipTriangle[1].x > clipTriangle[1].w && clipTriangle[2].x > clipTriangle[2].w) ||
		(clipTriangle[0].x < -clipTriangle[0].w && clipTriangle[1].x < -clipTriangle[1].w && clipTriangle[2].x < -clipTriangle[2].w) ||
		(clipTriangle[0].y > clipTriangle[0].w && clipTriangle[1].y > clipTriangle[1].w && clipTriangle[2].y > clipTriangle[2].w) ||
		(clipTriangle[0].y < -clipTriangle[0].w && clipTriangle[1].y < -clipTriangle[1].w && clipTriangle[2].y < -clipTriangle[2].w) ||
		(clipTriangle[0].z > clipTriangle[0].w && clipTriangle[1].z > clipTriangle[1].w && clipTriangle[2].z > clipTriangle[2].w) ||
		(clipTriangle[0].z < -clipTriangle[0].w && clipTriangle[1].z < -clipTriangle[1].w && clipTriangle[2].z < -clipTriangle[2].w)
	)return true;
	return false;
}

Triangle4 GeometryProcessor::mapToScreen(Triangle4 triangle) const
{
	for (int i = 0; i < 3; i++)
	{
		triangle[i] *= 1/triangle[i].w;
		triangle[i] *= 200;
	}
	return triangle;
}

bool GeometryProcessor::isTriangleFacingAway(Triangle4 triangle) const
{
		if (Vector4::dotProduct(triangle[0], triangle.normal) >= 0)
		{
			return true;
		}
	return false;
}

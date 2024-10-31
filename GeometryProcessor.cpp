#include "GeometryProcessor.h"
#include"iostream";
extern double fov;
extern double aspectRatio;
extern double nearPlane;
extern double farPlane;

Triangle4 GeometryProcessor::convertToCameraSpace(Triangle4 worldTriangle, Camera4 camera4) const
{
    worldTriangle = worldTriangle.transformed(camera4.rigidBody.getInverse());
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
	for (int i = 0; i < 3; i++)
	{
		if (!(clipTriangle[i].x > -clipTriangle[i].w &&
			clipTriangle[i].x < clipTriangle[i].w &&
			clipTriangle[i].y > -clipTriangle[i].w &&
			clipTriangle[i].y < clipTriangle[i].w &&
			clipTriangle[i].z > -clipTriangle[i].w &&
			clipTriangle[i].z < clipTriangle[i].w)
			)return {};
	}
	return { clipTriangle };
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

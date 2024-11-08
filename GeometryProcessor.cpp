#include "GeometryProcessor.h"
#include"iostream"
extern double fov;
extern double aspectRatio;
extern double nearPlane;
extern double farPlane;

void GeometryProcessor::clipToRightPlane()
{
	newVertices.clear();
	//interpolation factor for the line
	double t = 0;
	for (int i = 0; i < oldVertices.size(); ++i)
	{
		const Vertex4 currentVertex = oldVertices[i];
		const Vertex4 nextVertex = oldVertices[(i + 1) % oldVertices.size()];

		// Case 1: Current vertex is outside the plane, next is inside
		if ((currentVertex.x > currentVertex.w) && (nextVertex.x < nextVertex.w)) {
			//calculate the interpolation factor
			t = (currentVertex.x - currentVertex.w) / ((currentVertex.x - currentVertex.w) - (nextVertex.x - nextVertex.w));
			//find the intersection with the clipping plane
			newVertices.push_back(t * nextVertex + ((1 - t) * currentVertex));
			newVertices.back().v = t*nextVertex.v + ((1 - t) * currentVertex.v);
			newVertices.back().u = t * nextVertex.u + ((1 - t) * currentVertex.u);
			newVertices.push_back(nextVertex);
		}

		// Case 2: Current vertex is inside the plane, next is outside
		else if ((currentVertex.x < currentVertex.w) && (nextVertex.x > nextVertex.w)) {
			//calculate the interpolation factor
			t = (currentVertex.x - currentVertex.w) / ((currentVertex.x - currentVertex.w) - (nextVertex.x - nextVertex.w));
			//find the intersection with the clipping plane
			newVertices.push_back(t * nextVertex + ((1 - t) * currentVertex));
			newVertices.back().v = t * nextVertex.v + ((1 - t) * currentVertex.v);
			newVertices.back().u = t * nextVertex.u + ((1 - t) * currentVertex.u);
		}

		// Case 3: Both vertices are inside
		else if ((currentVertex.x < currentVertex.w) && (nextVertex.x < nextVertex.w))
			newVertices.push_back(nextVertex);
	}
	oldVertices = newVertices;
}

void GeometryProcessor::clipToLeftPlane()
{
	newVertices.clear();
	//interpolation factor for the line
	double t = 0;
	for (int i = 0; i < oldVertices.size(); ++i)
	{
		const Vertex4 currentVertex = oldVertices[i];
		const Vertex4 nextVertex = oldVertices[(i + 1) % oldVertices.size()];

		// Case 1: Current vertex is outside the plane, next is inside
		if ((currentVertex.x < -currentVertex.w) && (nextVertex.x > -nextVertex.w)) {
			//calculate the interpolation factor
			t = (currentVertex.x + currentVertex.w) / ((currentVertex.x + currentVertex.w) - (nextVertex.x + nextVertex.w));
			//find the intersection with the clipping plane
			newVertices.push_back(t * nextVertex + ((1 - t) * currentVertex));
			newVertices.back().v = t * nextVertex.v + ((1 - t) * currentVertex.v);
			newVertices.back().u = t * nextVertex.u + ((1 - t) * currentVertex.u);
			newVertices.push_back(nextVertex);
		}

		// Case 2: Current vertex is inside the plane, next is outside
		else if ((currentVertex.x > -currentVertex.w) && (nextVertex.x < -nextVertex.w)) {
			//calculate the interpolation factor
			t = (currentVertex.x + currentVertex.w) / ((currentVertex.x + currentVertex.w) - (nextVertex.x + nextVertex.w));
			//find the intersection with the clipping plane
			newVertices.push_back(t * nextVertex + ((1 - t) * currentVertex));
			newVertices.back().v = t * nextVertex.v + ((1 - t) * currentVertex.v);
			newVertices.back().u = t * nextVertex.u + ((1 - t) * currentVertex.u);
		}

		// Case 3: Both vertices are inside
		else if ((currentVertex.x > -currentVertex.w) && (nextVertex.x > -nextVertex.w))
			newVertices.push_back(nextVertex);
	}
	oldVertices = newVertices;
}

void GeometryProcessor::clipToTopPlane()
{
	newVertices.clear();
	//interpolation factor for the line
	double t = 0;
	for (int i = 0; i < oldVertices.size(); ++i)
	{
		const Vertex4 currentVertex = oldVertices[i];
		const Vertex4 nextVertex = oldVertices[(i + 1) % oldVertices.size()];

		// Case 1: Current vertex is outside the plane, next is inside
		if ((currentVertex.y > currentVertex.w) && (nextVertex.y < nextVertex.w)) {
			//calculate the interpolation factor
			t = (currentVertex.y - currentVertex.w) / ((currentVertex.y - currentVertex.w) - (nextVertex.y - nextVertex.w));
			//find the intersection with the clipping plane
			newVertices.push_back(t * nextVertex + ((1 - t) * currentVertex));
			newVertices.back().v = t * nextVertex.v + ((1 - t) * currentVertex.v);
			newVertices.back().u = t * nextVertex.u + ((1 - t) * currentVertex.u);
			newVertices.push_back(nextVertex);
		}

		// Case 2: Current vertex is inside the plane, next is outside
		else if ((currentVertex.y < currentVertex.w) && (nextVertex.y > nextVertex.w)) {
			//calculate the interpolation factor
			t = (currentVertex.y - currentVertex.w) / ((currentVertex.y - currentVertex.w) - (nextVertex.y - nextVertex.w));
			//find the intersection with the clipping plane
			newVertices.push_back(t * nextVertex + ((1 - t) * currentVertex));
			newVertices.back().v = t * nextVertex.v + ((1 - t) * currentVertex.v);
			newVertices.back().u = t * nextVertex.u + ((1 - t) * currentVertex.u);
		}

		// Case 3: Both vertices are inside
		else if ((currentVertex.y < currentVertex.w) && (nextVertex.y < nextVertex.w))
			newVertices.push_back(nextVertex);
	}
	oldVertices = newVertices;
}

void GeometryProcessor::clipToBottomPlane()
{
	newVertices.clear();
	//interpolation factor for the line
	double t = 0;
	for (int i = 0; i < oldVertices.size(); ++i)
	{
		const Vertex4 currentVertex = oldVertices[i];
		const Vertex4 nextVertex = oldVertices[(i + 1) % oldVertices.size()];

		// Case 1: Current vertex is outside the plane, next is inside
		if ((currentVertex.y < -currentVertex.w) && (nextVertex.y > -nextVertex.w)) {
			//calculate the interpolation factor
			t = (currentVertex.y + currentVertex.w) / ((currentVertex.y + currentVertex.w) - (nextVertex.y + nextVertex.w));
			//find the intersection with the clipping plane
			newVertices.push_back(t * nextVertex + ((1 - t) * currentVertex));
			newVertices.back().v = t * nextVertex.v + ((1 - t) * currentVertex.v);
			newVertices.back().u = t * nextVertex.u + ((1 - t) * currentVertex.u);
			newVertices.push_back(nextVertex);
		}

		// Case 2: Current vertex is inside the plane, next is outside
		else if ((currentVertex.y > -currentVertex.w) && (nextVertex.y < -nextVertex.w)) {
			//calculate the interpolation factor
			t = (currentVertex.y + currentVertex.w) / ((currentVertex.y + currentVertex.w) - (nextVertex.y + nextVertex.w));
			//find the intersection with the clipping plane
			newVertices.push_back(t * nextVertex + ((1 - t) * currentVertex));
			newVertices.back().v = t * nextVertex.v + ((1 - t) * currentVertex.v);
			newVertices.back().u = t * nextVertex.u + ((1 - t) * currentVertex.u);
		}

		// Case 3: Both vertices are inside
		else if ((currentVertex.y > -currentVertex.w) && (nextVertex.y > -nextVertex.w))
			newVertices.push_back(nextVertex);
	}
	oldVertices = newVertices;
}

void GeometryProcessor::clipToNearPlane()
{
}

Triangle4& GeometryProcessor::convertToCameraSpace(Triangle4& worldTriangle,const Camera4& camera4) const
{
	for (int i = 0; i < 3; i++)
	{
		//translate to camera space
		worldTriangle[i] *= camera4.inverse;
	}
	worldTriangle.normal *= camera4.inverse;
    return worldTriangle;
}

Triangle4& GeometryProcessor::convertToClipSpace(Triangle4& cameraTriangle) const
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



std::vector<Triangle4>& GeometryProcessor::clipTriangle(std::vector<Triangle4>& outputVector, Triangle4& clipTriangle)
{
	outputVector.clear();
	if (isTriangleEntirelyInsideFrustrum(clipTriangle)) { outputVector.push_back(clipTriangle); return outputVector; }
	newVertices.clear();
	oldVertices.clear();
	oldVertices = std::vector<Vertex4> (std::begin(clipTriangle.vertices),std::end(clipTriangle.vertices));

	clipToRightPlane();
	clipToLeftPlane();
	clipToTopPlane();
	clipToBottomPlane();
	clipToNearPlane();
	
	//turn points into triangles
	if (!newVertices.empty()) {
		for (int i = 0; i < newVertices.size() - 2; i++)
		{
			outputVector.push_back(Triangle4(newVertices[0], newVertices[i + 1], newVertices[i + 2], clipTriangle.normal, clipTriangle.texture));
		}
	}

	return outputVector;
}

bool GeometryProcessor::isTriangleEntirelyInsideFrustrum(const Triangle4& triangle) const {
	//check if any of the vertices are outside any of the clipping planes
	for (int i = 0; i < 3; i++) {
		if (triangle[i].x > triangle[i].w ||    
			triangle[i].x < -triangle[i].w ||    
			triangle[i].y > triangle[i].w ||     
			triangle[i].y < -triangle[i].w ||   
			triangle[i].z > triangle[i].w ||     
			triangle[i].z < -triangle[i].w) {    
			return false; 
		}
	}
	return true; 
}
bool GeometryProcessor::isTriangleOutsideOfFrustrum(const Triangle4& triangle) const
{
	if (
		//each vertex is outside the right plane
		(triangle[0].x > triangle[0].w && triangle[1].x > triangle[1].w && triangle[2].x > triangle[2].w) ||
		//each vertex is outside the left plane
		(triangle[0].x < -triangle[0].w && triangle[1].x < -triangle[1].w && triangle[2].x < -triangle[2].w) ||
		//each vertex is outside the upper plane
		(triangle[0].y > triangle[0].w && triangle[1].y > triangle[1].w && triangle[2].y > triangle[2].w) ||
		//each vertex is outside the lower plane
		(triangle[0].y < -triangle[0].w && triangle[1].y < -triangle[1].w && triangle[2].y < -triangle[2].w) ||
		//each vertex is outside the far plane
		(triangle[0].z > triangle[0].w && triangle[1].z > triangle[1].w && triangle[2].z > triangle[2].w) ||
		//each vertex is outside the near plane
		(triangle[0].z < -triangle[0].w && triangle[1].z < -triangle[1].w && triangle[2].z < -triangle[2].w)
		)return true;
	return false;
	
}

Triangle4& GeometryProcessor::mapToScreen(Triangle4& triangle) const
{
	for (int i = 0; i < 3; i++)
	{
		triangle[i] *= 1/triangle[i].w;
		triangle[i] *= 200;
	}
	return triangle;
}

bool GeometryProcessor::isTriangleFacingAway(const Triangle4& triangle) const
{
		if (Vector4::dotProduct(triangle[0], triangle.normal) >= 0)
		{
			return true;
		}
	return false;
}

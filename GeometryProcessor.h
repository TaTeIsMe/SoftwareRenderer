#pragma once
#include"Triangle4.h"
#include"Camera4.h"
#include<vector>
class GeometryProcessor
{
	std::vector<Vertex4>oldVertices;
	std::vector<Vertex4>newVertices;
	Matrix projectionMatrix;
	Matrix projectionInverseTranspose;
	void clipToRightPlane();
	void clipToLeftPlane();
	void clipToTopPlane();
	void clipToBottomPlane();
	void clipToNearPlane();
	
public:
	GeometryProcessor();
	Triangle4& convertToCameraSpace(Triangle4& worldTriangle,const Camera4& camera4)const;
	Triangle4& convertToClipSpace(Triangle4& cameraTriangle)const;
	std::vector<Triangle4>& clipTriangle(std::vector<Triangle4>& outputVector, Triangle4& clipTriangle);
	Triangle4& convertToScreenSpace(Triangle4& triangle)const;
    bool isTriangleFacingAway(const Triangle4& triangle) const;
	bool isTriangleOutsideOfFrustrum(const Triangle4& triangle)const;
	bool isTriangleEntirelyInsideFrustrum(const Triangle4& triangle)const;
};

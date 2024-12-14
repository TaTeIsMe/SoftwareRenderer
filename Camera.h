#pragma once
#include "Triangle2D.h"
#include "GameObject.h"
#include "Triangle4.h"
#include<vector>
class Camera : public GameObject {
	Matrix transpose;
	Vector3 planePos;
public:
	Triangle2D triangle3to2D(Triangle3 worldTriangle) const;
	Triangle3& triangle3to2Dz(Triangle3& worldTriangle) const;
	Triangle3& convertToCameraSpace(Triangle3& worldTriangle)const;
	std::vector<Triangle3> convertToCameraSpace(std::vector<Triangle3> worldTriangles) const;

	//assumes triangles are in camera space
	std::vector<Triangle3> backfaceCulling(std::vector<Triangle3> triangles)const;
	bool isTriangleFacingAway(const Triangle3& triangle) const ;
	std::vector<Triangle3> nearClipping(std::vector<Triangle3> triangles)const;
	bool isTriangleTooNear(const Triangle3& triangle) const;
	//returned z is original distance from cameraplane
	std::vector<Triangle3> triangles3Dto2Dz(std::vector<Triangle3> triangles)const;
	//poor man's frustrum clipping
	std::vector<Triangle3> sideClipping(std::vector<Triangle3> triangles)const;

	double getPlanez()const;
	Matrix getTranspose()const;
	void calculateTranspose();
	void clipTriangleToSides2D(Triangle3 projectedTriangle,std::vector<Triangle3>& worldTriangles)const;
	bool is2DTriangleOutsideOfScreen(const Triangle3& triangle) const;
	void handleMovement(Vector3 WSAD,int verticalMove, int mouseX, int mouseY,int dT);
	Camera();
};



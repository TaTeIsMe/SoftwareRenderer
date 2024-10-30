#pragma once
#include "Triangle2D.h"
#include "GameObject.h"
#include "Triangle4.h"
#include<vector>
class Camera : public GameObject {
	Matrix transpose;
	Vector3 planePos;
public:
	Triangle2D triangle3Dto2D(Triangle3D worldTriangle) const;
	Triangle3D triangle3Dto2Dz(Triangle3D worldTriangle) const;
	Triangle3D convertToCameraSpace(Triangle3D worldTriangle)const;
	std::vector<Triangle3D> convertToCameraSpace(std::vector<Triangle3D> worldTriangles) const;

	//assumes triangles are in camera space
	std::vector<Triangle3D> backfaceCulling(std::vector<Triangle3D> triangles)const;
	bool isTriangleFacingAway(Triangle3D triangle) const ;
	std::vector<Triangle3D> nearClipping(std::vector<Triangle3D> triangles)const;
	bool isTriangleTooNear(Triangle3D triangle) const;
	//returned z is original distance from cameraplane
	std::vector<Triangle3D> triangles3Dto2Dz(std::vector<Triangle3D> triangles)const;
	//poor man's frustrum clipping
	std::vector<Triangle3D> sideClipping(std::vector<Triangle3D> triangles)const;

	double getPlanez()const;
	Matrix getTranspose()const;
	void calculateTranspose();
	void clipTriangleToSides2D(Triangle3D projectedTriangle,std::vector<Triangle3D>& worldTriangles)const;
	bool is2DTriangleOutsideOfScreen(Triangle3D triangle) const;
	void handleMovement(Vector3 WSAD,int verticalMove, int mouseX, int mouseY,int dT);
	Camera();
};



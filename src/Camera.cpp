#include "Camera.h"
#include "Triangle3.h"
#include<iostream>
#include<chrono>
#include<algorithm>
extern double cameraPlaneDistance;
extern double movementSpeed;
extern int windowWidth;
extern int windowHeight;

Triangle2D Camera::triangle3to2D(Triangle3 worldTriangle) const {
	Triangle2D returnTriangle;

	for (int i = 0; i < 3; i++)
	{
		//translate to camera space
		worldTriangle[i] -= position;
		worldTriangle[i] *= rotation.transpose();

		//newrplane clipping change later
		if (worldTriangle[i].z < planePos.z) { return returnTriangle; };
	}

	for (int i = 0; i < 3; i++)
	{
		//translate to screen coords
		returnTriangle[i].x = planePos.z / worldTriangle[i].z * worldTriangle[i].x;
		returnTriangle[i].y = planePos.z / worldTriangle[i].z * worldTriangle[i].y;
	}
	return returnTriangle;
}

Triangle3& Camera::triangle3to2Dz(Triangle3& worldTriangle) const {
	for (int i = 0; i < 3; i++)
	{
		//translate to screen coords
		worldTriangle[i].x = planePos.z / worldTriangle[i].z * worldTriangle[i].x + planePos.x;
		worldTriangle[i].y = planePos.z / worldTriangle[i].z * worldTriangle[i].y + planePos.y;
		worldTriangle[i].z = worldTriangle[i].z;
	}
	return worldTriangle;
}

Triangle3& Camera::convertToCameraSpace(Triangle3& worldTriangle) const
{
	for (int i = 0; i < 3; i++)
	{
		//translate to camera space
		worldTriangle[i] -= position;
		worldTriangle[i] *= transpose;
	}
	worldTriangle.normal *= transpose;
	return worldTriangle;
}

std::vector<Triangle3> Camera::convertToCameraSpace(std::vector<Triangle3> worldTriangles) const
{
	for (int i = 0; i < worldTriangles.size(); i++)
	{
		worldTriangles[i] = convertToCameraSpace(worldTriangles[i]);
	}
	return worldTriangles;
}

//assumes triangles are in camera space
std::vector<Triangle3> Camera::backfaceCulling(std::vector<Triangle3> triangles)const
{
	std::vector<Triangle3> temp;
	for (int i = 0; i < triangles.size(); i++)
	{
		if (Vector3::dotProduct(triangles[i][0], triangles[i].normal) >= 0)
		{
			continue;
		}temp.push_back(triangles[i]);
	}
	return temp;
}

bool Camera::isTriangleFacingAway(const Triangle3& triangle) const
{
		if (Vector3::dotProduct(triangle[0], triangle.normal) >= 0)
		{
			return true;
		}
	return false;
}


std::vector<Triangle3> Camera::nearClipping(std::vector<Triangle3> triangles) const
{
	std::vector<Triangle3> temp;
	for (int i = 0; i < triangles.size(); i++)
	{
		for (int k = 0; k < 3; k++)
		{
			if (triangles[i][k].z < planePos.z)
			{
				goto skip;
			};
		}
		temp.push_back(triangles[i]);
	skip:;
	}
	return temp;
}

bool Camera::isTriangleTooNear(const Triangle3& triangle) const
{
		for (int k = 0; k < 3; k++)
		{
			if (triangle[k].z < planePos.z)
			{
				return true;
			};
		}
		return false;
}

std::vector<Triangle3> Camera::triangles3Dto2Dz(std::vector<Triangle3> triangles) const
{
	std::vector<Triangle3> temp;
	for (int i = 0; i < triangles.size(); i++)
	{
		temp.push_back(triangle3to2Dz(triangles[i]));
	}
	return temp;
}

std::vector<Triangle3> Camera::sideClipping(std::vector<Triangle3> triangles) const
{
	std::vector<Triangle3> temp;
	for (int i = 0; i < triangles.size(); i++)
	{
		for (int k = 0; k < 3; k++)
		{
			if (abs(triangles[i][k].x) > windowWidth / 2. || abs(triangles[i][k].y) > windowHeight / 2.)
			{
				clipTriangleToSides2D(triangles[i], temp);
				goto nestedcontinue;
			}
		}
		temp.push_back(triangles[i]);
	nestedcontinue:;
	}
	return temp;
}



double Camera::getPlanez()const
{
	return planePos.z;
}

Matrix Camera::getTranspose()const
{
	return transpose;
}

void Camera::calculateTranspose()
{
	transpose = rotation.transpose();
}

void Camera::clipTriangleToSides2D(Triangle3 triangle, std::vector<Triangle3>& worldTriangles) const
{
	int dx1 = abs(triangle[0].x - triangle[1].x);
	int dx2 = abs(triangle[0].x - triangle[2].x);
	int dx3 = abs(triangle[1].x - triangle[2].x);
	int boxWidth = std::max({dx1, dx2, dx3});
	int dy1 = abs(triangle[0].y - triangle[1].y);
	int dy2 = abs(triangle[0].y - triangle[2].y);
	int dy3 = abs(triangle[1].y - triangle[2].y);
	int boxHeight = std::max({ dy1, dy2, dy3 });
	int boxPosx = std::min({ triangle[0].x,triangle[1].x,triangle[2].x }) + boxWidth / 2.;
	int boxPosy = std::min({triangle[0].y, triangle[1].y, triangle[2].y}) + boxHeight / 2.;
	if (
		!(0 - windowWidth/2. < boxPosx + boxWidth/2. &&
		0 + windowWidth/2. > boxPosx - boxWidth/2. &&
		0 - windowHeight/2. < boxPosy + boxHeight/2. &&
		windowHeight/2. + 0 > boxPosy - boxHeight/2.)
		)
	{
		return;
	}
	
	worldTriangles.push_back(triangle);
}

bool Camera::is2DTriangleOutsideOfScreen(const Triangle3& triangle) const
{
	int dx1 = abs(triangle[0].x - triangle[1].x);
	int dx2 = abs(triangle[0].x - triangle[2].x);
	int dx3 = abs(triangle[1].x - triangle[2].x);
	int boxWidth = std::max({ dx1, dx2, dx3 });
	int dy1 = abs(triangle[0].y - triangle[1].y);
	int dy2 = abs(triangle[0].y - triangle[2].y);
	int dy3 = abs(triangle[1].y - triangle[2].y);
	int boxHeight = std::max({ dy1, dy2, dy3 });
	int boxPosx = std::min({ triangle[0].x,triangle[1].x,triangle[2].x }) + boxWidth / 2.;
	int boxPosy = std::min({ triangle[0].y, triangle[1].y, triangle[2].y }) + boxHeight / 2.;
	if (
		!(0 - windowWidth / 2. < boxPosx + boxWidth / 2. &&
			0 + windowWidth / 2. > boxPosx - boxWidth / 2. &&
			0 - windowHeight / 2. < boxPosy + boxHeight / 2. &&
			windowHeight / 2. + 0 > boxPosy - boxHeight / 2.)
		)
	{
		return true;
	}

	return false;
}

void Camera::handleMovement(Vector3 WSAD,int verticalMove, int mouseX, int mouseY,int dT)
{
	Vector3 movevec = WSAD * rotation;
	movevec.y = verticalMove;
	move(movevec.normalized() * movementSpeed * dT);
	extrinsicRotate(Matrix::yRotation(0.005 * mouseX));
	rotate(Matrix::xRotation(0.005 * mouseY));
}

Camera::Camera():transpose(Matrix::identityMatrix(3)) {
	planePos.x = 0;
	planePos.y = 0;
	planePos.z = cameraPlaneDistance;
}
#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include "Triangle3D.h"
#include<vector>
#include <string>

class GameObject
{
protected:
	Matrix rotation;
	Vector3 position;
	std::vector<Triangle3D> shape;

public:
	GameObject();
	void setPosition(Vector3 position);
	void setRotation(Matrix rotation);
	void rotate(Matrix rotation);
	void extrinsicRotate(Matrix rotation);
	void move(Vector3 movement);
	const std::vector<Triangle3D>& GetShape()const;
	Matrix getRotation()const;
	Vector3 getPosition()const;
	friend GameObject loadGameObject(std::string objectPath, std::string teturePath,double scale);
};

GameObject loadGameObject(std::string objectPath, std::string texturePath, double scale);
#pragma once
#include "Matrix.h"

struct Vector3 {
	double x;
	double y;
	double z;
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(const struct Vector2&);
	double length()const;
	static double distance(Vector3 vec1,Vector3 vec2);
	static Vector3 crossProduct(Vector3 vec1, Vector3 vec2);
	static double dotProduct(Vector3 vec1, Vector3 vec2);
	Vector3 crossProduct(Vector3 vec2)const;
	Vector3 normalized()const;
	Vector3& operator *=(const double& scalar);
	Vector3& operator *=(const Matrix& transformation);
	Vector3& operator +=(const Vector3& vector);
	Vector3& operator -=(const Vector3& vector);
	friend const Vector3 operator *(const Vector3& lhs, const double& rhs);
	friend const Vector3 operator *(const double& lhs, const Vector3& rhs);
	friend const Vector3 operator *(const Vector3& lhs, const Matrix& rhs);
	friend const Vector3 operator +(const Vector3& lhs, const Vector3& rhs);
	friend const Vector3 operator -(const Vector3& lhs, const Vector3& rhs);
};
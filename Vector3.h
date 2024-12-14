#pragma once
#include "Matrix.h"

struct Vector3 {
	double x;
	double y;
	double z;
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(const struct Vector2&,double z = 0);
	Vector3(const struct Vector4&);
	double length()const;
	static double distance(const Vector3& vec1,const Vector3& vec2);
	static Vector3 crossProduct(const Vector3& vec1,const Vector3& vec2);
	static double dotProduct(const Vector3& vec1, const Vector3& vec2);
	Vector3 crossProduct(const Vector3& vec2)const;
	Vector3 normalized()const;
	Vector3& operator *=(double scalar);
	Vector3& operator *=(const Matrix& transformation);
	Vector3& operator +=(const Vector3& vector);
	Vector3& operator -=(const Vector3& vector);
	friend const Vector3 operator *(const Vector3& lhs, double rhs);
	friend const Vector3 operator *(double lhs, const Vector3& rhs);
	friend const Vector3 operator *(const Vector3& lhs, const Matrix& rhs);
	friend const Vector3 operator +(const Vector3& lhs, const Vector3& rhs);
	friend const Vector3 operator -(const Vector3& lhs, const Vector3& rhs);
};
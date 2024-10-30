#pragma once
#include "Matrix.h"
struct Vector4
{
	double x;
	double y;
	double z;
	double w;
	Vector4();
	Vector4(double x, double y, double z, double w = 1);
	explicit Vector4(const struct Vector3&);
	explicit Vector4(const class Matrix&);
	double length()const;
	static double distance(Vector4 vec1, Vector4 vec2);
	static Vector4 crossProduct(Vector4 vec1, Vector4 vec2);
	static double dotProduct(Vector4 vec1, Vector4 vec2);
	Vector4 crossProduct(Vector4 vec2)const;
	Vector4 normalized()const;
	Vector4& operator *=(const double& scalar);
	Vector4& operator *=(const Matrix& transformation);
	Vector4& operator +=(const Vector4& vector);
	Vector4& operator -=(const Vector4& vector);
	friend const Vector4 operator *(const Vector4& lhs, const double& rhs);
	friend const Vector4 operator *(const double& lhs, const Vector4& rhs);
	friend const Vector4 operator *(const Vector4& lhs, const Matrix& rhs);
	friend const Vector4 operator +(const Vector4& lhs, const Vector4& rhs);
	friend const Vector4 operator -(const Vector4& lhs, const Vector4& rhs);
};


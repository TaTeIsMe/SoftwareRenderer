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
	explicit Vector4(const struct Vector3&,double w = 1);
	explicit Vector4(const struct Vector2&,double z = 0, double w = 1);
	double length()const;
	static double distance(const Vector4& vec1, const Vector4& vec2);
	static Vector4 crossProduct(const Vector4& vec1,const Vector4& vec2);
	static double dotProduct(const Vector4& vec1,const Vector4& vec2);
	Vector4 crossProduct(const Vector4& vec2)const;
	Vector4 normalized()const;
	Vector4& operator *=(double scalar);
	Vector4& operator *=(const Matrix& transformation);
	Vector4& operator +=(const Vector4& vector);
	Vector4& operator -=(const Vector4& vector);
	friend const Vector4 operator *(const Vector4& lhs,double rhs);
	friend const Vector4 operator *(double lhs, const Vector4& rhs);
	friend const Vector4 operator *(const Vector4& lhs, const Matrix& rhs);
	friend const Vector4 operator +(const Vector4& lhs, const Vector4& rhs);
	friend const Vector4 operator -(const Vector4& lhs, const Vector4& rhs);
};


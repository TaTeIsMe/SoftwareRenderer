#pragma once
#include"Matrix.h"
struct Vector2
{
	int x;
	int y;
	Vector2();
	Vector2(int x, int y);
	Vector2(const struct Vector3&);
	Vector2(const struct Vector4&);
	Vector2 normalized() const;
	bool isLeftOfLine(const Vector2& lineV1, const Vector2& lineV2);
	bool isRightOfLine(const Vector2& lineV1, const Vector2& lineV2);
	double length() const;
	static Vector2 lineIntersection(const Vector2& line1v1, const Vector2& line1v2, const Vector2& line2v1, const Vector2& line2v2 );
	Vector2& operator *=(double scalar);
	Vector2& operator *=(const Matrix& transformation);
	Vector2& operator +=(const Vector2& vector);
	Vector2& operator -=(const Vector2& vector);
	friend const Vector2 operator *(const Vector2& lhs, double rhs);
	friend const Vector2 operator *(double lhs, const Vector2& rhs);
	friend const Vector2 operator *(const Vector2& lhs, const Matrix& rhs);
	friend const Vector2 operator +(const Vector2& lhs, const Vector2& rhs);
	friend const Vector2 operator -(const Vector2& lhs, const Vector2& rhs);
};


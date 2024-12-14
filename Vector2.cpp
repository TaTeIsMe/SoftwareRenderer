#include "Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include<cmath>
#include<iostream>
Vector2::Vector2():x(0),y(0)
{
}

Vector2::Vector2(int x, int y):x(x),y(y)
{
}

Vector2::Vector2(const Vector3& vector3):x(vector3.x), y(vector3.y)
{
}

Vector2::Vector2(const Vector4& vector4):x(vector4.x),y(vector4.y)
{
}

Vector2 Vector2::normalized()const
{
	if (length() == 0)return Vector2(this->x, this->y);
	return Vector2(x / length(), y / length());
}

bool Vector2::isLeftOfLine(const Vector2& lineV1, const Vector2& lineV2)
{
	return ((lineV2.x-lineV1.x)*(y-lineV1.y)-(lineV2.y - lineV1.y)*(x-lineV1.x))>0;
}

bool Vector2::isRightOfLine(const Vector2& lineV1, const Vector2& lineV2)
{
	return ((lineV2.x - lineV1.x) * (y - lineV1.y) - (lineV2.y - lineV1.y) * (x - lineV1.x)) < 0;
}

double Vector2::length()const
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::lineIntersection(const Vector2& line1v1, const Vector2& line1v2, const Vector2& line2v1, const Vector2& line2v2)
{
	float denx = ((line1v1.x - line1v2.x) * (line2v1.y - line2v2.y) - (line1v1.y - line1v2.y) * (line2v1.x - line2v2.x));
	float deny = ((line1v1.x - line1v2.x) * (line2v1.y - line2v2.y) - (line1v1.y - line1v2.y) * (line2v1.x - line2v2.x));
	float x = ((line1v1.x * line1v2.y - line1v1.y * line1v2.x) * (line2v1.x - line2v2.x) - (line1v1.x - line1v2.x) * (line2v1.x * line2v2.y - line2v1.y * line2v2.x)) / denx ;
	float y = ((line1v1.x * line1v2.y - line1v1.y * line1v2.x) * (line2v1.y - line2v2.y) - (line1v1.y - line1v2.y) * (line2v1.x * line2v2.y - line2v1.y * line2v2.x)) / deny ;
	return Vector2(x,y);
}

Vector2& Vector2::operator*=(double scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2& Vector2::operator*=(const Matrix& transformation)
{
	if (transformation.getHeight() != 2 || transformation.getWidth() != 2) {
		std::cerr << "Vector3 can only be multiplied by 2x2 matrix";
	}
	double tempx = x;
	double tempy = y;
	x = transformation[0][0] * tempx + transformation[0][1] * tempy;
	y = transformation[1][0] * tempx + transformation[1][1] * tempy;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& vector)
{
	x += vector.x;
	y += vector.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;
	return *this;
}

const Vector2 operator*(const Vector2& lhs, double rhs)
{
	return Vector2(lhs) *= rhs;
}

const Vector2 operator*(double lhs, const Vector2& rhs)
{
	return Vector2(rhs)*=lhs;
}

const Vector2 operator*(const Vector2& lhs, const Matrix& rhs)
{
	return Vector2(lhs)*=rhs;
}

const Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs)+=rhs;
}

const Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs)-=rhs;
}

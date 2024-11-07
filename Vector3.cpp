#include "Vector3.h"
#include<iostream>
#include"Vector2.h"
#include<cmath>

Vector3& Vector3::operator *=(const double& scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
};

Vector3& Vector3::operator *=(const Matrix& transformation) {
	if (transformation.getHeight() != 3 || transformation.getWidth() != 3) {
		std::cerr << "Vector3 can only be multiplied by 3x3 matrix";
	}
	double tempx = x;
	double tempy = y;
	double tempz = z;
	x = transformation[0][0] * tempx + transformation[0][1] * tempy + transformation[0][2] * tempz;
	y = transformation[1][0] * tempx + transformation[1][1] * tempy + transformation[1][2] * tempz;
	z = transformation[2][0] * tempx + transformation[2][1] * tempy + transformation[2][2] * tempz;
	return *this;
}

Vector3 Vector3::normalized()const
{
	if (length() == 0)return Vector3(this->x,this->y,this->z);
	return Vector3(x/length(),y/length(),z/length());
}
;

Vector3& Vector3::operator +=(const Vector3& vector) {
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
};

Vector3& Vector3::operator -=(const Vector3& vector) {
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
};

const Vector3 operator *(const Vector3& lhs, const double& rhs) {
	return Vector3(lhs) *= rhs;
};

const Vector3 operator *(const double& lhs, const Vector3& rhs) {
	return Vector3(rhs) *= lhs;
};

const Vector3 operator *(const Vector3& lhs, const Matrix& rhs) {
	return Vector3(lhs) *= rhs;
};

const Vector3 operator +(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(lhs) += rhs;
};

const Vector3 operator -(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(lhs) -= rhs;
};

Vector3::Vector3():x(0),y(0),z(0)
{
}

Vector3::Vector3(double x, double y, double z):x(x),y(y),z(z) {
}

Vector3::Vector3(const Vector2& vector2):x(vector2.x),y(vector2.y),z(0)
{
}

double Vector3::length()const
{
	return sqrt(x* x+ y* y+ z* z);
}

double Vector3::distance(Vector3 vec1, Vector3 vec2)
{
	return (vec1 - vec2).length();
}

Vector3 Vector3::crossProduct(Vector3 vec1, Vector3 vec2)
{
	return Vector3((vec1.y*vec2.z-vec1.z*vec2.y),-(vec1.x*vec2.z-vec1.z*vec2.x),(vec1.x*vec2.y-vec1.y*vec2.x));
}

double Vector3::dotProduct(Vector3 vec1, Vector3 vec2)
{
	return vec1.x*vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vector3 Vector3::crossProduct(Vector3 vec2) const
{
	return crossProduct(*this,vec2);
}

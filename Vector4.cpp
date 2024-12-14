#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include<cmath>
#include<iostream>
Vector4::Vector4() :x(0),y(0),z(0),w(1)
{
}

Vector4::Vector4(double x, double y, double z, double w ) :x(x), y(y), z(z), w(w){

}

Vector4::Vector4(const Vector3& vector3,double w) :x(vector3.x), y(vector3.y),z(vector3.z),w(w)
{
}

Vector4::Vector4(const Vector2& vector2, double z, double w): x(vector2.x), y(vector2.y), z(z), w(w)
{
}

double Vector4::length() const
{
	return sqrt(x * x + y * y + z * z);
}

double Vector4::distance(const Vector4& vec1,const Vector4& vec2)
{
	return (vec1 - vec2).length();
}


double Vector4::dotProduct(const Vector4& vec1,const Vector4& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vector4& Vector4::operator-=(const Vector4& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
	return *this;
}

Vector4& Vector4::operator +=(const Vector4& vector) {
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
	return *this;
};

Vector4& Vector4::operator *=(double scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
};

Vector4& Vector4::operator *=(const Matrix& transformation) {
	if (transformation.getHeight() != 4 || transformation.getWidth() != 4) {
		std::cerr << "Vector4 can only be multiplied by 4x4 matrix";
	}
	double tempx = x;
	double tempy = y;
	double tempz = z;
	double tempw = w;
	x = transformation[0][0] * tempx + transformation[0][1] * tempy + transformation[0][2] * tempz + transformation[0][3] * tempw;
	y = transformation[1][0] * tempx + transformation[1][1] * tempy + transformation[1][2] * tempz + transformation[1][3] * tempw;
	z = transformation[2][0] * tempx + transformation[2][1] * tempy + transformation[2][2] * tempz + transformation[2][3] * tempw;
	w = transformation[3][0] * tempx + transformation[3][1] * tempy + transformation[3][2] * tempz + transformation[3][3] * tempw;
	return *this;
}

const Vector4 operator *(const Vector4& lhs, double rhs) {
	return Vector4(lhs) *= rhs;
};

const Vector4 operator *(double lhs, const Vector4& rhs) {
	return Vector4(rhs) *= lhs;
};

const Vector4 operator *(const Vector4& lhs, const Matrix& rhs) {
	return Vector4(lhs) *= rhs;
};

const Vector4 operator +(const Vector4& lhs, const Vector4& rhs) {
	return Vector4(lhs) += rhs;
};

const Vector4 operator -(const Vector4& lhs, const Vector4& rhs) {
	return Vector4(lhs) -= rhs;
};

Vector4 Vector4::crossProduct(const Vector4& vec1,const  Vector4& vec2)
{
	return Vector4((vec1.y * vec2.z - vec1.z * vec2.y), -(vec1.x * vec2.z - vec1.z * vec2.x), (vec1.x * vec2.y - vec1.y * vec2.x));
}

Vector4 Vector4::crossProduct(const Vector4& vec2) const
{
	return crossProduct(*this, vec2);
}

Vector4 Vector4::normalized() const
{
	if (length() == 0)return Vector4(this->x, this->y, this->z);
	return Vector4(x / length(), y / length(), z / length(),w/length());
}

#include "Vector4.h"
#include "Vector3.h"
#include<cmath>
#include<iostream>
Vector4::Vector4() :x(0),y(0),z(0),w(1)
{
}

Vector4::Vector4(double x, double y, double z, double w ) :x(x), y(y), z(z), w(w){

}

Vector4::Vector4(const Vector3& vector3) :x(vector3.x), y(vector3.y),z(vector3.z),w(1)
{
}

Vector4::Vector4(const Matrix& matrix)
{
	if(matrix.getWidth() != 4 || matrix.getHeight()!=4)std::cerr << "Can't cast a non 4x4 matrix to a 4D vector";
	x = matrix[0][3];
	y = matrix[1][3];
	z = matrix[2][3];
	w = 1;
}

double Vector4::length() const
{
	return sqrt(x * x + y * y + z * z);
}

double Vector4::distance(Vector4 vec1, Vector4 vec2)
{
	return (vec1 - vec2).length();
}


double Vector4::dotProduct(Vector4 vec1, Vector4 vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

//don't use this, use translation transformation instead
Vector4& Vector4::operator-=(const Vector4& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

//don't use this, use translation transformation instead
Vector4& Vector4::operator +=(const Vector4& vector) {
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
};

//don't use this, use scaling transformation instead
Vector4& Vector4::operator *=(const double& scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
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

//don't use this, use scaling transformation instead
const Vector4 operator *(const Vector4& lhs, const double& rhs) {
	return Vector4(lhs) *= rhs;
};

//don't use this, use scaling transformation instead
const Vector4 operator *(const double& lhs, const Vector4& rhs) {
	return Vector4(rhs) *= lhs;
};

const Vector4 operator *(const Vector4& lhs, const Matrix& rhs) {
	return Vector4(lhs) *= rhs;
};
//don't use this, use translation transformation instead
const Vector4 operator +(const Vector4& lhs, const Vector4& rhs) {
	return Vector4(lhs) += rhs;
};
//don't use this, use translation transformation instead
const Vector4 operator -(const Vector4& lhs, const Vector4& rhs) {
	return Vector4(lhs) -= rhs;
};

Vector4 Vector4::crossProduct(Vector4 vec1, Vector4 vec2)
{
	return Vector4((vec1.y * vec2.z - vec1.z * vec2.y), -(vec1.x * vec2.z - vec1.z * vec2.x), (vec1.x * vec2.y - vec1.y * vec2.x));
}

Vector4 Vector4::crossProduct(Vector4 vec2) const
{
	return crossProduct(*this, vec2);
}

//confusing name. this makes the lenght of the 3D vector 1
Vector4 Vector4::normalized() const
{
	if (length() == 0)return Vector4(this->x, this->y, this->z);
	return Vector4(x / length(), y / length(), z / length());
}

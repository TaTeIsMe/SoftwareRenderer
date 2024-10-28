#include "Vector4.h"
#include "Vector3.h"
#include<cmath>
Vector4::Vector4() :vectorMatrix(Matrix::identityMatrix(4))
{
}

Vector4::Vector4(double x, double y, double z) :vectorMatrix(Matrix::identityMatrix(4)) {
	vectorMatrix[0][3] = x;
	vectorMatrix[1][3] = y;
	vectorMatrix[2][3] = z;
}

Vector4::Vector4(const Vector3& vector3) :vectorMatrix(Matrix::identityMatrix(4))
{
	vectorMatrix[0][3] = vector3.x;
	vectorMatrix[1][3] = vector3.y;
	vectorMatrix[2][3] = vector3.z;
}

const double& Vector4::x() const
{
	return vectorMatrix[0][3];
}

const double& Vector4::y() const
{
	return vectorMatrix[1][3];
}

const double& Vector4::z() const
{
	return vectorMatrix[2][3];
}

const double& Vector4::w() const
{
	return vectorMatrix[3][3];
}

double& Vector4::x()
{
	return vectorMatrix[0][3];
}

double& Vector4::y()
{
	return vectorMatrix[1][3];
}

double& Vector4::z()
{
	return vectorMatrix[2][3];
}

double& Vector4::w()
{
	return vectorMatrix[3][3];
}

double Vector4::length() const
{
	return sqrt(x() * x() + y() * y() + z() * z());
}

double Vector4::distance(Vector4 vec1, Vector4 vec2)
{
	return (vec1 - vec2).length();
}

Vector4 Vector4::crossProduct(Vector4 vec1, Vector4 vec2)
{
	return Vector4();
}

double Vector4::dotProduct(Vector4 vec1, Vector4 vec2)
{
	return vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
}

//since w isn't modified don't use before normalization
Vector4& Vector4::operator-=(const Vector4& vector)
{
	x() -= vector.x();
	y() -= vector.y();
	z() -= vector.z();
	return *this;
}

Vector4& Vector4::operator +=(const Vector4& vector) {
	vectorMatrix *= vector.vectorMatrix;
	return *this;
};

//since w isn't modified don't use before normalization
Vector4& Vector4::operator *=(const double& scalar) {
	x() *= scalar;
	y() *= scalar;
	z() *= scalar;
	return *this;
};

Vector4& Vector4::operator *=(const Matrix& transformation) {
	vectorMatrix *= transformation;
	return *this;
}

const Vector4 operator *(const Vector4& lhs, const double& rhs) {
	return Vector4(lhs) *= rhs;
};

const Vector4 operator *(const double& lhs, const Vector4& rhs) {
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

Vector4 Vector4::crossProduct(Vector4 vec1, Vector4 vec2)
{
	return Vector3((vec1.y() * vec2.z() - vec1.z() * vec2.y()), -(vec1.x() * vec2.z() - vec1.z() * vec2.x()), (vec1.x() * vec2.y() - vec1.y() * vec2.x()));
}

Vector4 Vector4::crossProduct(Vector4 vec2) const
{
	return crossProduct(*this, vec2);
}

//confusing name. this makes the lenght of the 3D vector 1
Vector4 Vector4::normalized() const
{
	if (length() == 0)return Vector4(this->x(), this->y(), this->z());
	return Vector4(x() / length(), y() / length(), z() / length());
}

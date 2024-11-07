#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include "Vector4.h"
struct RigidBody :public Matrix
{
	RigidBody();	
	RigidBody(const Matrix& rotation, const Vector3& position);
	RigidBody(const Matrix& rotation, const Vector4& position);
	explicit RigidBody(const class Matrix&);
	Matrix getRotationMatrix()const;
	Matrix getTranslationMatrix()const;
	Matrix getInverse()const;
};


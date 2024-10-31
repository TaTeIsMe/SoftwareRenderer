#include "RigidBody.h"
#include "Vector4.h"
#include<iostream>
RigidBody::RigidBody(): Matrix(Matrix::identityMatrix(4))
{
}

RigidBody::RigidBody(const Matrix& rotation, const Vector3& position) :Matrix(Matrix::identityMatrix(4))
{
	if (rotation.getHeight() != 3 || rotation.getWidth() != 3) std::cerr << "this call of RigidBody needs the matrix to be 3x3";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			insides[i][j] = rotation[i][j];
		}
	}
	insides[0][3] = position.x;
	insides[1][3] = position.y;
	insides[2][3] = position.z;
}

RigidBody::RigidBody(const Matrix& rotation, const Vector4& position): Matrix(identityMatrix(4))
{
	if (rotation.getHeight() != 4 || rotation.getWidth() != 4) std::cerr << "this call of RigidBody needs the matrix to be 4x4";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			insides[i][j] = rotation[i][j];
		}
	}
	insides[0][3] = position.x;
	insides[1][3] = position.y;
	insides[2][3] = position.z;
}

Matrix RigidBody::getRotationMatrix()const
{
	Matrix rotationMatrix = Matrix::identityMatrix(4);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rotationMatrix[i][j] = insides[i][j];
		}
		
	}
	return rotationMatrix;
}

Matrix RigidBody::getTranslationMatrix()const
{
	Matrix translationMatrix = Matrix::identityMatrix(4);
	translationMatrix[0][3] = insides[0][3];
	translationMatrix[1][3] = insides[1][3];
	translationMatrix[2][3] = insides[2][3];
	return translationMatrix;
}

Matrix RigidBody::getInverse() const
{
	Matrix rotationInverse = getRotationMatrix().transpose();
	Vector4 translationInverse = Vector4(getTranslationMatrix()) * -1;
	translationInverse *= rotationInverse;
	return RigidBody(rotationInverse,translationInverse);

}

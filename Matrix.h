#pragma once
#include <initializer_list>
class Matrix
{
protected:
	int height;
	int width;
	double **insides;
public:
	Matrix(int rows, int cols);
	Matrix(const Matrix& other);
	Matrix(std::initializer_list<std::initializer_list<double>> init);
	Matrix & operator=(Matrix other);
	friend void swap(Matrix& first, Matrix& second);
	~Matrix();
	Matrix & operator *=(const Matrix& matrix);
	double *&operator [](int index) const;
	friend const Matrix operator *( const Matrix& lhs, const Matrix& rhs);
	const int& getHeight() const;
	const int& getWidth() const;
	Matrix inverse()const;
	Matrix transpose()const;
	void comout()const;
	static Matrix translation4(double x, double y, double z);
	static Matrix xRotation(double angle);
	static Matrix yRotation(double angle);
	static Matrix zRotation(double angle);
	static Matrix xRotation4(double angle);
	static Matrix yRotation4(double angle);
	static Matrix zRotation4(double angle);
	static Matrix identityMatrix(int size);
};



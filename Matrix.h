#pragma once
class Matrix
{
private:
	int height;
	int width;
	double **insides;
public:
	Matrix(int rows, int cols);
	Matrix(const Matrix& other);
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
	static Matrix xRotation(double angle);
	static Matrix yRotation(double angle);
	static Matrix zRotation(double angle);
	static Matrix identityMatrix(int size);
};



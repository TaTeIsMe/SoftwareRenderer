#pragma once
class Matrix
{
private:
	int height;
	int width;
	double **insides;
public:
	Matrix(const int& rows, const int& cols);
	Matrix(const Matrix& other);
	Matrix & operator=(Matrix other);
	friend void swap(Matrix& first, Matrix& second);
	~Matrix();
	Matrix & operator *=(const Matrix& matrix);
	double *&operator [](const int& index) const;
	friend const Matrix operator *( const Matrix& lhs, const Matrix& rhs);
	const int& getHeight() const;
	const int& getWidth() const;
	Matrix inverse()const;
	Matrix transpose()const;
	void comout()const;
	static Matrix xRotation(const double& angle);
	static Matrix yRotation(const double& angle);
	static Matrix zRotation(const double& angle);
	static Matrix identityMatrix(const int& size);
};



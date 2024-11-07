#include "Matrix.h"
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
Matrix::Matrix( int height, int width)
{
    this->height = height;
    this->width = width;
    insides = new double* [height];
    for (int i = 0; i < height; i++)
    {
        insides[i] = new double[width]();
    }
}

Matrix::Matrix(const Matrix& other)
{
    height = other.height;
    width = other.width;
    insides = new double* [height];
    for (int i = 0; i < other.height; i++)
    {
        insides[i] = new double[other.width];
    }
    for (int i = 0; i < other.height; i++)
    {
        for (int j = 0; j < other.width; j++)
        {
            insides[i][j] = other[i][j];
        }
    }
}

Matrix & Matrix::operator=(Matrix other)
{
    swap(*this,other);
    return *this;
}

double*& Matrix::operator [] (int index) const
{
    return insides[index];
}

Matrix & Matrix::operator *=(const Matrix &matrix) {
    if (height != matrix.width)
    {
        std::cerr << "couldn't multiply matrices";
        return *this;
    }
    else
    {
        Matrix temp(height, matrix.width);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < matrix.width; j++)
                for (int k = 0; k < width; k++)
                {
                    temp[i][j] += insides[i][k] * matrix[k][j];
                }
        *this = temp;
        return *this;
    }
};

const Matrix operator*(const Matrix& lhs,const Matrix& rhs) {
    return (Matrix(lhs) *= rhs);
}

const int& Matrix::getHeight()const {
    return height;
}

const int& Matrix::getWidth()const {
    return width;
}

Matrix Matrix::inverse()const {
    //GaussJ
    if (height != width) { std::cerr << "badmatrix!!"; }
    Matrix identity(identityMatrix(height));
    Matrix temp(*this);
    for (int i = 0; i < height; i++)
    {
        for (int j = width-1; j > i-1; j--)
        {
            if(j!=i)temp[i][j] = temp[i][j] / temp[i][i];
            identity[i][j] = identity[i][j] / temp[i][i];
        }
        for (int j = 0; j < height; j++)
        {
            if (j != i) {
                for (int k = i; k < width; k++)
                {
                    temp[j][k] = temp[j][k] - temp[j][i] * temp[i][k];
                    identity[j][k] = identity[j][k] - identity[j][i] * temp[i][k];
                }
            }
        }
    }
    return identity;
}

Matrix Matrix::transpose() const
{
    Matrix temp(width,height);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            temp[i][j] = insides[j][i];
        }
    }
    return temp;
}

void Matrix::comout() const
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            std::cout << insides[i][j] << "   ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix::~Matrix()
{
    for (int i = 0; i < height; i++)
        delete[] insides[i];
    delete[] insides;

}

void swap(Matrix& first, Matrix& second) {
    using std::swap;
    swap(first.height,second.height);
    swap(first.width,second.width);
    swap(first.insides,second.insides);
};

Matrix Matrix::xRotation( double angle) {
    Matrix returnMatrix(3,3);
    returnMatrix[0][0] = 1;
    returnMatrix[1][1] = cos(angle);
    returnMatrix[1][2] = -sin(angle);
    returnMatrix[2][1] = sin(angle);
    returnMatrix[2][2] = cos(angle);
    return returnMatrix;
};

Matrix Matrix::yRotation( double angle){
    Matrix returnMatrix(3, 3);
    returnMatrix[0][0] = cos(angle);
    returnMatrix[0][2] = sin(angle);
    returnMatrix[1][1] = 1;
    returnMatrix[2][0] = -sin(angle);
    returnMatrix[2][2] = cos(angle);
    return returnMatrix;
};

Matrix Matrix::zRotation( double angle){
    Matrix returnMatrix(3, 3);
    returnMatrix[0][0] = cos(angle);
    returnMatrix[0][1] = -sin(angle);
    returnMatrix[1][0] = sin(angle);
    returnMatrix[1][1] = cos(angle);
    returnMatrix[2][2] = 1;
    return returnMatrix;
}
Matrix Matrix::xRotation4D(double angle)
{
    Matrix returnMatrix(identityMatrix(4));
    returnMatrix[1][1] = cos(angle);
    returnMatrix[1][2] = -sin(angle);
    returnMatrix[2][1] = sin(angle);
    returnMatrix[2][2] = cos(angle);
    return returnMatrix;
}
;

Matrix Matrix::yRotation4D(double angle)
{
    Matrix returnMatrix(identityMatrix(4));
    returnMatrix[0][0] = cos(angle);
    returnMatrix[0][2] = sin(angle);
    returnMatrix[2][0] = -sin(angle);
    returnMatrix[2][2] = cos(angle);
    return returnMatrix;
}

Matrix Matrix::zRotation4D(double angle)
{
    Matrix returnMatrix(identityMatrix(4));
    returnMatrix[0][0] = cos(angle);
    returnMatrix[0][1] = -sin(angle);
    returnMatrix[1][0] = sin(angle);
    returnMatrix[1][1] = cos(angle);
    return returnMatrix;
}

Matrix Matrix::identityMatrix( int size) {
    Matrix returnMatrix(size, size);
    for (int i = 0; i < size; i++)
    {
        returnMatrix[i][i] = 1;
    }
    return returnMatrix;
}
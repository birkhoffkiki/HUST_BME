#include"stdafx.h"
#include"Matrix.h"
#include<iostream>
#include<iomanip>
#include"mat.h"
using namespace std;
Matrix::Matrix()
{
	this->col = 0;
	this->row = 0;
	this->value = NULL;
}
Matrix::Matrix(double * data, int row, int col)
{
	this->row = row;
	this->col = col;
	this->value = new double[row*col];
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < col;j++)
		{
			*(value + i*col + j) = *(data + i*col + j);
		}
	}
}
Matrix::Matrix(int row, int col)
{
	this->row = row;
	this->col = col;
	this->value = new double[row*col];
}
Matrix::Matrix(const Matrix & C)
{
	this->row = C.row;
	this->col = C.col;
	this->value = new double[C.row*C.col];
	for (int i = 0;i < C.row;i++)
	{
		for (int j = 0;j < C.col;j++)
		{
			*(value + i*C.col + j) = *(C.value + i*C.col + j);
		}
	}
}		//拷贝构造函数
Matrix & Matrix::operator=(const Matrix & obj)
{
	if (this->value)
		delete this->value;		//释放原内存区域
	this->row = obj.row;
	this->col = obj.col;
	this->value = new double[obj.col*obj.row];
	for (int i = 0;i < obj.row;i++)
	{
		for (int j = 0;j < obj.col;j++)
		{
			*(this->value + i*obj.col + j) = *(obj.value + i*obj.col + j);
		}
	}
	return *this;
}		//赋值运算符重载
Matrix Matrix::T()
{
	Matrix result(this->col,this->row);
	for (int i = 0;i < row;i++)
	{
		for (int j = i;j < col;j++)
		{
			*(result.value + j*row+i) = *(this->value + i*col + j);
			*(result.value + i*col+j) = *(this->value + j*row + i);
		}
	}
	return result;
}

void Matrix::set(int row, int col, double v)
{
	if (row < this->row && row >= 0 && col < this->col && col >= 0)
	{
		*(this->value + row*this->col + col) = v;
	}
}

double Matrix::get(int row, int col)
{
	if (row >= 0 && row < this->row && col >= 0 && col < this->col)
	{
		return *(this->value + row*this->col + col);
	}
	else
		return 0;
}

void Matrix::print()
{
	for (int i = 0;i < this->row;i++)
	{
		for (int j = 0;j < this->col;j++)
		{
			cout << setw(8)<<*(this->value + i*this->col + j) << ',';
		}
		cout << endl;
	}
}

Matrix::~Matrix()
{
	delete [] value;
}

Matrix operator+(const Matrix & n, const Matrix & m)
{
	Matrix result;
	mat op;
	result = op.add(n, m);
	return result;
}

Matrix operator+(const double n, const Matrix & m)
{
	mat op;
	return op.add(n,m);
}

Matrix operator+(const Matrix & n, const double m)
{
	mat op;
	return op.add(n,m);
}

Matrix operator-(const Matrix & n, const Matrix & m)
{
	mat op;
	return op.sub(n,m);
}

Matrix operator-(const Matrix & n, const double m)
{
	mat op;
	return op.sub(n,m);
}

Matrix operator-(const double m, const Matrix & n)
{
	mat op;
	return op.sub(m,n);
}

Matrix operator*(const Matrix & n, const Matrix & m)
{
	mat op;
	return op.mul(n,m);
}

Matrix operator*(const double n, const Matrix & m)
{
	mat op;
	return op.mul(n, m);
}

Matrix operator*(const Matrix & n, const double m)
{
	mat op;
	return op.mul(n,m);
}

Matrix operator/(const Matrix & n, const Matrix & m)
{
	mat op;
	return op.div(n,m);
}

Matrix operator/(const Matrix & n, const double m)
{
	mat op;
	return op.div(n,m);
}

Matrix operator/(const double n, const Matrix & m)
{
	mat op;
	return op.div(n,m);
}

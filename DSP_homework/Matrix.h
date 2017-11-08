#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
	int row;
	int col;
	double * value;
	Matrix();
	Matrix(double * data,int row,int col);
	Matrix(int row, int col);
	Matrix(const Matrix & C);			//拷贝构造函数
	Matrix & operator=(const Matrix &obj);
	~Matrix();

	Matrix T();		//转置函数,不改变原矩阵，返回转置矩阵。
	void set(int row, int col, double v);			//修改矩阵的值，下标从0开始。
	void print();		//输出函数，输出矩阵。

};


 #endif // !MATRIX_H 

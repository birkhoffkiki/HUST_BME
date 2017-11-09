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
	~Matrix();

	Matrix & operator=(const Matrix &obj);

	//*****双目运算符重载为友元函数*******
	friend Matrix operator + (const Matrix &n, const Matrix &m); 	
	friend Matrix operator + (const double n, const Matrix &m);
	friend Matrix operator + (const Matrix &n, const double m);

	friend Matrix operator - (const Matrix &n, const Matrix &m);
	friend Matrix operator - (const Matrix &n, const double m);
	friend Matrix operator - (const double m, const Matrix &n);

	friend Matrix operator * (const Matrix &n, const Matrix &m);			//矩阵对应元素乘。
	friend Matrix operator * (const double n, const Matrix &m);
	friend Matrix operator * (const Matrix &n, const double m);				

	friend Matrix operator / (const Matrix &n, const Matrix &m);
	friend Matrix operator / (const Matrix &n, const double m);
	friend Matrix operator / (const double n, const Matrix &m);
	//*****双目运算符重载为友元函数*******


	Matrix T();		//转置函数,不改变原矩阵，返回转置矩阵。
	void set(int row, int col, double v);			//修改矩阵的值，下标从0开始。
	double get(int row, int col);
	void print();		//输出函数，输出矩阵。

};


 #endif // !MATRIX_H 

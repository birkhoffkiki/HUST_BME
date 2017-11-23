#pragma once
#include"Matrix.h"
class mat
{
public:

	static double pi;

	Matrix conv(Matrix n, Matrix m);		//一维卷积
	Matrix matmul(Matrix n, Matrix m);		//矩阵乘法
	
	//******下列运算符已重载*********
	Matrix add(Matrix n, Matrix m);			//矩阵加法
	Matrix add(Matrix n, double m);
	Matrix add(double m, Matrix n);			//矩阵每个元素加m;
	Matrix sub(Matrix n, Matrix m);			//矩阵减法
	Matrix sub(Matrix n, double m);
	Matrix sub(double m, Matrix n);			//每个元素减m.

	Matrix mul(Matrix n, Matrix m);			//对应元素乘法，
	Matrix mul(Matrix n, double m);			
	Matrix mul(double m, Matrix n);			//标乘，给矩阵所有元素乘以一个标量；
	Matrix div(Matrix n, Matrix m);			//对应元素除法
	Matrix div(Matrix n, double m);			//矩阵所有元素除以某一标量
	Matrix div(double m, Matrix n);
	//*******上面运算符已重载***********

	Matrix tanm(Matrix n);
	Matrix sinm(Matrix n);
	Matrix cosm(Matrix n);				//计算矩阵的sin,cos
	Matrix powm(Matrix n, double y);		//计算矩阵元素的n次方，y做指数。
	Matrix powm(double y, Matrix n);		//y做底数，矩阵做指数。
	Matrix expm(Matrix n);					//计算e的矩阵元素次方，返回e的矩阵次方。
	Matrix sqrtm(Matrix n);					//对矩阵开方
	double sum(Matrix n);					//求和函数，返回double.

	Matrix seq(double init, double step, double end);		//产生一个序列，init 开始，步长为step，end结束,不包含end，返回值为行向量。
	Matrix zeros(int row, int col);					//matlab zeros
	Matrix ones(int row, int col);					//matlab ones
	Matrix randn(int row, int col, int seed = 0);	//产生0-1随机数矩阵。

	Matrix DFT(Matrix n, int type=0);		//计算离散时间傅里叶变换，type=0,返回幅度，type=1,返回相位。n为行向量。

	Matrix reverse(Matrix n);			//一维数组反序，多维返回空矩阵。
};

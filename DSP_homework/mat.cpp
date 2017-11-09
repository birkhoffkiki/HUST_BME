#include "stdafx.h"
#include "mat.h"
#include<stdlib.h>
#include<math.h>
using namespace std;

double mat::pi = 3.141592654;

Matrix mat::conv(Matrix n, Matrix m)
{
	if (n.row == 1 && m.row == 1 || n.col==1 && m.col == 1)
	{	
		int length = n.row*n.col + m.row * m.col - 1;
		int ln = n.row*n.col;			//数组n的长度
		int lm = m.row*m.col;			
		int maxmultimes = abs(ln-lm)+1;
		double *p = new double[length];
		double sum = 0;
		if (ln<=lm)			//n的长度小于m
		{
			for (int i1 = 0;i1 < ln-1;i1++)
			{
				for(int j1=0;j1<=i1;j1++)
				{
					sum = sum + *(m.value + j1)**(n.value +(i1- j1));
				}
				*(p + i1) = sum;
				sum = 0;
			}
			for (int i2 = ln - 1;i2 < ln -1+ maxmultimes;i2++)
			{
				for (int j2 = 0;j2 < ln;j2++)
				{
					sum = sum + *(m.value + j2+i2-(ln-1))**(n.value + (ln-j2-1));
				}
				*(p + i2) = sum;
				sum = 0;
			}
			for (int i3 = maxmultimes + ln - 1;i3 < length;i3++)
			{
				for (int j3 = 0; j3 <length-i3; j3++)
				{
					sum = sum + *(m.value + i3-(maxmultimes+ln-1)+j3)**(n.value + ln-1-j3);
				}
				*(p + i3) = sum;
				sum = 0;
			}
		}
		if (ln > lm)
		{
			for (int i1 = 0;i1 < lm - 1;i1++)
			{
				for (int j1 = 0;j1 <= i1;j1++)
				{
					sum = sum + *(n.value + j1)**(m.value + (i1 - j1));
				}
				*(p + i1) = sum;
				sum = 0;
			}
			for (int i2 = lm - 1;i2 < lm - 1 + maxmultimes;i2++)
			{
				for (int j2 = 0;j2 < lm;j2++)
				{
					sum = sum + *(n.value + j2 + i2 - (lm - 1))**(m.value + (lm- j2 - 1));
				}
				*(p + i2) = sum;
				sum = 0;
			}
			for (int i3 = maxmultimes + lm - 1;i3 < length;i3++)
			{
				for (int j3 = 0; j3 <length - i3; j3++)
				{
					sum = sum + *(n.value + i3 - (maxmultimes + lm - 1) + j3)**(m.value + lm - 1 - j3);
				}
				*(p + i3) = sum;
				sum = 0;
			}
		}
		if (n.row == 1)
		{
			Matrix result = Matrix(p, n.row, length);
			delete p;
			return result;
		}
		else
		{
			Matrix result = Matrix(p, length, n.col);
			delete p;
			return result;
		}
	}
	else
		return Matrix();
}

Matrix mat::matmul(Matrix n, Matrix m)
{

	Matrix result(n.row,m.col);
	if (n.col != m.row)
	{
		exit(0);
	}
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < m.col;j++)
		{
			double sum = 0;
			for (int counter = 0; counter < n.col;counter++)
			{
				sum = sum + *(n.value + i*n.col + counter)*(*(m.value + counter*m.col+j));
			}
			*(result.value + i*m.col + j) = sum;
		}
	}
	return result;
}

Matrix mat::add(Matrix n, Matrix m)
{
	if (n.row == m.row && n.col == m.col)
	{
		Matrix sum = Matrix(n.row, n.col);
		for (int i = 0;i < n.row;i++)
		{
			for (int j = 0;j < n.col;j++)
			{
				*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) + *(m.value + i*n.col + j);
			}
		}
		return sum;
	}
	else
		return Matrix();
}

Matrix mat::add(Matrix n, double m)
{
	Matrix sum = Matrix(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) + m;
		}
	}
	return sum;
}

Matrix mat::add(double m, Matrix n)
{
	Matrix sum = Matrix(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) + m;
		}
	}
	return sum;
}

Matrix mat::sub(Matrix n, Matrix m)
{
	if (n.row == m.row && n.col == m.col)
	{
		Matrix sum = Matrix(n.row, n.col);
		for (int i = 0;i < n.row;i++)
		{
			for (int j = 0;j < n.col;j++)
			{
				*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) - *(m.value + i*n.col + j);
			}
		}
		return sum;
	}
	else
		return Matrix();
}

Matrix mat::sub(Matrix n, double m)
{
	Matrix sum = Matrix(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) - m;
		}
	}
	return sum;
}

Matrix mat::sub(double m, Matrix n)
{
	Matrix sum = Matrix(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(sum.value + i*n.col + j) = m-*(n.value + i*n.col + j);
		}
	}
	return sum;
}

Matrix mat::mul(Matrix n, Matrix m)
{
	if (n.row == m.row && n.col == m.col)
	{
		Matrix sum = Matrix(n.row, n.col);
		for (int i = 0;i < n.row;i++)
		{
			for (int j = 0;j < n.col;j++)
			{
				*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) * *(m.value + i*n.col + j);
			}
		}
		return sum;
	}
	else
		return Matrix();
}

Matrix mat::mul(Matrix n, double m)
{
	Matrix sum = Matrix(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) * m;
		}
	}
	return sum;
}

Matrix mat::mul(double m, Matrix n)
{
	Matrix sum = Matrix(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) * m;
		}
	}
	return sum;
}

Matrix mat::div(Matrix n, Matrix m)
{
	if (n.row == m.row && n.col == m.col)
	{
		Matrix sum = Matrix(n.row, n.col);
		for (int i = 0;i < n.row;i++)
		{
			for (int j = 0;j < n.col;j++)
			{
				*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) / *(m.value + i*n.col + j);
			}
		}
		return sum;
	}
	else
		return Matrix();
}

Matrix mat::div(Matrix n, double m)
{
	Matrix sum = Matrix(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(sum.value + i*n.col + j) = *(n.value + i*n.col + j) / m;
		}
	}
	return sum;
}

Matrix mat::div(double m, Matrix n)
{
	Matrix sum = Matrix(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(sum.value + i*n.col + j) =m/ *(n.value + i*n.col + j) ;
		}
	}
	return sum;
}

Matrix mat::tanm(Matrix n)
{
	Matrix result(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(result.value + i*n.col + j) = tan(*(n.value + i*n.col + j));
		}
	}
	return result;;
}

Matrix mat::sinm(Matrix n)
{
	Matrix result(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(result.value + i*n.col + j) = sin(*(n.value + i*n.col + j));
		}
	}
	return result;
}

Matrix mat::cosm(Matrix n)
{
	Matrix result(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(result.value + i*n.col + j) = cos(*(n.value + i*n.col + j));
		}
	}
	return result;
}

Matrix mat::powm(Matrix n, double y)
{
	Matrix result(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(result.value + i*n.col + j) = pow(*(n.value + i*n.col + j), y);
		}
	}
	return result;
}

Matrix mat::powm(double y, Matrix n)
{
	Matrix result(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(result.value + i*n.col + j) = pow(y, *(n.value+i*n.col+j));
		}
	}
	return result;
}

Matrix mat::expm(Matrix n)
{
	Matrix result(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(result.value + i*n.col + j) = exp(*(n.value+i*n.col+j));
		}
	}
	return result;;
}

Matrix mat::sqrtm(Matrix n)
{
	Matrix result(n.row, n.col);
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			*(result.value + i*n.col + j) = sqrt(*(n.value + i*n.col + j));
		}
	}
	return result;;
}

double mat::sum(Matrix n)
{
	double sum = 0;
	for (int i = 0;i < n.row;i++)
	{
		for (int j = 0;j < n.col;j++)
		{
			sum = sum + *(n.value + i*n.col + j);
		}
	}
	return sum;
}

Matrix mat::seq(double init, double step, double end)
{
	int length = (int)((end - init) / step);
	Matrix result = Matrix(1, length);
	for (int i = 0;i < length;i++)
	{
		*(result.value + i) = init + i*step;
	}
	return result;
}

Matrix mat::zeros(int row, int col)
{
	Matrix result = Matrix(row, col);
	for (int i = 0;i < result.row;i++)
	{
		for (int j = 0;j < result.col;j++)
		{
			*(result.value + i*col + j) = 0;
		}
	}
	return result;
}

Matrix mat::ones(int row, int col)
{
	Matrix result = Matrix(row, col);
	for (int i = 0;i < result.row;i++)
	{
		for (int j = 0;j < result.col;j++)
		{
			*(result.value + i*col + j) = 1;
		}
	}
	return result;;
}

Matrix mat::randn(int row, int col, int seed)
{
	Matrix result = Matrix(row, col);
	srand(seed);
	for (int i = 0;i < result.row;i++)
	{
		for (int j = 0;j < result.col;j++)
		{
			*(result.value + i*col + j) = ((double)rand())/ RAND_MAX;
		}
	}
	return result;
}

Matrix mat::DTFT(Matrix n, Matrix w, int type)
{
	if (n.row == 1 || n.col == 1 && w.row == 1 || w.col == 1) {
		Matrix result = Matrix(w.row, w.col);
		int L = w.row*w.col;
		Matrix real, imag;
		mat op;
		real = op.matmul(n, op.cosm(op.matmul(n.T(), w)));
		imag = -1*op.matmul(n, op.sinm(op.matmul(n.T(), w)));
		if (type == 0)
		{
			return op.sqrtm(op.powm(real, 2) + op.powm(imag, 2));
		}
	
	}
	
	
	return Matrix();
}


Matrix mat::reverse(Matrix n)
{
	if (n.col == 1 || n.row == 1)
	{
		Matrix result(n.row, n.col);
		for (int i = 0;i < n.col*n.row;i++)
		{
			*(result.value + (n.col*n.row- i - 1)) = *(n.value + i);
		}
		return result;
	}
	else
		return Matrix();
}

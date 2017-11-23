

#include "stdafx.h"
#include"mat.h"
#include <iostream>
using namespace std;
int main()
{
	mat op;
	double a[] = { 1,2,3,4,5,6};
	double b[] = { 2,3,4,5,6,7 };

	Matrix n = op.seq(1.2, 0.3, 3.4);
	n.print();
	Matrix result;
	result = op.DFT(n);
	result.print();

	/*
	n = op.zeros(1, 50);
	for (int i = 0;i < 10;i++)
	{
		n.set(0, i, 1);
	}
	cout << "序列n的情况：" << endl;
	cout << n.row << endl;
	cout << n.col << endl;
	n.print();
	cout << "华丽的分割线————————————————————————————————————————————————————————" << endl;
	w = op.seq(0, mat::pi / 50, mat::pi);
	cout << "序列w的情况：" << endl;
	cout << w.row << endl;
	cout << w.col << endl;
	w.print();
	cout << "华丽的分割线------------------------------------------------------------------------------------------------------------" << endl;
	
	//result = op.DTFT(n, w, 0);
	cout << result.row << endl;
	cout << result.col << endl;
	result.print();
	*/
	system("pause");
    return 0;
}



#include "stdafx.h"
#include"mat.h"
#include <iostream>
using namespace std;
int main()
{
	double a[] = { 3.14,3.14,3.14,3.14};
	double b[] = { 2,3,1,0};
	double scalar = 3.14;
	Matrix x(a, 1, 4);
	Matrix y(b, 2,2);	
	system("pause");
    return 0;
}

#pragma once
#include<vector>
using std::vector;
class sort
{
public:
	//ð������
	//template <typename T>
	//ģ���࣬��ģ��
	void bubble_sort(vector<double> &data ,bool reverse = true);
	void straight_insert_sort(vector<double>& data, bool reverse = true);
	void shell_sort(vector<double>& data, bool reverse);
};


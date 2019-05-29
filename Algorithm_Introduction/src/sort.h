#pragma once
#include<vector>
using std::vector;
class sort
{
public:
	//冒泡排序
	//template <typename T>
	//模板类，类模板
	void bubble_sort(vector<double> &data ,bool reverse = true);
	void straight_insert_sort(vector<double>& data, bool reverse = true);
	void shell_sort(vector<double>& data, bool reverse);
};


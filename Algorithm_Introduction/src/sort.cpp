#include "sort.h"
void sort::bubble_sort(vector<double> &data, bool reverse)
{
	/*
	冒泡排序，基本思想两两互相比对，如果是顺序排序，若存在前者大于后者，
	则交换两者的位置，知道所有的元素都满足前一个小于后一个。
	逆序类似
	*/
	bool flag =true;
	double tmp;
	int length = data.size();
	if (reverse)
		while(flag){
			flag = false;
			for (int i=0; i<length-1; i++) {
				if (data[i] < data[i+1]) {
					tmp = data[i];
					data[i] = data[i + 1];
					data[i + 1] = tmp;
					flag = true;
				}
			}
		}
	else
		while (flag) {
			flag = false;
			for (int i = 0; i < length - 1; i++) {
				if (data[i] > data[i + 1]) {
					tmp = data[i];
					data[i] = data[i + 1];
					data[i + 1] = tmp;
					flag = true;
				}
			}
		}
}

void sort::straight_insert_sort(vector<double>& data, bool reverse)
{
	/*
	直接插入排序，从第2个元素开始，将第二个元素以后的每个元素（后面无序，前面因为只有一个元素，所以是有序的）
	都与前面的有序元素做对比，若后面某个无序元素在前面有序元素中某个位置满足大于前一个，小于后一个，
	则将该元素插入到该位置

	*/
	int length = data.size();
	if (reverse)
		for (int i = 1; i < length; i++) {

			for (int j = 0; j < i; j++) {
				if (data[i] > data[j]) {
					data.insert(data.begin()+j, data[i]);
					data.erase(data.begin() + i + 1);
					break;
				}
			}
		}
	else{
		for (int i = 1; i < length; i++) {

			for (int j = 0; j < i; j++) {
				if (data[i] < data[j]) {
					data.insert(data.begin() + j, data[i]);
					data.erase(data.begin() + i + 1);
					break;
				}
			}
		}
	}
}

void sort::shell_sort(vector<double>& data, bool reverse)
{
	int length = data.size();
	for (int step = length / 3; step > 1; step = step / 3 + 1) {
		for (int i = 0; i < step; i++) {
			for (int j = i+step; j < length; j = j + step) {
				for (int k = j ; k < length; k = k + step) {
					if (data[j] > data[k]) {
						data.insert(data.begin() + k, data[j]);
						data.erase(data.begin() + j + 1);
					}
				}
			}
		}
	}
}

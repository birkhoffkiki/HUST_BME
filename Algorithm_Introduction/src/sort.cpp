#include "sort.h"
void sort::bubble_sort(vector<double> &data, bool reverse)
{
	/*
	ð�����򣬻���˼����������ȶԣ������˳������������ǰ�ߴ��ں��ߣ�
	�򽻻����ߵ�λ�ã�֪�����е�Ԫ�ض�����ǰһ��С�ں�һ����
	��������
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
	ֱ�Ӳ������򣬴ӵ�2��Ԫ�ؿ�ʼ�����ڶ���Ԫ���Ժ��ÿ��Ԫ�أ���������ǰ����Ϊֻ��һ��Ԫ�أ�����������ģ�
	����ǰ�������Ԫ�����Աȣ�������ĳ������Ԫ����ǰ������Ԫ����ĳ��λ���������ǰһ����С�ں�һ����
	�򽫸�Ԫ�ز��뵽��λ��

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

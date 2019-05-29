
#include <iostream>
#include "src/sort.h"
using namespace std;
int main()
{
	sort s;
	vector<double> a{ 2.2, 1,1,5,0,1000,6,9.0,7.8 };
	//s.bubble_sort(a,false);
	//s.straight_insert_sort(a, true);
	s.shell_sort(a, true);
	for (int i = 0; i < a.size(); i++) {
		std::cout << a[i] << endl;
	}
	cout << "size:"<<a.size() << endl;
	

	system("pause");
	return 0;
}

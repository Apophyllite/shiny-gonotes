//快速排序
#include <iostream>
#include <vector>
using namespace std;

void qsort(std::vector<int>& v, int left, int right) {
	if (left >= right) return;
	int begin = left, end = right;
	int midpos = left + (right - left)/2;
	int mid = v[midpos];
	while (left < right) {
		while (v[left] < mid) {
			left ++;
		}
		while (v[right] > mid) {
			right --;
		}
		int tmp = v[left];
		v[left] = v[right];
		v[right] = tmp;
	}
	v[left] = mid;
	qsort(v, begin, left - 1);
	qsort(v, left + 1, end);
}

int main() {
	std::vector<int> v  {9,8,7,6,5,4,3,2,1};
	qsort(v, 0, v.size()-1);
	for (auto i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

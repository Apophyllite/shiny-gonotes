#include <iostream>
#include <vector>
using namespace std;
//大根堆 左闭右开
void heapsort (std::vector<int>& v, int pos, int end) {
	while (pos < end) {
		int i = 2*pos + 1;
		if (i >= end) break;
		if (i + 1 < end and v[i+1] > v[i]) i += 1;
		if (v[i] > v[pos]) {
			swap(v[i], v[pos]);
			pos = i;
		} else {
			break;
		}
	}
	return ;
}

int main() {
	std::vector<int> v {9, 7, 6, 5, 8, 2, 1, 3};
	for (int i = v.size()/2; i >= 0; i --) {
		heapsort(v, i, v.size());
	}

	std::cout << "after first adjust: "; 
	for (auto i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	for (int i = v.size() - 1; i >= 0; i--) {
		swap(v[0], v[i]);
		heapsort(v, 0, i);
	}
	for (auto i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}

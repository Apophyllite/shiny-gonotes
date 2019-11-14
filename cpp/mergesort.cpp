#include <iostream>
#include <vector>
using namespace std;

void mergesort(std::vector<int>& v, int left, int right) {
	if (left >= right) {
		return;
	}
	mergesort(v, left, left+(right-left)/2);
	mergesort(v, left+(right-left)/2+1, right);

	int ll = left, lend = left+(right-left)/2, lr = left+(right-left)/2+1;

	std::vector<int> tmp(right - left + 1, 0);
	int pos = 0;
	while (ll <= lend or lr <= right) {
		if (ll > lend) {
			tmp[pos++] = v[lr++];
		} else if (lr > right) {
			tmp[pos++] = v[ll++];
		} else {
			if (v[ll] > v[lr]) {
				tmp[pos++] = v[ll++];
			} else {
				tmp[pos++] = v[lr++];
			}
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		v[left+i] = tmp[i];
	}
	return;
}

int main() {
	std::vector<int> v {1,3,5,7,9,2,4,6,8};
	mergesort(v, 0, v.size() - 1);
	for (auto i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}

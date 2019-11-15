#include <unistd.h>
#include<iostream>
#include<set>
#include <unordered_set>
#include"mthreads.h"
std::unordered_set <int> mis;
void Insert(int threadidx) {
	for (int i = 0; i < 100; i++) {
		mis.insert(100*threadidx + i);
	}
}
/*
int main() {
	std::thread t1([]{std::cout << "a" << std::endl;});
	std::vector<std::thread> tv;
	//t1.join();
	tv.push_back(std::move(t1));
	//for (auto t:tv) t.join(); //错误 禁止拷贝构造
	for (auto& t:tv) t.join(); //
}
*/

int main() {
	std::vector<std::thread> tv;
	for (int i = 0; i < 4; i++) {
		tv.emplace_back(std::thread(Insert, i));
	}
	for (auto& t:tv)
		t.join();
	sleep(10);

	std::cout << mis.size() << std::endl;
	return 0;
}

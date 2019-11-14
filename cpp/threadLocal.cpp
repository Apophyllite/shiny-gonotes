#include <iostream>
#include <string>
#include <thread>
#include <mutex>
//线程局部存储 编译器 需要支持c++11以上版本
class A {
	public:
		A(int x):a(x){
			std::cout << "con A : " << a << std::endl;
		}
		A(int &x):a(x){
			std::cout << "copy A : " << a << std::endl;
		}
		A& operator=(const A &x) {
			a = x.a;
			std::cout << " == " << a << std::endl;
			return *this;
		}
		~A(){
			std::cout << "delete A :"<< a << std::endl;
		}
	public:
		int a;
};
A aa(12);
A bb(45);
thread_local A rage(1);
std::mutex cout_mutex;

void increase_rage(const std::string& thread_name)
{
	//rage= new A(3);
	if(thread_name == "b") {
		rage = bb;
	} else {
		rage = aa;
	}
	rage = A(789);
	//++rage; // modifying outside a lock is okay; this is a thread-local variable
	std::lock_guard<std::mutex> lock(cout_mutex);
	std::cout << "Rage counter for " << thread_name << ": " << rage.a << '\n';
}

int main()
{
	std::thread a(increase_rage, "a"), b(increase_rage, "b");

	{
		std::lock_guard<std::mutex> lock(cout_mutex);
		//rage = A(222);
		std::cout << "Rage counter for main: " << rage.a << '\n';
	}    
	a.join();
	b.join();
}

#include<cstdio>
#include<cstring>
#include<algorithm>
#include <iostream>
#include <json/json.h>
using namespace std;

int main()
{

	Json::Value jv = Json::arrayValue;
	jv.append(1);
	jv.append(2);
	auto begin = jv.begin();
	std::cout << *begin << std::endl;
	if (begin->isInt()) {
		std::cout << "is int" << std::endl;
	}
	return 0;
}


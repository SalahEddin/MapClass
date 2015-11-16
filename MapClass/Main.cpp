#include <iostream>
#include <map>
#include "CMap.h"

int main() {
	std::map<std::string, int> stdMap;
	stdMap["num"] = 5;
	stdMap["num"] = 14;
	stdMap.clear();
	std::cout << stdMap.size() << std::endl;
	
	CMap<std::string, int> myMap;
	myMap["X"] = 1;
	system("pause");
}
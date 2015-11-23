#include <iostream>
#include <map>
#include "CMap.h"

int main() {
	std::map<std::string, int> stdMap;
	stdMap["num"] = 5;
	stdMap["num"] = 14;
	stdMap.clear();
	std::cout << stdMap.size() << std::endl;
	
	CMap<std::string, int> *myMap = new CMap<std::string, int>();
	std::string foo = "x";
	//myMap->insert(foo,5);
	//auto c = (*myMap)[foo];
	//std::cout << c << std::endl;
	system("pause");
}
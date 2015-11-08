#include <iostream>
#include <map>

int main() {
	std::map<std::string, int> stdMap;
	stdMap["num"] = 5;
	stdMap["num"] = 14;
	stdMap.clear();
	std::cout << stdMap.size() << std::endl;
	
	system("pause");
}
#include <iostream>
#include "CMap.h"

int main() {
	/*std::map<std::string, int> stdMap;
	stdMap["num"] = 5;
	stdMap["num"] = 14;
	stdMap.clear();
	std::cout << stdMap.size() << std::endl;*/

	//CMap<int, std::string>* test = new CMap<int, std::string>();
	//test->Insert(5, "wow");
	//test->Insert(4, "wows");
	//test->Insert(2, "xxxxxxx");
	//test->Insert(6, "wowsasd");
	//test->Insert(1, "wowda");
	//std::cout << test->Get(1) << std::endl;
	//test->Update(1, "ZZZZZZZZZ");
	//std::cout << test->Get(1) << std::endl;
	//test->Erease(1);
	//std::cout << test->Get(1) << std::endl;
	//delete test;
	
	CMap<int, int>* myMap = new CMap<int, int>();

	system("pause");
}
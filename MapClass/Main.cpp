#include <iostream>
#include "CMap.h"

int main() {
	/*std::map<std::string, int> stdMap;
	stdMap["num"] = 5;
	stdMap["num"] = 14;
	stdMap.clear();
	std::cout << stdMap.size() << std::endl;*/
	std::string val;
	CMap<int, std::string>* test = new CMap<int, std::string>();
	test->Insert(5, "wow");
	test->Insert(4, "wows");
	test->Insert(2, "xxxxxxx");
	test->Insert(6, "wowsasd");
	test->Insert(1, "wowda");
	val = test->Get(1);
	test->Update(1, "ZZZZZZZZZ");
	val = test->Get(1);
	test->Erease(1);
	val = test->Get(1);
	delete test;
	

	system("pause");
}
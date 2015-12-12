#include <iostream>
#include "CMap.h"

int main() {
	/*std::map<std::string, int> stdMap;
	stdMap["num"] = 5;
	stdMap["num"] = 14;
	stdMap.clear();
	std::cout << stdMap.size() << std::endl;*/
	std::string val;
	CMap<int, int>* test = new CMap<int, int>();
	/*test->Insert(5, "wow");
	test->Insert(4, "wows");
	test->Insert(2, "xxxxxxx");
	test->Insert(6, "wowsasd");
	test->Insert(1, "wowda");*/
	test->Insert(5, 223344);
	test->Insert(4, 1234);
	test->Insert(2, 4230);
	test->Insert(6, 97979);
	test->Insert(1, 23323322);
	std::cout << test->Get(1) << std::endl;;
	test->Update(1, 10101010);
	std::cout << test->Get(1) << std::endl;;
	// test->Erease(1);
	//test->Get(1);
	delete test;
	

	system("pause");
}
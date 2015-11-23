#include <iostream>
#include <map>
#include "CMap.h"
#include "CBinTree.h"

int main() {
	/*std::map<std::string, int> stdMap;
	stdMap["num"] = 5;
	stdMap["num"] = 14;
	stdMap.clear();
	std::cout << stdMap.size() << std::endl;*/

	CBinTree* test = new CBinTree();
	test->Insert(5, "wow");
	test->Insert(4, "wows");
	test->Insert(2, "xxxxxxx");
	test->Insert(6, "wowsasd");
	test->Insert(1, "wowda");
	std::cout << test->Get(1);
	system("pause");
}
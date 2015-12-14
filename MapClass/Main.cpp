#include <iostream>
#include "CMap.h"
#include <cstdio>
#include <ctime>
#include <map>

#define PROCESS_COUNT 300
void stdMapTest();
void myCMapTest();

int main() {

	std::clock_t start;
	double duration;

	start = std::clock();

	// stdMapTest();
	myCMapTest();

	duration = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);

	std::cout << "std::map required: " << duration << '\n';

	start = std::clock();

	// stdMapTest();
	myCMapTest();

	duration = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);

	std::cout << "my map required: " << duration << '\n';

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

void stdMapTest()
{
	std::map<int, int> stdMap;
	// PROCESS_COUNT insertions
	for (int i = 0; i < PROCESS_COUNT; i++)
	{
		stdMap[i] = rand() % PROCESS_COUNT;
	}
}

void myCMapTest()
{
	CMap<int, int>* myMap = new CMap<int, int>();
	// 3000 insertions
	for (int i = 0; i < PROCESS_COUNT; i++)
	{
		int key_i = rand() % PROCESS_COUNT;
		// my implementation uses trees in opposition to balanced trees
		// so it performs better when elements aren't ordered
		myMap->Insert(key_i, rand() % PROCESS_COUNT);
		// myMap->Update(key_i, rand() % PROCESS_COUNT);
	}
	delete myMap;
}
#include <iostream>
#include "CMap.h"
#include <cstdio>
#include <ctime>
#include <map>
#include <string>

#define PROCESS_COUNT (30000)
void stdMapTest();
void myCMapTest();

int main() {

	/*std::clock_t start;
	double duration;
	start = std::clock();
	myCMapTest();
	duration = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "my map required: " << duration << " to insert, update and delete " <<'\n';
	*/
	system("pause");
}

void stdMapTest()
{
	std::map<int, int>* stdMap = new std::map<int, int>;
	// PROCESS_COUNT insertions
	for (int i = 0; i < PROCESS_COUNT; i++)
	{
		(*stdMap)[i] = rand() % PROCESS_COUNT;
		(*stdMap)[i] = rand() % PROCESS_COUNT;
		(*stdMap)[i];
	}
	delete stdMap;
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
		// myMap[key_i + 1];
		std::cout << myMap->chunksCount() << std::endl;
	}
	delete myMap;
}
#include "stdafx.h"
#include "CppUnitTest.h"
#include <CMap.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			CMap<int, int>* map = new CMap<int, int>();
			int key = 12, value = 15;
			map->Insert(key, value);
			Assert::AreEqual(value, (*map)[key]);
			delete map;
		}

	};
}
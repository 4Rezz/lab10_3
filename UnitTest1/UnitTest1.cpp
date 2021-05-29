#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10_3/lab_10_3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ofstream f("test.txt");
			Goods goods;
			goods.price = 200.0;
			f.write((char*)&goods, sizeof(Goods));
			f.close();
			ifstream file("test.txt");
			bool x = SortPrice("test.txt", 100.0, 1000.0);
			Assert::AreEqual(x, true);
		}
	};
}

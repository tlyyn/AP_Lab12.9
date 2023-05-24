#include "pch.h"
#include "CppUnitTest.h"
#include "../AP_Lab12.9/Source.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{

			Node* root = nullptr;

			int t = countNodesWithBothChildren(root);

			Assert::AreEqual(t, 0);
		}
	};
}


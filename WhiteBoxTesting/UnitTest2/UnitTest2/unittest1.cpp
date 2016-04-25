#include "stdafx.h"
#include "CppUnitTest.h"
#include "Method.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestZero)
		{
			double expected = 0;
			Assert::AreEqual( expected, Calculator::getDistance(0, 0, 0, 0));
		}
		TEST_METHOD(TestNotZero)
		{
			double expected = 0;
			Assert::AreNotEqual(expected ,Calculator::getDistance(100, 100, 0, 0));
		}
		TEST_METHOD(Test100m)
		{
			int expected = 1568;

			Assert::AreEqual(expected,(int) Calculator::getDistance(0, 0, 10, 10));
		}
		TEST_METHOD(TestAdd)
		{
			float expected = 10;

			Assert::AreEqual(expected, Calculator::Increase(5,5,10));
		}
		TEST_METHOD(TestAdd2)
		{
			float expected = 10;

			Assert::AreEqual(expected, Calculator::Increase(10, 10, 10));
		}
		TEST_METHOD(TestAdd3)
		{
			float expected = 6;

			Assert::AreEqual(expected, Calculator::Increase(3, 3, 10));
		}
	};
}
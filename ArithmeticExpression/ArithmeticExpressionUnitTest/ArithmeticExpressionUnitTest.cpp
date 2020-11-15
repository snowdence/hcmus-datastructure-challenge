#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "../ArithmeticExpression/ArExp.h"
#include "../ArithmeticExpression/ArExpConverter.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArithmeticExpressionUnitTest
{
	TEST_CLASS(ArithmeticExpressionUnitTest)
	{
	public:
		TEST_METHOD(testInfixToPrefix_1)
		{
			string expect = "+12";
			ArExpConverter converter(ArExp("1 + 2"));
			ArExp result = converter.infix_to_prefix();
			Assert::AreEqual(result.to_string(), expect);
		}
		TEST_METHOD(testInfixToPrefix_2)
		{
			string expect = "+/+/+123456";
			ArExpConverter converter(ArExp("((1+2)/3+4)/5+6"));
			ArExp result = converter.infix_to_prefix();
			Assert::AreEqual(result.to_string(), expect);
		}
		TEST_METHOD(testInfixConvert) {
			ArExpConverter converter(ArExp("3^2/(5 * 3) + 10"));
			Assert::IsTrue("3 2 ^ 5 3 * / 10 +" == converter.infix_to_postfix().to_string());
		}

		TEST_METHOD(testInfixConvertException) {
			ArExpConverter converter(ArExp("4 4 3 + -"));
			ArExp result = converter.infix_to_postfix();
			Assert::IsTrue("3 2 ^ 5 3 * / 10 +" == result.to_string() );
		}
	};
}

#pragma once
#include <iostream>
#include "ArExpConverter.h"

using namespace std;
int main()
{
	ArExp exp("[(2 + 3) ^ 3] * 2");
	cout << exp.to_string() << endl;;
	ArExpConverter converter(exp);
	cout << "Convert to postfix: " << endl;
	//cout << converter.infix_to_prefix().to_string() << endl;
	try {
		ArExp converted = converter.infix_to_postfix();
		std::cout << converted.to_string() << endl;
	}
	catch (MismatchedParenthesisException e) {
		cout << e.what() << endl;
	}
	catch (InvalidExpressionException e) {
		cout << e.what() << endl;
	}
	catch (NotBalanceBracketExpressionException e) {
		cout << e.what() << endl;
	}

	system("pause");
}

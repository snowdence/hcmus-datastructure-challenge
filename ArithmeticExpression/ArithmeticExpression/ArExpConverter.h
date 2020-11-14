#pragma once
#include "ArExp.h"
#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#include "ArConfig.h"
#include "ArExpException.h"
#include "ArHelper.h"

using namespace std;
class ArExpConverter
{
protected:
	ArExp _arexp;
public:
	ArExpConverter() {}
	ArExpConverter(ArExp arexp) { this->_arexp = arexp; }

	int getPriority(char C)
	{
		if (C == '-' || C == '+')
			return 1;
		else if (C == '*' || C == '/')
			return 2;
		else if (C == '^')
			return 3;
		return 0;
	}
	ArExp infix_to_prefix() {
		string exp_str = _arexp.to_string();
		// stack for operators. 
		stack<char> operators;

		// stack for operands. 
		stack<string> operands;


		for (int i = 0; i < exp_str.length(); i++) {
			if (exp_str[i] == ' ') {
				continue;
			}
			else if (exp_str[i] == '(') {
				operators.push(exp_str[i]);
			}
			else if (exp_str[i] == ')') {
				while (!operators.empty() && operators.top() != '(') {
					string op1 = operands.top();
					operands.pop();
					string op2 = operands.top();
					operands.pop();
					char op = operators.top();
					operators.pop();
					string tmp = op + op2 + op1;
					operands.push(tmp);
				}
				operators.pop();
			}
			else if (!(!isalpha(exp_str[i]) && !isdigit(exp_str[i]))) {
				operands.push(string(1, exp_str[i]));
			}
			else {
				while (!operators.empty() &&
					getPriority(exp_str[i]) <=
					getPriority(operators.top())) {

					string op1 = operands.top();
					operands.pop();

					string op2 = operands.top();
					operands.pop();

					char op = operators.top();
					operators.pop();

					string tmp = op + op2 + op1;
					operands.push(tmp);
				}

				operators.push(exp_str[i]);
			}
		}

		while (!operators.empty()) {
			string op1 = operands.top();
			operands.pop();

			string op2 = operands.top();
			operands.pop();

			char op = operators.top();
			operators.pop();

			string tmp = op + op2 + op1;
			operands.push(tmp);
		}

		// Final prefix expression is 
		// present in operands stack. 
		ArExp result(operands.top(), ExpForm::POSTFIX_EXP);
		return result;

	}


	bool isOperator(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
	}

	bool leftAssoc(char c) {
		return c != '^';
	}

	int priority(char c) {
		if (c == '^') return 3;
		if (c == '*') return 2;
		if (c == '/') return 2;
		if (c == '+') return 1;
		if (c == '-') return 1;
		return 0;
	}


	string next_token(int& i) {
		string b = "";
		string expr = this->_arexp.to_string();
		while (i < expr.length() && expr[i] == ' ') i++;
		if (i == expr.length()) return "";
		while (i < expr.length() && expr[i] != ' ' && expr[i] != '(' && expr[i] != ')' && !isOperator(expr[i])) {
			b += expr[i++];
		}
		if (b != "") return b;
		return  string(1, expr[i++]);

	}
	ArExp infix_to_postfix() {
		ArExp result;
		string expr = _arexp.to_string();
		int i = 0;
		string tok = "";
		stack<string> S;
		stack<string> O;
		while ((tok = next_token(i)) != "") {

#ifdef AR_EXP_DEBUG
			cout << "Parse token: " << tok << endl;
#endif // AR_EXP_DEBUG

			if (tok == "(") S.push(tok);
			else if (tok == ")") {
				while (!S.empty() && S.top() != "(") {
					string s_top = S.top();
					O.push(s_top);
					S.pop();
				}
				if (S.empty()) throw MismatchedParenthesisException();
				S.pop();
			}
			else if (isOperator(tok[0])) {
				while (!S.empty() && isOperator(S.top()[0]) && ((leftAssoc(tok[0]) && priority(tok[0]) <= priority(S.top()[0])) || (!leftAssoc(tok[0]) && priority(tok[0]) < priority(S.top()[0]))))
				{
					string s_top = S.top();
					O.push(s_top);
					S.pop();
				}
				S.push(tok);
			}
			else {
				O.push(tok);
			}
		}
		while (!S.empty()) {
			if (!isOperator(S.top()[0])) throw MismatchedParenthesisException();
			string s_top = S.top();
			O.push(s_top);
			S.pop();
		}

		if (O.empty()) return ArExp("Invalid expression.");
		string temp = "";
		while (!O.empty()) {
			temp = O.top() + " "+ temp;
			O.pop();
		}
		temp = ArHelper::trim(temp);
#ifdef AR_EXP_DEBUG
		cout << "[" << temp << "]" << endl;
#endif // AR_EXP_DEBUG

		return ArExp(temp, ExpForm::POSTFIX_EXP);
	}

};


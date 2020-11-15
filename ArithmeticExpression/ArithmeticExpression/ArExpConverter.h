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


	string next_token(string str, int& i) {
		string b = "";
		string expr = str;
		while (i < expr.length() && expr[i] == ' ') i++;
		if (i == expr.length()) return "";
		while (i < expr.length() && expr[i] != ' ' && expr[i] != '(' && expr[i] != ')' && !isOperator(expr[i])) {
			b += expr[i++];
		}
		if (b != "") return b;
		return  string(1, expr[i++]);

	}


	// function to check if brackets are balanced 
	bool areBracketsBalanced(string  str_expr)
	{
		string expr = ArHelper::filter_bracket(str_expr);

		stack<char> s;
		char x;

		// Traversing the Expression 
		for (int i = 0; i < expr.length(); i++)
		{
			if (expr[i] == '(' || expr[i] == '['
				|| expr[i] == '{')
			{
				// Push the element in the stack 
				s.push(expr[i]);
				continue;
			}

			// IF current current character is not opening 
			// bracket, then it must be closing. So stack 
			// cannot be empty at this point. 
			if (s.empty())
				return false;

			switch (expr[i]) {
			case ')':

				// Store the top element in a 
				x = s.top();
				s.pop();
				if (x == '{' || x == '[')
					return false;
				break;

			case '}':

				// Store the top element in b 
				x = s.top();
				s.pop();
				if (x == '(' || x == '[')
					return false;
				break;

			case ']':

				// Store the top element in c 
				x = s.top();
				s.pop();
				if (x == '(' || x == '{')
					return false;
				break;
			}
		}

		// Check Empty Stack 
		return (s.empty());
	}


	bool basic_validate_infix(string infix_exp) {
		string expr = ArHelper::trim(infix_exp);
		expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
		char t1, t2;

		for (int i = 0; i < expr.size() - 1; i++)
		{
			t1 = expr[i];
			t2 = expr[i + 1];
			if (isOperator(t1) && isOperator(t2)) {
				return false;
			}
		}
		return true;
	}

	string replace_bracket(string infix_exp) {
		string result = "";
		for (int i = 0; i < infix_exp.size(); i++) {
			char c = infix_exp[i];
			if (c == '[' || c == '{') {
				result += '(';
			}
			else if (c == ']' || c == '}') {
				result += ')';
			}
			else {
				result += c;
			}

		}
		return result;
	}

	ArExp infix_to_postfix() {
		ArExp result;
		string expr = _arexp.to_string();

		if (areBracketsBalanced(expr) == false) {
			throw NotBalanceBracketExpressionException();
		}
		if (basic_validate_infix(expr) == false) {
			cout << "Error infix" << endl;
			throw InvalidExpressionException();
		}

		// chuan hoa ngoac
		expr = replace_bracket(expr);

		int i = 0;
		string tok = "";
		stack<string> S;
		vector<string> O;
		while ((tok = next_token(expr, i)) != "") {

#ifdef AR_EXP_DEBUG
			cout << "Parse token: " << tok << endl;
#endif // AR_EXP_DEBUG

			if (tok == "(") {
				S.push(tok);
			}
			else if (tok == ")") {
				if (tok == ")") {
					while (!S.empty() && S.top() != "(") {
						string s_top = S.top();
						O.push_back(s_top);
						S.pop();
					}
					if (S.empty())
					{
						throw MismatchedParenthesisException();
					}
					S.pop();
				}
			}
			else if (isOperator(tok[0])) {
				while (!S.empty() && isOperator(S.top()[0]) && ((leftAssoc(tok[0]) && priority(tok[0]) <= priority(S.top()[0])) || (!leftAssoc(tok[0]) && priority(tok[0]) < priority(S.top()[0]))))
				{
					string s_top = S.top();
					O.push_back(s_top);
					S.pop();
				}
				S.push(tok);
			}
			else {
				O.push_back(tok);
			}
		}
		while (!S.empty()) {
			if (!isOperator(S.top()[0]))
			{
				throw MismatchedParenthesisException();
			}
			string s_top = S.top();
			O.push_back(s_top);
			S.pop();
		}

		if (O.empty()) throw InvalidExpressionException();

		string temp = "";
		int cur_tk_value = 0;
		stack<int> evalutate;
		for (int i = 0; i < O.size(); i++) {
			string cur_tk_str = O[i];

			if (!isOperator(cur_tk_str[0])) {
				//operant
				cur_tk_value = atoi(cur_tk_str.c_str());
				evalutate.push(cur_tk_value);
			}
			else {

				int val1 = evalutate.top();
				evalutate.pop();
				int val2 = evalutate.top();
				evalutate.pop();
				switch (cur_tk_str[0])
				{
				case '+': evalutate.push(val2 + val1); break;
				case '-':  evalutate.push(val2 - val1); break;
				case '*':  evalutate.push(val2 * val1); break;
				case '/':  evalutate.push(val2 / val1); break;
				}
			}
			temp += " " + O[i];
		}


		temp = ArHelper::trim(temp);
#ifdef AR_EXP_DEBUG
		cout << "[" << temp << "]" << endl;
#endif // AR_EXP_DEBUG

		return ArExp(temp, ExpForm::POSTFIX_EXP);
	}

};


#pragma once
#include <iostream>
#include <string>
#include "ExpForm.h"
#include "ArHelper.h"
#include  <stack>
#include <vector>
#include "ArExpException.h"
using namespace std;


class ArExp
{
protected:
	string _exp = "";
	ExpForm _exp_form;
public:
	ArExp() { _exp = "0"; _exp_form = ExpForm::INFIX_EXP; }
	
	ArExp(string exp) {
		this->set_exp_str(exp);
		_exp_form = (ExpForm::INFIX_EXP);
	}
	
	bool isValid() {
		return true;
	}
	ExpForm getFormType() {
		return this->_exp_form;
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


	bool isOperator(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
	}

	ArExp(string exp, ExpForm form)  {
		_exp = (exp);
		_exp_form = (form); 
	}
	void set_exp_str(string exp) {
		_exp = exp;
		this->trim_space(); // chuan hoa 
	}
	
	
	void trim_space()
	{
		this->_exp = ArHelper::trim(_exp);
		//_exp.erase(remove(_exp.begin(), _exp.end(), ' '), _exp.end());
	}
	string to_string() {
		return this->_exp;
	}


	friend inline bool operator==(const ArExp& lhs, const ArExp& rhs) { 
		return (lhs._exp == rhs._exp && lhs._exp_form == rhs._exp_form);
	}

	friend inline bool operator==(const ArExp& lhs, const char*& rhs) {
		return (lhs == ArExp(rhs));
	}

	friend inline bool operator==(const ArExp& lhs, const string& rhs) {
		return (lhs== ArExp(rhs));
	}

	friend inline bool operator==(const char*& lhs, const ArExp& rhs) {
		return (ArExp(lhs) == rhs);
	}
	friend inline bool operator==(const string& lhs, const ArExp& rhs) {
		return (ArExp(lhs) == rhs);
	}
};

// ArithmeticExpressionSingle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <iomanip>
#include <fstream>

using namespace std;

enum class ExpForm { INFIX_EXP, PREFIX_EXP, POSTFIX_EXP };

#pragma region AR_Exception
class ArExpException : public exception
{
/// <summary>
/// Base class exception for ArExp
/// </summary>

public:
	virtual const char* what() const throw()
	{
		return "Mismatched parenthesis.";
	}
};

class MismatchedParenthesisException : public ArExpException
{
public:
	/// <summary>
	/// Mismatch Parenthesis close tag " (, {, [ ] } )"
	/// </summary>
	/// <returns></returns>
	virtual const char* what() const throw()
	{
		return "Mismatched parenthesis.";
	}
};

class NotBalanceBracketExpressionException : public ArExpException
{
public:
	/// <summary>
	/// Not balanced bracket exception "([), {[},..."
	/// </summary>
	/// <returns></returns>
	virtual const char* what() const throw()
	{
		return "Not balanced bracket.";
	}
};

class InvalidExpressionException : public ArExpException
{
public:
	/// <summary>
	/// invalid expression ex: 2 3 3 +, 2 + 4 +,...
	/// </summary>
	/// <returns></returns>
	virtual const char* what() const throw()
	{
		return "Invalid expression.";
	}
};

class InvalidDoubleException : public ArExpException
{
/// <summary>
/// Following requirements, double value must accept two decimal digits after point symbol
/// </summary>
public:
	virtual const char* what() const throw()
	{
		return "Invalid Double expression.";
	}
};

#pragma endregion


/// <summary>
/// ArHelper provides utilites to process string, double
/// </summary>
class ArHelper
{
public:

	static std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
	{
		/// <summary>
		/// Trim all space, tab, end character both right and left  [ a b c ] => [a b c]
		/// </summary>
		/// <param name="str">String need to process</param>
		/// <param name="chars">Pattern to remove both right and left</param>
		/// <returns></returns>
		return ltrim(rtrim(str, chars), chars);
	}

	static std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
	{
		/// <summary>
		/// Trim Left side of the string str
		/// </summary>
		/// <param name="str"></param>
		/// <param name="chars"></param>
		/// <returns></returns>
		str.erase(0, str.find_first_not_of(chars));
		return str;
	}

	static std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
	{
		/// <summary>
		/// Trim right side
		/// </summary>
		/// <param name="str"></param>
		/// <param name="chars"></param>
		/// <returns></returns>
		str.erase(str.find_last_not_of(chars) + 1);
		return str;
	}
	static std::string filter_bracket(std::string& str)
	{
		/// <summary>
		/// Apply filter to remove all character except bracket character () [] {}. This function 's use to validate balanced bracket/
		/// </summary>
		/// <param name="str"></param>
		/// <returns></returns>
		string balance_filter = "";
		for (int i = 0; i < str.size(); i++) {
			char c = str[i];
			if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}')
			{
				balance_filter += c;
			}
		}
		return balance_filter;
	}
	std::string getPoint(std::string x)
	{
		return x.substr(x.find(".") + 1, x.length());
	}

	static double parseTwoPointDouble(string x) {
		/// <summary>
		/// Return the substring with two decimal digits
		/// Return {exception() } if the number of digits after point symbol > 2
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		if (x.find(".") != std::string::npos) {
			int p_idx = x.find(".");


			int max_limit = x.find(".") + 2;
			//1.234
			if (max_limit < x.length() - 1) {
				//cout << "max_limit " << max_limit << endl;
				throw  exception("Invalid double ");
			}
			max_limit = (max_limit > x.length() ? x.length() : max_limit);

			for (int i = 0; i < x.length(); i++) {
				if (!isdigit(x[i]) && x[i] != '.') {
					throw exception("Invalid double");
					return -1;
				}
			}
			string sub_d = x.substr(0, max_limit + 1);
			return stod(sub_d);
		}
		else {
			return stod(x);
		}
	}
};




class ArExp
{
/// <summary>
/// ArExp class: represent save the input expression.
/// </summary>
protected:
	string _exp = "";
	ExpForm _exp_form;
public:
	ArExp() { _exp = "0"; _exp_form = ExpForm::INFIX_EXP; }

	ArExp(string exp) {
		this->set_exp_str(exp);
		_exp_form = (ExpForm::INFIX_EXP);
	}

	

	ArExp(string exp, ExpForm form) {
		_exp = (exp);
		_exp_form = (form);
	}

	void set_exp_str(string exp) {
		_exp = exp;
		this->trim_space(); // chuan hoa 
	}

	ExpForm getFormType() {
		return this->_exp_form;
	}

	void trim_space()
	{
		/// <summary>
		/// trim space to avoid unexpected at left or right side.
		/// </summary>
		this->_exp = ArHelper::trim(_exp);
		//_exp.erase(remove(_exp.begin(), _exp.end(), ' '), _exp.end());
	}

	string to_string() {
		/// <summary>
		/// return string expression
		/// </summary>
		/// <returns></returns>
		return this->_exp;
	}


	/// <summary>
	/// Overloading operation for checking equaltion
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	friend inline bool operator==(const ArExp& lhs, const ArExp& rhs) {
		return (lhs._exp == rhs._exp && lhs._exp_form == rhs._exp_form);
	}

	friend inline bool operator==(const ArExp& lhs, const char*& rhs) {
		return (lhs == ArExp(rhs));
	}

	friend inline bool operator==(const ArExp& lhs, const string& rhs) {
		return (lhs == ArExp(rhs));
	}

	friend inline bool operator==(const char*& lhs, const ArExp& rhs) {
		return (ArExp(lhs) == rhs);
	}
	friend inline bool operator==(const string& lhs, const ArExp& rhs) {
		return (ArExp(lhs) == rhs);
	}
};


class ArExpConverter
{
/// <summary>
/// ArExpConverter: Class provides some methods to convert infix-postfix, evaluate the postfix expression
/// </summary>
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

	/// <summary>
	/// Function to caculate the expression. If the expression is infix_exp, this will convert to posfix and caculate the result. 
	/// Exception:
	///		- InvalidDoubleException: if double values have more than 2 decimal digits
	///		- InvalidExpressionException: if expression is invalid
	/// </summary>
	/// <returns></returns>
	double evaluate() {
		double result = 0;

		string temp = "";
		double cur_tk_value = 0;

		stack<double> evalutate;
		string tok = "";


		if (_arexp.getFormType() == ExpForm::INFIX_EXP) {
			_arexp = this->infix_to_postfix();
		}

		string expr = _arexp.to_string();

		int i = 0;
		vector<string> O;
		while ((tok = next_token(expr, i)) != "") {
			if (tok == " ") {
				continue;
			}
			O.push_back(tok);
		}
		for (int i = 0; i < O.size(); i++) {
			string cur_tk_str = O[i];
			if (!isOperator(cur_tk_str[0])) {
				try {
					cur_tk_value = ArHelper::parseTwoPointDouble(cur_tk_str);
					evalutate.push(cur_tk_value);
				}
				catch (exception e) {
					throw InvalidDoubleException();
				}
			}
			else {
				if (evalutate.size() < 2) {
					throw InvalidExpressionException();
				}

				double val1 = evalutate.top();
				evalutate.pop();
				double val2 = evalutate.top();
				evalutate.pop();
				switch (cur_tk_str[0])
				{
				case '+': evalutate.push(val2 + val1); break;
				case '-':  evalutate.push(val2 - val1); break;
				case '*':  evalutate.push(val2 * val1); break;
				case '/':  evalutate.push(val2 / val1); break;
				case '^':  evalutate.push(pow(val2, val1)); break;
				}
			}
			temp += " " + O[i];
		}
		if (evalutate.size() != 1) {
			throw InvalidExpressionException();
		}
		else {
			result = evalutate.top();
		}
		return result;
	}

	// no use with the requirements
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

	/// <summary>
	/// Parse and get the next token (operants or operators from expression)
	/// ex: str= 1 * 23 + 3
	/// next_token(str, i) = 1, next_token(str, i) = 23; next_token(str, i) = +;  next_token(str, i) = 3 
	/// </summary>
	/// <param name="str"></param> 
	/// <param name="i"></param>
	/// <returns></returns>
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

	/// <summary>
	/// check the expression have all blanced brackets
	/// </summary>
	/// <param name="str_expr">Expression string</param>
	/// <returns>true: balanced, false - not balanced</returns>
	bool areBracketsBalanced(string  str_expr)
	{
		string expr = ArHelper::filter_bracket(str_expr);

		stack<char> s;
		char x;
		for (int i = 0; i < expr.length(); i++)
		{
			if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
			{
				s.push(expr[i]);
				continue;
			}
			if (s.empty()) {
				return false;
			}

			switch (expr[i]) {
			case ')':
				x = s.top();
				s.pop();
				if (x == '{' || x == '[')
					return false;
				break;

			case '}':
				x = s.top();
				s.pop();
				if (x == '(' || x == '[')
					return false;
				break;

			case ']':
				x = s.top();
				s.pop();
				if (x == '(' || x == '{')
					return false;
				break;
			}
		}

		return (s.empty());
	}

	/// <summary>
	/// Check that an operator is preceded by another operator  (1 * + 2)
	/// </summary>
	/// <param name="infix_exp">Ìnix expression</param>
	/// <returns>true - valid, false - invalid operators</returns>
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

	/// <summary>
	/// Replace all { [ to ( and  } ] to ) for easy to implement the algorithms
	/// </summary>
	/// <param name="infix_exp"></param>
	/// <returns></returns>
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


	/// <summary>
	/// Get valid postfix expression. 
	/// </summary>
	/// <param name="O">stack keep process infix expression (no bracket)</param>
	/// <returns>string : postfix expression</returns>
	string get_valid_postfix(vector<string> O) {
		string temp = "";
		double cur_tk_value = 0;
		stack<double> evalutate;
		for (int i = 0; i < O.size(); i++) {
			string cur_tk_str = O[i];

			if (!isOperator(cur_tk_str[0])) {
				//operant
				try {
					cur_tk_value = ArHelper::parseTwoPointDouble(cur_tk_str);
					evalutate.push(cur_tk_value);
				}
				catch (exception e) {
					throw InvalidDoubleException();
				}
			}
			else {
				if (evalutate.size() < 2) {
					throw InvalidExpressionException();
				}

				double val1 = evalutate.top();
				evalutate.pop();
				double val2 = evalutate.top();
				evalutate.pop();
				switch (cur_tk_str[0])
				{
				case '+': evalutate.push(val2 + val1); break;
				case '-':  evalutate.push(val2 - val1); break;
				case '*':  evalutate.push(val2 * val1); break;
				case '/':  evalutate.push(val2 / val1); break;
				case '^':  evalutate.push(pow(val2, val1)); break;
				}
			}
			temp += " " + O[i];
		}
		if (evalutate.size() != 1) {
			throw InvalidExpressionException();
		}

		temp = ArHelper::trim(temp);
		return temp;
	}

	/// <summary>
	/// Infix to posfix
	/// Exception:
	///	- NotBalanceBracketExpressionException: the expression contains not balanced brackets  ( [ )
	/// - InvalidExpressionException: ex: 2 * + 3
	/// - MismatchedParenthesisException: mismatched parenthesis ex: ( ( )  - this is sub case of NotBalanceBracketExpressionException
	/// - InvalidDoubleException: double format not true
	/// </summary>
	/// <returns>return ArExp(postfix_str,  ExpForm::POSTFIX_EXP)</returns>
	ArExp infix_to_postfix() {
		ArExp result;
		string expr = _arexp.to_string();

		if (areBracketsBalanced(expr) == false) {
			throw NotBalanceBracketExpressionException();
		}
		if (basic_validate_infix(expr) == false) {
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
				//Version 1: BUG 2 ^ 2 ^ 2 priority not true

				//while (!S.empty() &&  priority(tok[0]) <= priority(S.top()[0]))
				while (!S.empty() && isOperator(S.top()[0]) && ((leftAssoc(tok[0]) && priority(tok[0]) <= priority(S.top()[0])) || (!leftAssoc(tok[0]) && priority(tok[0]) < priority(S.top()[0]))))
				{
					// ^ begin from right
					string s_top = S.top();
					O.push_back(s_top);
					S.pop();
				}
				S.push(tok);
			}
			else {
				try {
					double cur = ArHelper::parseTwoPointDouble(tok);
					O.push_back(tok);
				}
				catch (exception e) {
					throw InvalidDoubleException();
				}
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

		string temp = get_valid_postfix(O);

#ifdef AR_EXP_DEBUG
		cout << "[" << temp << "]" << endl;
#endif // AR_EXP_DEBUG

		return ArExp(temp, ExpForm::POSTFIX_EXP);
	}

};



#pragma region MAIN
/// <summary>
/// Show helping menu
/// </summary>
/// <param name="name"></param>
static void show_usage(std::string name)
{
	std::cerr << "Usage: A.exe InputPath N Action OuputPath"
		<< "Options:\n"
		<< "\tA.exe: Exe file\n"
		<< "\tInputPath: Path to the \"input.txt\" file\n"
		<< "\tN: an integer, represent the number of expressions from the input.txt file\n"
		<< "\tAction: \n"
		<< "\t\t-c: Caculate the identified expressions\n"
		<< "\t\t-t: Convert infix to postfix\n"

		<< "\tOutputPath: Path to the \"output.txt\" file\n"
		<< std::endl;
}
/// <summary>
/// Read file line by line and save to a vector
/// </summary>
/// <param name="fileName"></param>
/// <param name="vec_str"></param>
/// <returns></returns>
bool read_file(string fileName, std::vector<std::string>& vec_str) {
	std::ifstream in(fileName.c_str());
	if (!in)
	{
		std::cerr << "Cannot open the File : " << fileName << std::endl;
		return false;
	}
	std::string str;
	while (std::getline(in, str))
	{
		if (str.size() > 0)
			vec_str.push_back(str);
	}
	in.close();
	return true;
}

/// <summary>
/// Convert Infix to Postfix features for -t tag
/// </summary>
/// <param name="input"></param>
/// <param name="output"></param>
/// <param name="n"></param>
void convertInfixPostfix(string input = "input.txt", string output = "output.txt", int n = 3) {
	vector<string> input_exprs;
	read_file(input, input_exprs);

	vector<double> output_data;
	std::ofstream oss(output.c_str());

	if (!oss)
	{
		std::cerr << "Cannot open the File : " << output << std::endl;
	}
	std::string str;

#ifdef AR_EXP_DEBUG
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
#endif // AR_EXP_DEBUG

	oss << std::fixed;
	oss << std::setprecision(2);
	for (int i = 0; i < input_exprs.size(); i++) {
		ArExp exp(input_exprs[i]);
		ArExpConverter converter(exp);
		try {
			ArExp exp_post_fix = converter.infix_to_postfix();

			oss << exp_post_fix.to_string() << endl;


#ifdef AR_EXP_DEBUG
			cout << evaluate_result << endl;
#endif
		}
		catch (exception ex) {
#ifdef AR_EXP_DEBUG
			cout << "E" << endl;
#endif			
			oss << "E" << endl;
		}
		if (i == n - 1) {
			break;
		}
	}
	oss.close();
	cout << "Convert prefix to postfix -t" << endl;


}


/// <summary>
/// Caculate the value of infix expression -c tag 
/// </summary>
/// <param name="input"></param>
/// <param name="output"></param>
/// <param name="n"></param>

void caculate(string input = "input.txt", string output = "output.txt", int n = 3) {
	vector<string> input_exprs;
	read_file(input, input_exprs);


	vector<double> output_data;
	std::ofstream oss(output.c_str());

	if (!oss)
	{
		std::cerr << "Cannot open the File : " << output << std::endl;
	}
	std::string str;


	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	oss << std::fixed;
	oss << std::setprecision(2);


	for (int i = 0; i < input_exprs.size(); i++) {
		ArExp exp(input_exprs[i]);
		ArExpConverter converter(exp);
		try {
			ArExp exp_post_fix = converter.infix_to_postfix();
			double evaluate_result = converter.evaluate();

			oss << evaluate_result << endl;
			cout << evaluate_result << endl;
		}
		catch (exception ex) {
			cout << "E" << endl;
			oss << "E" << endl;
		}
		if (i == n - 1) {
			break;
		}
	}
	oss.close();

	cout << "Caculate -c" << endl;
}

int main(int argc, char* argv[]) {
	string input_file = "input.txt";
	string output_file = "output.txt";
	int n = 4;

	//convertInfixPostfix(intput_file, output_file, n);
	//A.exe InputPath N Action OutputPath
	if (argc < 3) {
		show_usage(argv[0]);
		return 1;
	}
	//a.exe input.txt 3 -t output.txt
	// 0	1		2	3	4 => 5
	input_file = argv[1];
	n = stoi(argv[2]);
	string action = argv[3];
	output_file = argv[4];
	if (action == "-c") {
		caculate(input_file, output_file, n);
	}
	else if (action == "-t") {
		convertInfixPostfix(input_file, output_file, n);
	}



	/*
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if ((arg == "-h") || (arg == "--help")) {
			show_usage(argv[0]);
			return 0;
		}
		cout << arg << endl;
	}
	*/

	return 0;
}
#pragma endregion


#pragma once
#include <exception>
using namespace std;

class ArExpException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Mismatched parenthesis.";
	}
};
class MismatchedParenthesisException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Mismatched parenthesis.";
	}
};

class NotBalanceBracketExpressionException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Not balanced bracket.";
	}
};



class InvalidExpressionException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Invalid expression.";
	}
};


class InvalidDoubleException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Invalid Double expression.";
	}
};

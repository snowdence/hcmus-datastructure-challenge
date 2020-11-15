#pragma once
#include <iostream>
#include <string>
using namespace std;
class ArHelper
{
public:
	static std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
	{
		return ltrim(rtrim(str, chars), chars);
	}

	static std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
	{
		str.erase(0, str.find_first_not_of(chars));
		return str;
	}

	static std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
	{
		str.erase(str.find_last_not_of(chars) + 1);
		return str;
	}
	static std::string filter_bracket(std::string& str)
	{
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
};
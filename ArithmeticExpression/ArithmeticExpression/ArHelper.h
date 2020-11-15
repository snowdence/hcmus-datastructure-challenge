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
	std::string getPoint(std::string x)
	{
		return x.substr(x.find(".") +1 , x.length());
	}
	static double parseTwoPointDouble(string x) {
		if (x.find(".") != std::string::npos) {
			int p_idx = x.find(".");
			
			int max_limit = x.find(".") + 2;
			if (max_limit != x.length() - 1) {
				throw  exception("Invalid double ");
			}
			max_limit = (max_limit > x.length() ? x.length() : max_limit);
			
			for (int i = 0; i < x.length(); i++) {
				if (!isdigit(x[i]) && x[i] != '.') {
					throw exception("Invalid double" );
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
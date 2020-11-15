#pragma once
#include <iostream>
#include "ArExpConverter.h"
#include <string>
#include <ostream>	
#include <vector> 
#include <fstream>
#include <iomanip>
#include "ArConfig.h"
using namespace std;
/*
int main()
{
	ArExp exp("[(2.01 + 3.20) * 3 + 2] * 2");
	cout << exp.to_string() << endl;;
	ArExpConverter converter(exp);
	cout << "Convert to postfix: " << endl;
	//cout << converter.infix_to_prefix().to_string() << endl;
	try {
		ArExp converted = converter.infix_to_postfix();
		std::cout << converted.to_string() << endl;
		std::cout << "Evaluate = " << converter.evaluate() << endl;
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


*/

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

	system("pause");
	return 0;
}
#pragma once
#include <iostream>
#include "ArExpConverter.h"

using namespace std;
int main()
{
    ArExp exp("4 4 3 +");
    cout << exp.to_string() << endl;;
    ArExpConverter converter(exp);
    cout << "Convert to postfix: " << endl;
    //cout << converter.infix_to_prefix().to_string() << endl;
    cout <<  "[" <<  converter.infix_to_postfix().to_string() << "]" << endl;

    std::cout << "Arithmetic Expression\n";
    system("pause");
}

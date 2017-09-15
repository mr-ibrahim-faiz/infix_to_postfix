#include "infix_to_postfix.h"

#include<iostream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;

#include<stdexcept>
using std::exception;
using std::runtime_error;

int main()
try
{
	string expression { "" };

	while (true)
	{
		// gets expression from input
		cout << "> ";
		getline(cin, expression);

		// checks if the user want to quit the program
		// exits if the user enters "exit"
		if (expression == "exit")
			break;

		// clear expression
		clear_expression(expression);

		try {
			// converts infix expression to postfix and displays final result
			cout << infix_to_postfix(expression) << endl;
			cout << endl;
		}
		catch (runtime_error& e) {
			cerr << "Error: " << e.what() << endl;
			cerr << endl;
		}

	}

	cout << "\nGoodbye !" << endl;
	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
}
catch (...) {
	cerr << "Error: unknown exception caught." << endl;
}
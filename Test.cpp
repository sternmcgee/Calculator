/*
Stern McGee
Testing file with main()
03/16/17
*/
#include "Parser.h"
#include "Evaluator.h"
#include <iostream>
#include <string>
using namespace std;
int main() {
	try
	{
		char line[100]; string str;
		cout << "Type quit to end program loop." << endl
			<< "Type double can be stored in variables from a to z, " << endl
			<< "but otherwise use a digit 1-9 on command line" << endl;
		while (true) {
			cout << "Enter expression: ";
			cin.get(line, 100);
			cin.ignore(100, '\n');
			str = string(line); //convert line to a string
			if (str == "quit") break;
			cout << "Infix expression: " << str << endl;
			Parser par(str); // new parser
			par.to_postfix(); // convert to postfix form
			par.print_postfix(); // print
			Parser* p = &par;
			Evaluator e(p);
			cout << e.getValue() << endl;
		}
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
	}
	catch (...)
	{
		cerr << "some exception" << endl;
	}
	return 0;
}
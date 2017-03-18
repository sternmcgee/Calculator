/*
Stern McGee
Evaluator Implementation
03/16/17
*/
#include "Evaluator.h"
#include <cmath>
#include <cctype>
#include <iostream>
#include <stdlib.h>
using namespace std;

bool Evaluator::isOperator(Parser::enumTokens token)
{
	return (token == Parser::EXP || token == Parser::MULT || token == Parser::DIV || token == Parser::PLUS
		|| token == Parser::MINUS || token == Parser::UNARY_MINUS);
}

double Evaluator::define_var(char val)
{
	double num;
	cout << "What is the value of " << val << endl;
	if (cin >> num)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		return num;
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		throw runtime_error("invalid value");
	}
}

double Evaluator::eval(double a, Parser::enumTokens op)
{
	if (op == Parser::UNARY_MINUS) return -1 * a;
	return 0;
}

double Evaluator::eval(double a, double b, Parser::enumTokens op)
{
	if (op == Parser::EXP)
		return static_cast<double>(pow(static_cast<double>(a), b));
	else if (op == Parser::MULT)
		return a*b;
	else if (op == Parser::DIV)
		if (b != 0) return a / b;
		else throw DivisionByZero();
	else if (op == Parser::PLUS)
		return a + b;
	else if (op == Parser::MINUS)
		return a - b;
	return 0;
}

double Evaluator::getValue()
{
	Parser::enumTokens token;
	double a, b;
	LinkedQueue<char>& postfix = parser->get_postfix();
	while (!postfix.isEmpty())
	{
		try
		{
			token = parser->getToken(postfix.dequeue());
		}
		catch (...)
		{
			cerr << "postfix queue error " << endl;
		}

		if (isOperator(token))
		{
			try
			{
				if (token == Parser::UNARY_MINUS)
				{
					a = valStack.pop();
					valStack.push(eval(a, token));
				}
				else
				{
					a = valStack.pop();
					b = valStack.pop();
					valStack.push(eval(b, a, token));
				}
			}
			catch (DivisionByZero& e)
			{
				cerr << e.what() << endl;
				return 0;
			}
			catch (...)
			{
				cerr << "Wrong operand(s)" << endl;
				return 0;
			}
		}
		else if (token != Parser::END)
		{
			try
			{
				double num;
				int castint;
				char val = parser->get_val();
				if (isalpha(val))  num = define_var(val);
				else
				{
					if (!isdigit(val)) cerr << "Value(s) is not a digit" << endl;
					castint = val - '0';		//conversion of char to int
					num = static_cast<double>(castint);
				}

				valStack.push(num);
			}
			catch (...)
			{
				cerr << "Bad value: " << parser->get_val() << endl;
			}
		}
	}		//end of while loop
	try
	{
		return valStack.pop();		//final value is popped and returned
	}
	catch (...)
	{
		cerr << "Bad expression" << endl;
	}
	return 0;
}
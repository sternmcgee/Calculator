/*
Stern McGee
Evaluator Header File
03/16/17
*/
#ifndef EVAL_H
#define EVAL_H

#include "Parser.h"

class Evaluator
{
	class DivisionByZero : public runtime_error {
	public: DivisionByZero() :
		runtime_error("Division by zero") {}
	};
	LinkedStack<double> valStack;
	Parser* parser;
	//returns true if token is an operator
	bool isOperator(Parser::enumTokens token);
	//eval function for UNARY_MINUS (single operand)
	double eval(double a, Parser::enumTokens op);
	//eval function for other operators (two operands)
	double eval(double a, double b, Parser::enumTokens op);
public:
	//constructor
	Evaluator(Parser* p) : parser(p), valStack() { parser->is_balanced(); }
	//returns the value of the expression
	double getValue();
	//defines the variable from user before evaluation
	double define_var(char val);

};
#endif
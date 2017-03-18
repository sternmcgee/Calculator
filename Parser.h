/*
Stern McGee
Parser Header File
03/16/17
*/
#ifndef PARSER_H
#define PARSER_H

#include "Stack.h"
#include "Queue.h"
#include <vector>
#include <string>
class Parser
{
	char curval;		//current value
	static const char* delimiters;
	const char* tokens;		//array of tokens
	int length;		//length of expression
	LinkedStack<int> opStack;		//operator stack
	LinkedQueue<char> postfix;		//postfix queue
	class Precedence
	{
	public: int input, stack;
			Precedence(int i = 0, int s = 0) : input(i), stack(s) {}
	};
	static const Precedence precTable[];	//precedence table
	static const char opTable[];		//conversion table
public:
	//token enumeration
	enum enumTokens { END, VALUE, LPAREN, RPAREN, EXP, MULT, DIV, PLUS, MINUS, UNARY_MINUS };
	//returns the enumeration of the token
	enumTokens getToken(int c, enumTokens prevToken = VALUE);
	//constructor
	Parser(string str) : opStack(), postfix()
	{
		tokens = str.c_str();		//convert tokens to c string
		length = str.size();		//length of string expression
		opStack.push(END);		//initialization of opStack
	}
	//checks whether parenthesis are balanced and whether expression has an operator
	bool is_balanced();
	//converts expression (string) from infix form to postfix form
	void to_postfix();
	//prints postfix form
	void print_postfix();
	//get postfix
	LinkedQueue<char>& get_postfix() { return postfix; }
	//getter for the current value
	char get_val() { return curval; }
};
#endif
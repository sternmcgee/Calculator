/*
Stern McGee
Parser Implementation
03/16/17
*/
#include "Parser.h"
#include <iostream>
//initialization of constants, delimiters, and precedence table
const char* Parser::delimiters = "+-*/^() ";
const char Parser::opTable[] = { '\0', '$', '(', ')', '^', '*', '/', '+', '-', '~' };
const Parser::Precedence Parser::precTable[] = {
	Precedence(0,-1),		//END
	Precedence(0, 0),		//VALUE
	Precedence(100, 0),		//LPAREN
	Precedence(0, 99),		//RPAREN
	Precedence(6, 5),		//EXP
	Precedence(3, 4),		//MULT
	Precedence(3, 4),		//DIV
	Precedence(1, 2),		//PLUS
	Precedence(1, 2),		//MINUS
	Precedence(8, 7),		//UNARY_MINUS
};

bool Parser::is_balanced()
{
	int l_count = 0;
	int r_count = 0;
	int op_count = 0;

	for (int i = 0; i < Parser::length; ++i)
	{
		if (Parser::tokens[i] == '(') ++l_count;
		if (Parser::tokens[i] == ')') ++r_count;
		if (Parser::tokens[i] == '^' || Parser::tokens[i] == '*' || Parser::tokens[i] == '/'
			|| Parser::tokens[i] == '+' || Parser::tokens[i] == '-' || Parser::tokens[i] == '~') ++op_count;
	}	

	if (l_count != r_count)
	{
		throw runtime_error("Parenthesis are not balanced.");
		return false;
	}
	else if (op_count == 0)
	{
		throw runtime_error("No operator found in expression.");
		return false;
	}
	else return true;
}
Parser::enumTokens Parser::getToken(int c, enumTokens prevToken)
{
	if (c == '\0') return END;
	//token is a delimiter
	else if (c == '^') return EXP;
	else if (c == '*') return MULT;
	else if (c == '/') return DIV;
	else if (c == '+') return PLUS;
	else if (c == '(') return LPAREN;
	else if (c == ')') return RPAREN;
	else if (c == '~') return UNARY_MINUS;
	else if (c == '-')
	{
		if (prevToken == VALUE || prevToken == RPAREN) return MINUS;
		else return UNARY_MINUS;
	}
	else
	{
		curval = c;		//variable or number
		return VALUE;
	}
}

void Parser::to_postfix()
{
	int op;
	char c;
	enumTokens newToken = END;
	int tokenIndex = 0;
	//do while loop
	do
	{
		c = tokens[tokenIndex];
		while (c == ' ') c = tokens[++tokenIndex];
		newToken = getToken(c, newToken);
		switch (newToken)
		{
		case VALUE:
			postfix.enqueue(curval);
			break;
		case RPAREN:
			op = opStack.top();
			while (op != LPAREN)
			{
				postfix.enqueue(opTable[op]);
				opStack.pop();
				op = opStack.top();
			}
			opStack.pop();		//remove LPAREN
			break;
		case LPAREN:
			opStack.push(newToken);
			break;
		case END:
			while (!opStack.isEmpty())
			{
				op = opStack.top();
				postfix.enqueue(opTable[op]);
				opStack.pop();
			}
			break;
		case EXP:case MULT:case DIV:case PLUS:
		case MINUS:case UNARY_MINUS:
			op = opStack.top();
			while (precTable[newToken].input <= precTable[op].stack)
			{
				postfix.enqueue(opTable[op]);
				opStack.pop();
				op = opStack.top();
			}
			opStack.push(newToken);
			break;
		default:
			cerr << "Invalid token: " << newToken << endl;
			newToken = END;
			break;
		}
		++tokenIndex;
	} while (newToken != END);
	}

void Parser::print_postfix()
{
	LinkedQueue<char> newQueue;
	char item;
	while (!postfix.isEmpty())
	{
		item = static_cast<char>(postfix.dequeue());	//test without the static cast
		cout << item;
		newQueue.enqueue(item);
	}
	cout << endl;
	postfix = newQueue;
}
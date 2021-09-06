/* ========================  RECURSE CALCULATOR ========================
AUTHOR : Jonayed Mohiuddin
EMAIL  : jonayedmohiuddin@gmail.com
GITHUB : https://github.com/JonayedMohiuddin/
FLOW CHART : Look at bottom.
========================================================================= */

/*
[1]Adding Comments.
[2]Separating Classes.
[3]Adding more operators.
*/

#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

/*#####################
##### TOKEN TYPES #####
#####################*/

enum TokenTypes
{
	UNKNOWN = -2,		// -2 UNKNOWN
	_EOF = -1,			// -1 '\0'
	OP_START = 0,
	PLUS,		      	//  1 '+'
	MINUS,				//  2 '-'
	MULTIPLY,			//  3 '*'
	DIVIDE,				//  4 '/'
	EXPONENTIAL,		//  5 '^'
	MODULO,				//  6 '%'
	BRACKET_START,      //  7 '('
	BRACKET_END,		//  8 ')'
	OP_END,
	NUMBER = 20,		// 20 '+'
	MAXTOKEN_NUMBER
};

/*###############
##### TOKEN #####
###############*/

class Token
{
public:
	TokenTypes tokenType;
	string tokenValue;

	Token(){};

	Token(TokenTypes tokenType)
	{
		this->tokenType = tokenType;
	}

	Token(TokenTypes tokenType, char tokenValue)
	{
		this->tokenType = tokenType;
		this->tokenValue = tokenValue;
	}

	Token(TokenTypes tokenType, string tokenValue)
	{
		this->tokenType = tokenType;
		this->tokenValue = tokenValue;
	}
};

/*###############
##### LEXER #####
###############*/

class Lexer
{
private:
	string expression;
	char curChar;

	int curPos;
	int startPos;
	int endPos;

public:
	Lexer()
	{
		this->expression = "";
		curChar = ' ';
		curPos = 0;
	}

	Lexer(string &expression)
	{
		this->expression = expression;
		curChar = ' ';
		curPos = -1;
		nextChar();
	}

private:
	void nextChar()
	{
		curPos++;
		if (curPos <= expression.length())
			curChar = expression[curPos];
		else
			curChar = '\0';
	}

	char peekChar()
	{
		if ((curPos + 1) <= expression.length())
			return expression[curPos + 1];
		else
			return '\0';
	}

	void skipWhitespace()
	{
		while (curChar == ' ' || curChar == '\t' || curChar == '\r')
		{
			nextChar();
		}
	}

	void abort(string errMsg)
	{
		cout << errMsg;
		exit(EXIT_FAILURE);
	}

public:
	Token getToken()
	{
		skipWhitespace();

		Token token;

		if (curChar == '+')
		{
			token = Token(PLUS, curChar);
		}

		else if (curChar == '-')
		{
			token = Token(MINUS, curChar);
		}

		else if (curChar == '*')
		{
			token = Token(MULTIPLY, curChar);
		}

		else if (curChar == '/')
		{
			token = Token(DIVIDE, curChar);
		}

		else if (curChar == '^')
		{
			token = Token(EXPONENTIAL, curChar);
		}

		else if (curChar == '%')
		{
			token = Token(MODULO, curChar);
		}

		else if (isdigit(curChar))
		{
			startPos = curPos;

			while (isdigit(peekChar()))
				nextChar();

			if (peekChar() == '.')
			{
				nextChar();
			}

			while (isdigit(peekChar()))
				nextChar();

			string tokenValue = expression.substr(startPos, curPos - startPos + 1); // Get the substring.
			token = Token(NUMBER, tokenValue);
		}

		else if (curChar == '\0')
		{
			token = Token(_EOF);
		}

		else
		{
			token = Token(UNKNOWN);
		}

		nextChar();
		return token;
	}
};

/*###########################
##### CALCULATOR (MAIN) #####
###########################*/
// Actually a parser.

class Calculator
{
	string input;
	Lexer lexer;
	double result;

	Token curToken;
	Token peekToken;

private:
	void read()
	{
		cin >> input;
	}

	void nextToken()
	{
		curToken = peekToken;
		peekToken = lexer.getToken();
	}

	bool isCurToken(TokenTypes tokenType)
	{
		return (tokenType == curToken.tokenType) ? true : false;
	}

	bool isPeekToken(TokenTypes tokenType)
	{
		return (tokenType == peekToken.tokenType) ? true : false;
	}

	void abort(string message)
	{
		cout << message << endl;
		exit(EXIT_FAILURE);
	}

	// expression ::= term {( "-" | "+" ) term}
	double expression()
	{
		cout << "~ > EXPRESSION (" << curToken.tokenValue << ")" << endl;

		double number = term();

		// Can have 0 or more +/- and expressions.
		while (isCurToken(PLUS) || isCurToken(MINUS))
		{
			if (isCurToken(PLUS))
			{
				nextToken();
				number += term();
			}
			else if (isCurToken(MINUS))
			{
				nextToken();
				number -= term();
			}
		}

		return number;
	}

	// term ::= unary {( "*" | "/" ) unary}
	double term()
	{
		cout << "~ > ^   TERM (" << curToken.tokenValue << ")" << endl;

		double number = unary();

		// Can have 0 or more * or / and expressions.
		while (isCurToken(MULTIPLY) || isCurToken(DIVIDE))
		{
			if (isCurToken(MULTIPLY))
			{
				nextToken();
				number *= unary();
			}
			else if (isCurToken(DIVIDE))
			{
				nextToken();
				number /= unary();
			}
		}

		return number;
	}

	// unary ::= ["+" | "-"] number
	double unary()
	{
		cout << "~ > ^^  UNARY (" << curToken.tokenValue << ")" << endl;

		double number;
		short int sign = 1;

		while (isCurToken(PLUS) || isCurToken(MINUS))
		{
			if (isCurToken(PLUS))
			{
				nextToken(); // Skip the PLUS
			}
			else if (isCurToken(MINUS))
			{
				sign *= -1;
				nextToken();
			}
		}

		number = (double)sign * getNumber();
		nextToken();

		return number;
	}

	// number
	double getNumber()
	{
		cout << "~ > ^^^ NUMBER (" << curToken.tokenValue << ")" << endl;

		if (!isCurToken(NUMBER))
			abort("!! Expected a number");

		return std::stod(curToken.tokenValue);
	}

public:
	void calculate(string input = "")
	{
		if (input == "")
			input = this->input;

		cout << input << endl;

		lexer = Lexer(input);

		nextToken();
		nextToken();

		result = 0;
		result = expression();
	}

	double answer()
	{
		return result;
	}
};

/*#######################
##### MAIN FUNCTION #####
#######################*/

int main()
{
	cout << endl;
	string exp = "1000/4*-2+2*5*6-234+--5000";
	Calculator calculator;
	calculator.calculate(exp);
	cout << calculator.answer() << endl;

	return 0;
}

/*
FLOW CHART:
	INPUT
	 ||
	 \/
+-----------+
|   LEXER   |  <<-------------------+
+-----------+                       |
	 ||                             |
	 \/                             |
	TOKEN -> [ TokenTypes ]         |
	 ||                             |
	 \/							    |
+------------+                      |
| CALCULATOR |  >>--- NEXT TOKEN ---+ [calls]
+------------+
	 ||
	 \/
	RESULT
*/
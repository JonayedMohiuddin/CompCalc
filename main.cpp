/* ================= ADVANCED EXPRESSION - CALCULATOR =================
AUTHOR : Jonayed Mohiuddin
EMAIL  : jonayedmohiuddin@gmail.com
GITHUB : https://github.com/JonayedMohiuddin/
FLOW CHART : Look at bottom.
======================================================================= */

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

using std::to_string;  // Converts int to string
using std::stod;       // Converst string to decimal

/*#####################
##### TOKEN TYPES #####
#####################*/

enum TokenTypes
{
	UNKNOWN = -2,       // -2 UNKNOWN
	_EOF = -1,          // -1 '\0'
	OP_START = 0,       // Just to mark the start of operator enums in loops if needed
	ADD,                //  1 '+'
	SUBTRACT,           //  2 '-'
	MULTIPLY,           //  3 '*'
	DIVIDE,             //  4 '/'
	EXPONENTIAL,        //  5 '^'
	MODULO,             //  6 '%'
	BRACKET_START,      //  7 '('
	BRACKET_END,        //  8 ')'
    LOG,                //  9 'log'
    LN,                 // 10 'ln'
    SIN,                // 11 'sin'
    COS,                // 12 'cos'
    TAN,                // 13 'tan'
	OP_END,             // Just to mark the end of operator enums in loops if needed
	NUMBER = 20,        // 20 '+'
	MAXTOKEN_NUMBER
};

/*###############
##### TOKEN #####
###############*/

class Token
{
public:
	TokenTypes type;
	double value;

    Token() {};

	Token(TokenTypes type)
	{
		this->type = type;
        this->value = -1;
	}

    Token(TokenTypes type, double value)
	{
		this->type = type;
		this->value = value;
	}

    int getTokenType(string &token)
    {
        if(token == "log") return LOG;
        else if(token == "ln")  return LN;
        else if(token == "sin") return SIN;
        else if(token == "cos") return COS;
        else if(token == "tan") return TAN;
        else                    return UNKNOWN;
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
			token = Token(ADD, curChar);
		}

		else if (curChar == '-')
		{
			token = Token(SUBTRACT, curChar);
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

			double value = stod(expression.substr(startPos, curPos - startPos + 1)); // Get the number from the substring.
			token = Token(NUMBER, value);
		}

        else if (isalpha(curChar))
		{
			startPos = curPos;

            while (isalpha(peekChar()))
                nextChar();

            string tokenText = expression.substr(startPos, curPos - startPos + 1);
            TokenTypes tokenType = (TokenTypes) token.getTokenType(tokenText);

            token = Token(tokenType);
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

	bool isCurToken(TokenTypes type)
	{
		return (type == curToken.type) ? true : false;
	}

	bool isPeekToken(TokenTypes type)
	{
		return (type == peekToken.type) ? true : false;
	}

	void abort(string message)
	{
		cout << message << endl;
		exit(EXIT_FAILURE);
	}

	// expression ::= term {( "-" | "+" ) term}
	double expression()
	{
		cout << "~ > EXPRESSION (" << curToken.value << ")" << endl;

		double number = term();

		// Can have 0 or more +/- and expressions.
		while (isCurToken(ADD) || isCurToken(SUBTRACT))
		{
			if (isCurToken(ADD))
			{
				nextToken();
				number += term();
			}
			else if (isCurToken(SUBTRACT))
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
		cout << "~ > ^   TERM (" << curToken.value << ")" << endl;

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
		cout << "~ > ^^  UNARY (" << curToken.value << ")" << endl;

		double number;
		short int sign = 1;

		while (isCurToken(ADD) || isCurToken(SUBTRACT))
		{
			if (isCurToken(ADD))
			{
				nextToken(); // Skip the ADD
			}
			else if (isCurToken(SUBTRACT))
			{
				sign *= -1;
				nextToken();
			}
		}

		number = (double)sign * primary();
		nextToken();

		return number;
	}

	// number
	double primary()
	{
		cout << "~ > ^^^ NUMBER (" << curToken.value << ")" << endl;

		if (!isCurToken(NUMBER))
			abort("!! Expected a number");

		return curToken.value;
	}

public:
	double evaluate(string input = "")
	{
		if (input == "")
			input = this->input;

		cout << input << endl;

		lexer = Lexer(input);

		nextToken();
		nextToken();

		result = expression();

        return result;
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
	// string exp = "1000/4*-2+2*5*6-234+--5000";
    string exp = "log ln sin cos tan";
	Lexer lexer(exp);
    cout << exp                        << endl;
    cout << (int)lexer.getToken().type << endl;
    cout << (int)lexer.getToken().type << endl;
    cout << (int)lexer.getToken().type << endl;
    cout << (int)lexer.getToken().type << endl;
    cout << (int)lexer.getToken().type << endl;
    
    //Calculator calculator;
	//cout << calculator.evaluate(exp) << endl;

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
     \/                             |
+------------+                      |
| CALCULATOR |  >>--- NEXT TOKEN ---+ [calls]
+------------+
     ||
	 \/
	RESULT
*/

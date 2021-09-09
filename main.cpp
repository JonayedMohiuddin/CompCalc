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
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::stod;      // Converst string to decimal
using std::to_string; // Converts int to string

/*#####################
##### TOKEN TYPES #####
#####################*/

enum TokenTypes
{
    UNKNOWN = -2,  // -2 UNKNOWN
    _EOF = -1,     // -1 '\0'
    OP_START = 0,  // Just to mark the start of operator enums in loops if needed
    PLUS,          //  1 '+'
    MINUS,         //  2 '-'
    MULTIPLY,      //  3 '*'
    DIVIDE,        //  4 '/'
    EXPONENTIAL,   //  5 '^'
    MODULO,        //  6 '%'
    BRACKET_START, //  7 '('
    BRACKET_END,   //  8 ')'
    LOG,           //  9 'log'
    LN,            // 10 'ln'
    SIN,           // 11 'sin'
    COS,           // 12 'cos'
    TAN,           // 13 'tan'
    OP_END,        // Just to mark the end of operator enums in loops if needed
    NUMBER = 20,   // 20 '+'
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

    Token(){};

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
        if (token == "log")
            return LOG;
        else if (token == "ln")
            return LN;
        else if (token == "sin")
            return SIN;
        else if (token == "cos")
            return COS;
        else if (token == "tan")
            return TAN;
        else
            return UNKNOWN;
    }

    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // FOR DEBUG PURPOSE
    string getTokenTypeString()
    {
        string tokenTypes[MAXTOKEN_NUMBER];
        tokenTypes[PLUS] = "PLUS";
        tokenTypes[MINUS] = "MINUS";
        tokenTypes[MULTIPLY] = "MULTIPLY";
        tokenTypes[DIVIDE] = "DIVIDE";
        tokenTypes[EXPONENTIAL] = "EXPONENTIAL";
        tokenTypes[MODULO] = "MODULO";
        tokenTypes[BRACKET_START] = "BRACKET_START";
        tokenTypes[BRACKET_END] = "BRACKET_END";
        tokenTypes[LOG] = "LOG";
        tokenTypes[LN] = "LN";
        tokenTypes[SIN] = "SIN";
        tokenTypes[COS] = "COS";
        tokenTypes[TAN] = "TAN";
        tokenTypes[NUMBER] = "NUMBER";

        if(type == _EOF)
            return "EOF";
        else if(type == UNKNOWN)
            return "UNKNOWN";
        else
            return tokenTypes[type];
        
    }
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
};

/*###########################################
##### TOKEN TYPES PRINTER DEBUG PURPOSE #####
###########################################*/

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

        else if (curChar == '(')
        {
            token = Token(BRACKET_START, curChar);
        }

        else if (curChar == ')')
        {
            token = Token(BRACKET_END, curChar);
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
            TokenTypes tokenType = (TokenTypes)token.getTokenType(tokenText);

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
    double expression(int depth = 0)
    {
        cout << " |\\    EXPRESSION (" << curToken.getTokenTypeString() << ")" << endl;
        
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

    // term ::= unary {( "*" | "/" | "%" | "^" | "") unary}
    double term()
    {
        cout << " | \\   TERM (" << curToken.getTokenTypeString() << ")" << endl;

        double number = unary();

        // Can have 0 or more * or / and expressions.
        while (isCurToken(MULTIPLY) || isCurToken(DIVIDE) || isCurToken(MODULO) || isCurToken(EXPONENTIAL) || isCurToken(BRACKET_START))
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
            else if (isCurToken(MODULO))
            {
                nextToken();
                number = (int)number % (int)unary();
            }
            else if (isCurToken(EXPONENTIAL))
            {
                nextToken();
                number = pow(number, unary());
            }
            else if (isCurToken(BRACKET_START))
            {
                nextToken();
                number *= unary();
            }
        }

        return number;
    }

    // unary ::= ["+" | "-"] primary
    double unary()
    {
        cout << " |  \\  UNARY (" << curToken.getTokenTypeString() << ")" << endl;

        double number = 0;
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

        number = (double)sign * primary();
        nextToken();

        return number;
    }

    // primary ::= NUMBER | "("  expression  ")" | function ( NUMBER | "("  expression  ")" )
    double primary()
    {
        cout << " |___\\ PRIMARY (" << curToken.getTokenTypeString() << ")" << endl;

        double number = 0;

        if (isCurToken(NUMBER))
        {
            number = curToken.value;
        }
        else if(isCurToken(BRACKET_START))
        {
            nextToken();
            number = expression(0);
        }
        else if(isCurToken(BRACKET_END))
        {
            nextToken();
            return number;
        }
        else
        {
            number = prededefinedOperations();
        }

        return number;
    }

    double prededefinedOperations()
    {
        double number = 0;

        if (isCurToken(LOG))
        {
            nextToken();
            number = log10(primary());
        }
        else if(isCurToken(LN))
        {
            nextToken();
            number = log(primary());
        }
        else if(isCurToken(SIN))
        {
            nextToken();
            number = sin(primary());
        }
        else if(isCurToken(COS))
        {
            nextToken();
            number = cos(primary());
        }
        else if(isCurToken(TAN))
        {
            nextToken();
            number = tan(primary());
        }

        return number;
    }

public:
    double evaluate(string input = "")
    {
        if (input == "")
            input = this->input;

        cout << "\nPlease ignore." << endl;
        cout << "########### DEBUG TREE (START): ###########\n";
        cout << "Input[In Calculator] = " << input << endl;

        lexer = Lexer(input);

        nextToken();
        nextToken();

        result = expression();

        cout << "########### ::DEBUG TREE (END)  ###########\n\n";

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
    string exp = "";
    cout << "\nInput = ";
    getline(cin, exp);

    Calculator calculator;
    
    double answer = calculator.evaluate(exp);

    cout << "Input  = " << exp << endl;
    cout << "Answer = " << answer << endl;

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
    AST TREE
     ||
     \/
+------------+
| CALCULATOR |  
+------------+   
     ||
     \/
	RESULT
*/

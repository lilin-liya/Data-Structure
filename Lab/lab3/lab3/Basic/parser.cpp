#include <iostream>
#include <string>
#include "error.h"
#include "exp.h"
#include "parser.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "statement.h"

using namespace std;

string insenstr(string str)
{
   string result = str;
   for (int i = 0; i < str.length(); ++i)
   {
      if (str[i] >= 'a' && str[i] <= 'z')
      {
         result[i] = result[i] - 32;
      }
   }
   return result;
}

Expression *parseExp(TokenScanner & scanner) 
{
   Expression *exp = readE(scanner);
   if (scanner.hasMoreTokens()) 
   {
      error("parseExp: Found extra token: " + scanner.nextToken());
   }
   return exp;
}

Expression *readE(TokenScanner & scanner, int prec) 
{
   Expression *exp = readT(scanner);
   string token;
   while (true) 
   {
      token = scanner.nextToken();
      int newPrec = precedence(token);
      if (newPrec <= prec) 
         break;
      Expression *rhs = readE(scanner, newPrec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner.saveToken(token);
   return exp;
}

Expression *readT(TokenScanner & scanner) 
{
   string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type == WORD) 
      return new IdentifierExp(token);
   if (type == NUMBER) 
      return new ConstantExp(stringToInteger(token));
   if (token != "(") 
      error("Illegal term in expression");
   Expression *exp = readE(scanner);
   if (scanner.nextToken() != ")") 
   {
      error("Unbalanced parentheses in expression");
   }
   return exp;
}

int precedence(string token) 
{
   if (token == "+" || token == "-") 
      return 2;
   if (token == "*" || token == "/") 
      return 3;
   return 0;
}

Statement * parseStatement (TokenScanner & scanner) 
{
	string token = scanner.nextToken();
	if (insenstr(token) == "REM") 
      return new RemStmt (scanner);
	else if (insenstr(token) == "PRINT") 
      return new PrintStmt (scanner);
	else if (insenstr(token) == "INPUT") 
      return new InputStmt (scanner);
	else if (insenstr(token) == "LET")	
      return new LetStmt(scanner);
	else if (insenstr(token) == "GOTO") 
      return new GotoStmt(scanner);
	else if (insenstr(token) == "IF") 
      return new IfStmt(scanner);
	else if (insenstr(token) == "END") 
      return new EndStmt(scanner);
}

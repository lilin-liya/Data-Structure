#include <iostream>
#include <fstream>
#include <string>
#include "strlib.h"
#include "tokenscanner.h"
#include "error.h"
#include <vector>

using namespace std;

/*In this homework,since I get in touch with expression trees at the first time,
so I just use the three classes in the reference book to solve the problem.
I modified some of the codes in the book to reach the goal.*/

enum ExpressionType { CONSTANT, IDENTIFIER, COMPOUND };

//virtual father class
class Expression 
{
public:
   Expression();

   virtual ~Expression();
   virtual string toString() = 0;
   virtual ExpressionType getType() = 0;
};

//constant class
class ConstantExp: public Expression 
{
private:
   int value;
public:
   ConstantExp(int val);

   virtual string toString();
   virtual ExpressionType getType();
   int getValue();
};

//Identif class such as (x,y...)
class IdentifierExp: public Expression 
{
private:
   string name;
public:
   IdentifierExp(string name);

   virtual string toString();
   virtual ExpressionType getType();
   string getName();
};

//compound class such as (a op b...)
class CompoundExp: public Expression 
{
private:
   string op;
   Expression *lhs, *rhs;
public:
   CompoundExp(string op, Expression *lhs, Expression *rhs);
   
   virtual ~CompoundExp();
   virtual string toString();
   virtual ExpressionType getType();
   string getOp();
   Expression *getLHS();
   Expression *getRHS();
};

Expression::Expression() 
{

}

Expression::~Expression() 
{

}

ConstantExp::ConstantExp(int value) 
{
	this->value = value;
}

string ConstantExp::toString() 
{
	return integerToString(value);
}

ExpressionType ConstantExp::getType() 
{
	return CONSTANT;
}

int ConstantExp::getValue() 
{
	return value;
}

IdentifierExp::IdentifierExp(string name) 
{
	this->name = name;
}

string IdentifierExp::toString() 
{
	return name;
}

ExpressionType IdentifierExp::getType() 
{
	return IDENTIFIER;
}

string IdentifierExp::getName()
{
	return name;
}

CompoundExp::CompoundExp(string op, Expression *lhs, Expression *rhs)
{
	this->op = op;
	this->lhs = lhs;
	this->rhs = rhs;
}

CompoundExp::~CompoundExp() 
{
	delete lhs;
	delete rhs;
}

string CompoundExp::toString()
{
	//return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
   //I modified here to realize the cout of rpn
	return lhs->toString() + ' ' + rhs->toString() + ' ' + op;
}

ExpressionType CompoundExp::getType() 
{
	return COMPOUND;
}

string CompoundExp::getOp() 
{
	return op;
}

Expression *CompoundExp::getLHS() 
{
	return lhs;
}

Expression *CompoundExp::getRHS() 
{
	return rhs;
}

Expression *readT(TokenScanner &);

Expression *readE(TokenScanner &, int);

Expression *parseExp(TokenScanner &); 

//judge the level of each op
int precedence(string token) {
   if (token == "=") return 1;
   if (token == "+" || token == "-") return 2;
   if (token == "*" || token == "/") return 3;
   return 0;
}

//read tokens
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
   Expression *exp = readE(scanner,1);
   if (scanner.nextToken() != ")") 
   {
      error("Unbalanced parentheses in expression");
   }
   return exp;
}

//read expressions
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

Expression *parseExp(TokenScanner & scanner) 
{
   Expression *exp = readE(scanner,1);
   if (scanner.hasMoreTokens()) 
   {
      error("parseExp: Found extra token: " + scanner.nextToken());
   }
   return exp;
}

int main()
{
	vector<string> tests;
	string temp;

	ifstream ist;
	ist.open("./test_case/test_case_1.txt");

	while(getline(ist,temp))
		tests.push_back(temp);

	ist.close();

	ist.open("./test_case/test_case_2.txt");

	while(getline(ist,temp))
		tests.push_back(temp);

	ist.close();

	ist.open("./test_case/test_case_3.txt");

	while(getline(ist,temp))
		tests.push_back(temp);

	ist.close();

	for (int i = 0; i < 3; ++i)
	{
		string result = "";
		int judge = i * 2;
		while(1)
		{
			string str = tests[judge];
			judge ++;

			if (str == "quit")
				break;
			TokenScanner scanner(str);

			scanner.ignoreWhitespace();   // ignore the spaces between every two ops or numbers

			Expression *exp = parseExp(scanner);

			result += exp->toString();    //toString() is to cout the result

		   cout << result << endl;

		   delete exp;
		}
	}

	return 0;
}
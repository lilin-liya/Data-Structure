#include <string>
#include "variable.h"
#include "expcalculate.h"
#include "program.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/error.h"

using namespace std;

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

int ConstantExp::eval(EvalState & state) 
{
   return value;
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
   this->name = smallTobig(name);
}

int IdentifierExp::eval(EvalState & state) 
{
   //test if the var is defined
   if (!state.isDefined(name))
   {
      cout<<"VARIABLE NOT DEFINED"<<endl; 
      error(name + " is undefined");
   }
   return state.getValue(name);
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

int CompoundExp::eval(EvalState & state) 
{
   if (op == "=") 
   {
      if (lhs->getType() != IDENTIFIER) 
      {
         error("Illegal variable in assignment");
      }
      int val = rhs->eval(state);
      state.setValue(((IdentifierExp *) lhs)->getName(), val);
      return val;
   }
   int left = lhs->eval(state);
   int right = rhs->eval(state);
   if (op == "+") 
      return left + right;
   if (op == "-") 
      return left - right;
   if (op == "*") 
      return left * right;
   if (op == "/")
   {
      //test if the right == 0
      if (right == 0)
      {
         cout<<"DIVIDE BY ZERO"<<endl;
         error("DIVIDE BY ZERO");
      }
      else
         return left / right;
   }
   error("Illegal operator in expression");
   return 0;
}

string CompoundExp::toString() 
{
   return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
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

int precedence(string token) 
{
   if (token == "=") 
      return 1;
   if (token == "+" || token == "-") 
      return 2;
   if (token == "*" || token == "/") 
      return 3;
   return 0;
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
   Expression *exp = readE(scanner,1);
   if (scanner.nextToken() != ")") 
   {
      error("Unbalanced parentheses in expression");
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

Expression *parseExp(TokenScanner & scanner) 
{
   Expression *exp = readE(scanner,0);
   if (scanner.hasMoreTokens()) 
   {
      error("parseExp: Found extra token: " + scanner.nextToken());
   }
   return exp;
}
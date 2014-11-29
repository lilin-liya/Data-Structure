#include <string>
#include "../StanfordCPPLib/error.h"
#include "evalstate.h"
#include "exp.h"
#include "../StanfordCPPLib/strlib.h"
#include "parser.h"

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
   this->name = insenstr(name);
}

int IdentifierExp::eval(EvalState & state) 
{
   if (!state.isDefined(name))
   {
      //to test if the var name is defined
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
   if (op == "=") {
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
      //check if it is divided by 0
      if (right == 0)
      {
         cout<<"DIVIDE BY ZERO"<<endl;
         error("DIVIDE BY ZERO");
      }
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
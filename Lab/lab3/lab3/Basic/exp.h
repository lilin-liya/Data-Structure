#ifndef _exp_h
#define _exp_h

#include "evalstate.h"
#include <string>

using namespace std;

enum ExpressionType { CONSTANT, IDENTIFIER, COMPOUND };

class Expression 
{
public:
   Expression();
   virtual ~Expression();
   virtual int eval(EvalState & state) = 0;
   virtual string toString() = 0;
   virtual ExpressionType getType() = 0;
};

class ConstantExp: public Expression 
{
public:
   ConstantExp(int value);
   virtual int eval(EvalState & state);
   virtual string toString();
   virtual ExpressionType getType();
   int getValue();
private:
   int value;
};

class IdentifierExp : public Expression 
{
public:
   IdentifierExp(string name);
   virtual int eval(EvalState & state);
   virtual string toString();
   virtual ExpressionType getType();
   string getName();
private:
   string name;
};

class CompoundExp: public Expression 
{
public:
   CompoundExp(string op, Expression *lhs, Expression *rhs);
   virtual ~CompoundExp();
   virtual int eval(EvalState & state);
   virtual string toString();
   virtual ExpressionType getType();
   string getOp();
   Expression *getLHS();
   Expression *getRHS();
private:
   string op;
   Expression *lhs, *rhs;
};

#endif
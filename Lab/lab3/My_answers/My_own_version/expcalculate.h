#ifndef _EXPCALCULATE_H
#define _EXPCALCULATE_H

#include "variable.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include <string>

/*This file is just like homework7 I turned on before.
The codes can be found in CS106B's book.
All the classes designed to calculate the value of an exp.*/

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
private:
   int value;
public:
   ConstantExp(int value);
   virtual int eval(EvalState & state);
   virtual string toString();
   virtual ExpressionType getType();
   int getValue();
};

class IdentifierExp : public Expression 
{
private:
   string name;
public:
   IdentifierExp(string name);
   virtual int eval(EvalState & state);
   virtual string toString();
   virtual ExpressionType getType();
   string getName();
};

class CompoundExp: public Expression 
{
private:
   string op;
   Expression *lhs, *rhs;
public:
   CompoundExp(string op, Expression *lhs, Expression *rhs);
   virtual ~CompoundExp();
   virtual int eval(EvalState & state);
   virtual string toString();
   virtual ExpressionType getType();
   string getOp();
   Expression *getLHS();
   Expression *getRHS();
};

Expression *readT(TokenScanner &);

Expression *readE(TokenScanner &, int);

Expression *parseExp(TokenScanner &); 

int precedence(string token); 

#endif
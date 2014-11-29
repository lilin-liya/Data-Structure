#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "../StanfordCPPLib/tokenscanner.h"

//this file is for statements like "REM","INPUT"...

//a virtual father class,which has seven classes for seven different basic commands
//just like the style in exp.h
class Statement 
{	
public:	
	Statement();	
	virtual ~Statement();
	virtual void execute(EvalState & state) = 0;
};

class RemStmt: public Statement 
{
public:
    RemStmt(TokenScanner & scanner);
    virtual ~RemStmt();
    virtual void execute(EvalState & state);	
};

class LetStmt : public Statement 
{
public:
    LetStmt(TokenScanner &scanner);
    virtual ~LetStmt ();
    virtual void execute(EvalState & state);
private:
    string name; 
    Expression *rhs;
};

class InputStmt : public Statement 
{
public:
    InputStmt(TokenScanner & scanner);
    virtual ~InputStmt();
    virtual void execute (EvalState & state);
private:
    string name;
};

class PrintStmt : public Statement 
{
public:
    PrintStmt(TokenScanner & scanner);
    virtual ~PrintStmt ();
    virtual void execute(EvalState & state);
private:
    Expression *exp;
};

class GotoStmt : public Statement 
{
public:
    GotoStmt(TokenScanner & scanner);
    virtual ~GotoStmt();
    virtual void execute(EvalState & state);
private:
    int gotoLine;
    int maxLine;
};

class EndStmt:public Statement 
{
public:
    EndStmt(TokenScanner &scanner);
    virtual ~EndStmt();
    virtual void execute(EvalState &state);
};

class IfStmt:public Statement 
{
public:
    IfStmt(TokenScanner &scanner);
    virtual ~IfStmt();
    virtual void execute(EvalState &state);
private:
    Expression *expOne,*expTwo;
    string op;
    int thenLine;
};

#endif
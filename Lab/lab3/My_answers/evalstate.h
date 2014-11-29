#ifndef _evalstate_h
#define _evalstate_h

#include <string>
#include "../StanfordCPPLib/map.h"

//this file is for the vars defined,and the vars are insensetive to big or small letters

class EvalState 
{
public:
	EvalState();
	~EvalState();
	void setValue(string var, int value);
	int getValue(string var);
	bool isDefined(string var);
	void setCurrentLine (int lineNumber);
   	int getCurrentLine ();
   	void clear();
private:
   	Map<string,int> symbolTable;
	int currentLine;
};

#endif
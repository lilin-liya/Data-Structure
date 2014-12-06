#ifndef _evalstate_h
#define _evalstate_h

#include <string>
#include "map.h"

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
private:
   	Map<string,int> symbolTable;
	int currentLine;
};

#endif
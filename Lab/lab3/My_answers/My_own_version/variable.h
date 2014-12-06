#ifndef _VARIABLE_H
#define _VARIABLE_H

/*This file deals with all variables.
The codes can also be found in CS106B's book.
*/

#include <string>
#include "../StanfordCPPLib/map.h"

using namespace std;

class EvalState 
{
public:
   	Map<string,int> symbolTable;
public:
	EvalState();
	~EvalState();
	void setValue(string var, int value);
	int getValue(string var);
	bool isDefined(string var);
	void remove(string var);
   	void clear();
};

#endif
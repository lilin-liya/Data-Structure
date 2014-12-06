#include <string>
#include "evalstate.h"
#include "../StanfordCPPLib/map.h"
#include "parser.h"

using namespace std;

EvalState::EvalState() 
{
   
}

EvalState::~EvalState() 
{

}

void EvalState::setValue(string var, int value) 
{
   //symbolTable.put(var, value);
	symbolTable.put(insenstr(var), value);
}

int EvalState::getValue(string var) 
{
   //return symbolTable.get(var);
	return symbolTable.get(insenstr(var));
}

bool EvalState::isDefined(string var) 
{
   //return symbolTable.containsKey(var);
	return symbolTable.containsKey(insenstr(var));
}

void EvalState::setCurrentLine(int lineNumber) 
{
	currentLine=lineNumber;
}

int EvalState::getCurrentLine() 
{
	return currentLine;
}

void EvalState::clear() 
{
	currentLine = -1;
	symbolTable.clear();
}
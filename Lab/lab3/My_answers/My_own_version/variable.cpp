#include <string>
#include "variable.h"
#include "program.h"
#include "../StanfordCPPLib/map.h"

using namespace std;

EvalState::EvalState() 
{
   
}

EvalState::~EvalState() 
{

}

void EvalState::setValue(string var, int value) 
{
  	symbolTable.put(smallTobig(var), value);
}

int EvalState::getValue(string var) 
{
	return symbolTable.get(smallTobig(var));
}

bool EvalState::isDefined(string var) 
{
	return symbolTable.containsKey(smallTobig(var));
}

void EvalState::remove(string var)
{
	symbolTable.remove(smallTobig(var));	
}

void EvalState::clear() 
{
	symbolTable.clear();
}
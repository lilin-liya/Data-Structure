#ifndef _program_h
#define _program_h

#include <string>
#include "../StanfordCPPLib/vector.h"
#include "../StanfordCPPLib/hashmap.h"
#include "statement.h"
#include "../StanfordCPPLib/error.h"

/*this file defines a class for a basic program*/

using namespace std;

struct StrStmt 
{
  string str;
  Statement *stmt;
  int indx;
};

class Program 
{
private:
	HashMap<int, StrStmt * > stmtMap;    //stmtMap has line and its command
public:
	Vector<int> lineNumVec;              //this vector saves all linenumbers
	Program();  
 	~Program();
 	void clear();
 	void addSourceLine(int lineNumber, std::string line);
 	void removeSourceLine(int lineNumber);   
 	string getSourceLine(int lineNumber);
 	void setParsedStatement(int lineNumber, Statement *stmt);
 	Statement *getParsedStatement(int lineNumber);
 	int getFirstLineNumber();
 	int getNextLineNumber(int lineNumber);
};

#endif
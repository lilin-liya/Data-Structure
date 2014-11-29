#ifndef _program_h
#define _program_h

#include <string>
#include "vector.h"
#include "hashmap.h"
#include "statement.h"
#include "error.h"

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
	HashMap<int, StrStmt * > stmtMap;
	//Vector<int> lineNumVec;
public:
	Vector<int> lineNumVec;
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
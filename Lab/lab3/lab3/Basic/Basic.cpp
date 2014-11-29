#include <cctype>
#include <iostream>
#include <string>
#include "console.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "error.h"

using namespace std;

int now_line = 0;
Vector<int> all_gotolines;
int find_goto = 0;
int can_goto = 0;

void processLine(string line, Program & program, EvalState & state);

int main() 
{
	EvalState state;
	Program program;
	while (true) 
	{
		try 
		{
			processLine(getLine(), program, state);
			now_line += 10;
		} 
        catch (ErrorException & ex) 
        {
			cerr << "Error: " << ex.getMessage() << endl;
		}
	}
	// for (int i = 0; i < all_gotolines.size(); ++i)
	// {
	// 	cout<<all_gotolines[i]<<" ";
	// }
	return 0;
}

void processLine(string line, Program & program, EvalState & state) 
{
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
    string str=scanner.nextToken();

    if (scanner.getTokenType(str)==NUMBER) 
    {	
        int lineNumber=stringToInteger(str);
        string token=scanner.nextToken();
        scanner.saveToken(token);
        if (token!="") 
        {
        	if (insenstr(token) == "GOTO")
        	{
	        	all_gotolines.push_back(lineNumber);
        	}
            program.addSourceLine(lineNumber, line);
            program.setParsedStatement(lineNumber, parseStatement(scanner));
        }
        else 
        {
            program.removeSourceLine(lineNumber);
        }
    }
    else if (insenstr(str) == "PRINT" || insenstr(str) == "REM" ||
    		insenstr(str) ==  "INPUT" || insenstr(str) == "LET" ||
    		insenstr(str) ==  "GOTO" || insenstr(str) == "IF" || 
    		insenstr(str) == "END")
    {
    	string token = insenstr(str);
        scanner.saveToken(token);
        if (token!="") 
        {
            program.addSourceLine(now_line, line);
            program.setParsedStatement(now_line, parseStatement(scanner));
        }
        else 
        {
            program.removeSourceLine(now_line);
        }
        state.setCurrentLine(now_line);
        program.getParsedStatement(now_line)->execute(state);
    }
    else if (insenstr(str) == "LIST") 
    {
        for (int i=program.getFirstLineNumber(); i!=-1; i=program.getNextLineNumber(i)) 
        {
            cout << program.getSourceLine(i)<<endl;
        }
    }
    else if (insenstr(str) == "CLEAR") 
    {
        program.clear();
    }
    else if(insenstr(str) == "QUIT") 
    	exit(0);
    else if (insenstr(str) == "HELP") 
    	cout<<"This is a minimal BASIC interpreter."<<endl;
    else if (insenstr(str) == "RUN")
    {
        int currentLine=program.getFirstLineNumber();
        state.setCurrentLine(currentLine);
        while (currentLine!=-1) 
        {
        	// for (int i = 0; i < all_gotolines.size(); ++i)
        	// {
        	// 	if (currentLine == all_gotolines[i])
        	// 		find_goto = 1;
        	// }
        	// if (find_goto)
        	// {
	        // 	currentLine = program.getNextLineNumber(currentLine);
	        // 	for (int i = 0; i < program.lineNumVec.size(); ++i)
	        // 	{
	        // 		if (currentLine == program.lineNumVec[i])
	        // 			can_goto = 1;
	        // 	}
	        // 	if (!can_goto)
	        // 	{
	        // 		cout<<"wrong"<<endl;
        	// 		error("wrong");
	        // 	}
        	// }
        	//else
        	//{                       
	            program.getParsedStatement(currentLine)->execute(state);
				
	            if(currentLine!=state.getCurrentLine()) 
	            {
	                currentLine=state.getCurrentLine();
	            }
	            else 
	            {
	                currentLine=program.getNextLineNumber(currentLine);
	                state.setCurrentLine(currentLine);
	            }
        	//}
        }
    }
}
#include <iostream>
#include <string>
#include "../StanfordCPPLib/console.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/vector.h"
#include "../StanfordCPPLib/error.h"

using namespace std;

//if this line has no linenumber,then I give it a number which is < 0
//so,it will not conflict with the other linenumber
int now_line = -10;

//this function is to get the current input line and parse it
void processLine(string line, Program & program, EvalState & state,bool can_goto);
//this is for "RUN"
void run_interpreter(Program & program, EvalState & state,bool can_goto);

int main() 
{
	EvalState state;
	Program program;           //the basic program
    bool can_goto = 0;         //to judge if it can goto the line when meet "GOTO"
	while (true) 
	{
		try 
		{
			processLine(getLine(), program, state,can_goto);
            //every line whose has no linenumber need this now_line
			now_line -= 10;
		} 
        catch (ErrorException & ex) 
        {
			cerr << "Error: " << ex.getMessage() << endl;
		}
	}
	return 0;
}

void run_interpreter(Program & program, EvalState & state,bool can_goto)
{
    int currentLine=program.getFirstLineNumber();

    //since I create linenumber < 0,every time meet "RUN",we need to cheek the linenumber 
    //to ensure it > 0 
    while (currentLine < 0)
        currentLine=program.getNextLineNumber(currentLine);

    state.setCurrentLine(currentLine);
    while (currentLine!=-1) 
    {   
        can_goto = 0;
        //only the current linenumber is a member of the linenumber vector,
        //this command is valid,can_goto becomes 1
        for (int i = 0; i < program.lineNumVec.size(); ++i)
        {
            if (currentLine == program.lineNumVec[i])
                can_goto = 1;
        } 
        if (!can_goto)
        {
            cout<<"LINE NUMBER ERROR"<<endl;
            error("LINE NUMBER ERROR");
        }
        //execute the line
        program.getParsedStatement(currentLine)->execute(state);
        
        if(currentLine!=state.getCurrentLine()) 
        {
            currentLine=state.getCurrentLine();
        }
        else 
        {
            //get next linenumber
            currentLine=program.getNextLineNumber(currentLine);
            state.setCurrentLine(currentLine);
        }
    }
}

void processLine(string line, Program & program, EvalState & state,bool can_goto) 
{
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
    string str=scanner.nextToken();

    //deal with the command start by number
    if (scanner.getTokenType(str)==NUMBER) 
    {	
        int lineNumber=stringToInteger(str);
        string token=scanner.nextToken();
        scanner.saveToken(token);
        if (token!="") 
        {
            program.addSourceLine(lineNumber, line);
            program.setParsedStatement(lineNumber, parseStatement(scanner));
        }
        else 
        {
            program.removeSourceLine(lineNumber);
        }
    }
    //if this line has no linenumber,but still a valid command
    //just run it
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
    //list all lines with linenumbers
    else if (insenstr(str) == "LIST") 
    {
        for (int i=program.getFirstLineNumber(); i!=-1; i=program.getNextLineNumber(i)) 
        {
            cout << program.getSourceLine(i)<<endl;
        }
    }
    //clear the program and state
    else if (insenstr(str) == "CLEAR") 
    {
        program.clear();
        state.clear();
    }
    //exit interpreter
    else if(insenstr(str) == "QUIT") 
    {
    	exit(0);
    }
    //cout help
    else if (insenstr(str) == "HELP") 
    	cout<<"This is a minimal BASIC interpreter."<<endl;
    //run interpreter
    else if (insenstr(str) == "RUN")
    {
        run_interpreter(program,state,can_goto);
    }
}
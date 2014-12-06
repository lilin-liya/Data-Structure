#ifndef _PROGRAM_H
#define _PROGRAM_H

/*This file defines the BasicLine and BasicProgram class*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "expcalculate.h"
#include "variable.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

const int NOLINENUMBER = -10;		//if this line has no linenumber,we assume it be -10

/*
Assume a line:10 PRINT 2+2
Then:
original_line is:10 PRINT 2+2
linenumber is:10
keyword is:"PRINT"
content is:2+2
*/

class BasicLine
{
public:
	bool is_valid;					//is this line a valid command ?
	bool withlinenumber_valid;		//is this line has a linenumber ?
	bool withoutlinenumber_valid;	//is this line has no linenumber ?
	bool keyword_valid;				//is this line's keyword
	bool content_valid; 
	int linenumber;
	string keyword;
	string content;
	string original_line;
	bool if_valid;					//if the keyword is "IF",is the condition satisfied?
	int then_linenumber;			//if the condition is satisfied,then get its next linenumber
public:
	BasicLine();
	void SetLine(string line);
	void run(EvalState& basicstate);
	void clear();
	~BasicLine();
};

class BasicProgram
{
private:
	map<int,BasicLine> basicprogram;	//this map stores all basiclines with linenumber
public:
	vector<int>sorted_linenumbers;		//all sorted linenumbers 
	BasicProgram();
	void Add_BasicLine(BasicLine b_l);	//add a basicline to the basicprogram
	void Store_Linenumber();			//init the sorted_linenumbers vector
	int Get_Firstline();
	void RunProgram(int beginline,EvalState& basicstate);	//run the whole program
	void ListProgram();
	void clear();
	~BasicProgram();
};

string smallTobig(string str);		//a function turns all small letter to big

#endif
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "program.h"

using namespace std;

int main()
{
	BasicLine basicline;			//each input line
	BasicProgram basicprogram;		//the whole basic program contains all inputlines with a linenumber
	EvalState basicstate;			//all variables used in the program
	while(1)
	{
		try
		{
			basicline.clear();		//before read a new line,need to clear the old info in the basicline
			string line = getLine();

			basicline.SetLine(line);	//set the info of the basicline
			//if this line has no linenumber,but still a valid command,then run it immediately
			if (basicline.withoutlinenumber_valid && basicline.is_valid)
			{
				basicline.run(basicstate);
			}
			//else add it into the whole basicprogram
			basicprogram.Add_BasicLine(basicline);
			//if we accept "RUN",run the whole basicprogram
			if (smallTobig(line) == "RUN")
			{
				//since we may run more than 1 time,so we need to init the linenumbers everytime
				basicprogram.sorted_linenumbers.clear();
				basicprogram.Store_Linenumber();
				int beginline = basicprogram.Get_Firstline();
				//RunProgram() accepts a begin linenumber and a variable set as input
				basicprogram.RunProgram(beginline,basicstate);
			}
			if (smallTobig(line) == "QUIT")
			{
				exit(0);
			}
			if (smallTobig(line) == "LIST")
			{
				//list the whole basicprogram by linenumber from smaller to biger
				basicprogram.sorted_linenumbers.clear();
				basicprogram.Store_Linenumber();
				basicprogram.ListProgram();
			}
			if (smallTobig(line) == "CLEAR")
			{
				//both the whole basicprogram and the variable set need to be cleared
				basicstate.clear();
				basicprogram.clear();
			}
			if (smallTobig(line) == "HELP")
			{
				cout<<"HELP"<<endl;
			}
		}
		catch (ErrorException & ex) 
        {
			cerr << "Error: " << ex.getMessage() << endl;
		}
	}
	return 0;
}
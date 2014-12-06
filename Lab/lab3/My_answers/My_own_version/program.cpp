#include "program.h"

using namespace std;

string smallTobig(string str)
{
    string result = str;
    int len = str.length();
    for (int i = 0; i < len; ++i)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
          result[i] = result[i] - 32;
        }
    }
    return result;
}

//init the infos in BasicLine
BasicLine::BasicLine()
{
    is_valid = 0;
    withlinenumber_valid = 0;
    withoutlinenumber_valid = 0;
    keyword_valid = 0;
    content_valid = 0; 
  	linenumber = NOLINENUMBER;
  	keyword = "";
  	content = "";
    original_line = "";
    if_valid = 0;
    then_linenumber = NOLINENUMBER;
}

void BasicLine::SetLine(string line)
{
    original_line = line;
	  TokenScanner token(line);

  	token.scanStrings();
  	token.ignoreWhitespace();

    //here we get the linenumber if has
  	string _linenumber = smallTobig(token.nextToken());
    //if meet those strings ,just return
    if (_linenumber == "RUN" || _linenumber == "LIST"
      || _linenumber == "CLEAR" || _linenumber == "QUIT"
      || _linenumber == "HELP")
      return;

  	if (token.getTokenType(_linenumber) == NUMBER)
  	{
      int temp_linenumber = stringToInteger(_linenumber);
      if (temp_linenumber >= 0)
      {
        withlinenumber_valid = 1;
  		  linenumber = temp_linenumber;
      }
      else
        error("ERROR LINENUMBER");
  	}
  	else
  	{
      withoutlinenumber_valid = 1;
  		linenumber = NOLINENUMBER;
      token.saveToken(_linenumber);
  	}

    //here we get keyword
  	string _keyword = smallTobig(token.nextToken());
  	if (_keyword == "REM" || _keyword == "PRINT" || _keyword == "INPUT" || _keyword == "LET"
  		|| _keyword == "GOTO" || _keyword == "IF" || _keyword == "END" || _keyword == "")
  	{
      keyword_valid = 1;
  		keyword = _keyword;
  	}

    //here we get content
  	string _content = "";
    while(token.hasMoreTokens())
    {
      _content = _content + token.nextToken() + " ";
    }
    //since I add a space at the end of the content,so need to erase it
    if (_content.length() != 0)
    {
      _content.erase(_content.end()-1);
    }
  	content = smallTobig(_content);
    content_valid = 1;
    if (withlinenumber_valid && keyword_valid && content_valid)
    {
      is_valid = 1;
    }
    if (withoutlinenumber_valid && keyword_valid && content_valid)
    {
      is_valid = 1;
    }
}

void BasicLine::run(EvalState& basicstate)
{
    //"REM":do nothing
    if (keyword == "REM")
    {
      
    }
    //"PRINT":calculate the exp's value and cout it
		else if (keyword == "PRINT")
		{
      TokenScanner scanner;
      scanner.ignoreWhitespace();
      scanner.scanNumbers();
      scanner.setInput(content);
      Expression *exp = parseExp(scanner);
      int value = exp->eval(basicstate);
			cout<<value<<endl;
		}
    //"INPUT":get the var's name and wait until get the right int value
    else if (keyword == "INPUT")
    {
      TokenScanner scanner;
      scanner.ignoreWhitespace();
      scanner.scanNumbers();
      scanner.setInput(content);

      string name = content;

      bool success = 0;
      string str;
      while(!success)
      {
        str = getLine(" ? ");
        istringstream stream(str);
        int value;
        stream >> value;
        if (stream.fail() || !stream.eof()) 
        {
            cout<<"INVALID NUMBER"<<endl;
        }
        else
        {
            success = 1;
            basicstate.setValue(name,value);
        }
      }
    }
    //"LET":get the exp's value,and add the var's name and value to the variable set
    else if (keyword == "LET")
    {
      TokenScanner scanner;
      scanner.ignoreWhitespace();
      scanner.scanNumbers();
      scanner.setInput(content);

      string name=scanner.nextToken();
      scanner.saveToken(name);

      Expression *exp = parseExp(scanner);
      int value = exp->eval(basicstate);
      basicstate.setValue(name,value);
    }

    //"IF":judge if the condition is satisfied then goto the then_linenumber
    else if (keyword == "IF")
    {

      //init these two everytime
      if_valid = 0;
      then_linenumber = NOLINENUMBER;

      string strExpOne="";    //the op's left exp
      string strExpTwo="";    //the op's right exp
      string next = "";

      TokenScanner scanner;
      scanner.ignoreWhitespace();
      scanner.scanNumbers();
      scanner.setInput(content);

      while (true) 
      {
        next = scanner.nextToken();
        if (next == "=" || next == "<" || next == ">") 
          break;
        strExpOne += next;
      }

      TokenScanner scannerOne(strExpOne);
      scannerOne.ignoreWhitespace();
      scannerOne.scanNumbers();
      Expression *expOne = parseExp(scannerOne);
      string op = next;

      while (true) 
      {
          next = scanner.nextToken();
          if(next == "THEN") 
            break;
          strExpTwo += next;
      }

      TokenScanner scannerTwo(strExpTwo);
      scannerTwo.ignoreWhitespace();
      scannerTwo.scanNumbers();
      Expression *expTwo = parseExp(scannerTwo);
      int then_line = stringToInteger(scanner.nextToken());

      int resultOne = expOne->eval(basicstate);
      int resultTwo = expTwo->eval(basicstate);
      if((op == "=" && resultOne == resultTwo) || 
         (op == ">" && resultOne > resultTwo) || 
         (op == "<" && resultOne < resultTwo))
      {
        if_valid = 1;
        then_linenumber = then_line;
      }     //only satisfied,we can get the right then_linenumber
    }
    else
      error("INVALID COMMAND");
}

void BasicLine::clear()
{
    is_valid = 0;
    withlinenumber_valid = 0;
    withoutlinenumber_valid = 0;
    keyword_valid = 0;
    content_valid = 0; 
    linenumber = NOLINENUMBER;
    keyword = "";
    content = "";
    original_line = "";
    if_valid = 0;
    then_linenumber = NOLINENUMBER;
}

BasicLine::~BasicLine()
{

}

BasicProgram::BasicProgram()
{

}

void BasicProgram::Add_BasicLine(BasicLine b_l)
{
  //if this line has a linenumber and is a valid command,add it
	if (b_l.withlinenumber_valid && b_l.is_valid)
	{
    int _linenumber = b_l.linenumber;
    //for the case:this line never showed before and only has a linenumber
    if (!basicprogram.count(_linenumber) && (b_l.keyword + b_l.content).length() == 0)
      return;
    //for the case:this line's linenumber has shown before
    if (basicprogram.count(_linenumber))
    {
      //if it only has a linenumber,erase this line from the whole program
      if ((b_l.keyword + b_l.content).length() == 0)
      {
        map<int,BasicLine>::iterator iter;
        iter = basicprogram.find(_linenumber);
        basicprogram.erase(iter);
      }
      //else we replace the old line with the new one
      else
        basicprogram[_linenumber] = b_l;
    }
    else
    {
      basicprogram.insert(pair<int,BasicLine>(_linenumber,b_l));
    }
	}
}

void BasicProgram::Store_Linenumber()
{
  map<int,BasicLine>::iterator it;
  for (it = basicprogram.begin(); it != basicprogram.end(); it++)
  {
    sorted_linenumbers.push_back(it->first);
  } 
}

int BasicProgram::Get_Firstline()
{
  return sorted_linenumbers[0];
}

void BasicProgram::RunProgram(int beginline,EvalState& basicstate)
{
  int index;
  int currentline = beginline;    //run from currentline
  for (int i = 0; i < sorted_linenumbers.size(); ++i)
  {
    if (sorted_linenumbers[i] == currentline)
    {
      index = i;
      break;
    }
  }
  for (int i = index; i < sorted_linenumbers.size(); ++i)
  {
    currentline = sorted_linenumbers[i];
    //deal with "IF",if "IF" is satisfied,we continue run with then_linenumber
    if (basicprogram[currentline].keyword == "IF")
    {
      basicprogram[currentline].run(basicstate); 
      if (basicprogram[currentline].if_valid)
      {
        currentline = basicprogram[currentline].then_linenumber;
        RunProgram(currentline,basicstate);
        return;
      }
    }
    //deal with "GOTO",if we can goto,run with the goto_linenumber
    else if (basicprogram[currentline].keyword == "GOTO")
    {
      bool can_goto = 0;
      currentline = stringToInteger(basicprogram[currentline].content);
      for (int i = 0; i < sorted_linenumbers.size(); ++i)
      {
        if (currentline == sorted_linenumbers[i])
        {
          can_goto = 1;
          break;
        }
      }
      if (can_goto)
      {
        can_goto = 0;
        RunProgram(currentline,basicstate);
      }
      else
      {
        can_goto = 0;
        cout<<"LINE NUMBER ERROR"<<endl;
        error("LINE NUMBER ERROR");
      }
      return;
    }
    //deal with "END",just return
    else if (basicprogram[currentline].keyword == "END")
    {
      return;
    }
    //other cases,we run normally
    else
      basicprogram[currentline].run(basicstate);
  }
}

void BasicProgram::ListProgram()
{
  for (int i = 0; i < sorted_linenumbers.size(); ++i)
  {
    cout<<basicprogram[sorted_linenumbers[i]].original_line<<endl;
  } 
}

void BasicProgram::clear()
{
  map<int,BasicLine>::iterator it;
  for (it = basicprogram.begin(); it != basicprogram.end(); it++)
  {
    it->second.clear();
  } 
  basicprogram.clear();
  sorted_linenumbers.clear();
}

BasicProgram::~BasicProgram()
{

}
#ifndef _parser_h
#define _parser_h

#include <string>
#include "exp.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "statement.h"

Expression *parseExp(TokenScanner & scanner);

Expression *readE(TokenScanner & scanner, int prec = 0);

Expression *readT(TokenScanner & scanner);

int precedence(string token);

//parse the statement
Statement *parseStatement (TokenScanner & scanner);

//turn every char in str to big letter
string insenstr(string str);

#endif
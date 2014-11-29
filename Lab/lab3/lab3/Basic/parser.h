#ifndef _parser_h
#define _parser_h

#include <string>
#include "exp.h"
#include "tokenscanner.h"
#include "statement.h"

Expression *parseExp(TokenScanner & scanner);

Expression *readE(TokenScanner & scanner, int prec = 0);

Expression *readT(TokenScanner & scanner);

int precedence(string token);

Statement *parseStatement (TokenScanner & scanner);

string insenstr(string str);

#endif
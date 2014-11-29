#include "TryTokenScanner.h"

#include "tokenscanner.h"

using namespace std;

// Part I
Vector<string> TryTokenScanner::allTokens(string text) {
  Vector<string> tokens;
  // [TODO] put your code here
  stringstream is(text);
  string str;
  while(is >> str)
  	tokens.push_back(str);
  return tokens;
}

// Part II
Vector<string> TryTokenScanner::noWhitespaces(string text) {
  Vector<string> tokens;
  // [TODO] put your code here

  return tokens;
}

// Part III
Vector<string> TryTokenScanner::noComments(string text) {
  Vector<string> tokens;
  // [TODO] put your code here

  return tokens;
}

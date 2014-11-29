#include "TryTokenScanner.h"

#include "tokenscanner.h"

using namespace std;

// Part I
Vector<string> TryTokenScanner::allTokens(string text) {
  Vector<string> tokens;
  // [TODO] put your code here

  TokenScanner tokenall(text);

  tokenall.scanStrings();

  while(tokenall.hasMoreTokens())
    tokens.push_back(tokenall.nextToken());
    
  return tokens;
}

// Part II
Vector<string> TryTokenScanner::noWhitespaces(string text) {
  Vector<string> tokens;
  // [TODO] put your code here

  TokenScanner no_ws_token(text);

  no_ws_token.scanStrings();
  no_ws_token.ignoreWhitespace();

  while(no_ws_token.hasMoreTokens())
    tokens.push_back(no_ws_token.nextToken());

  return tokens;
}

// Part III
Vector<string> TryTokenScanner::noComments(string text) {
  Vector<string> tokens;
  // [TODO] put your code here

  TokenScanner no_comments_token(text);
  
  no_comments_token.scanStrings();
  no_comments_token.ignoreComments();

  while(no_comments_token.hasMoreTokens())
    tokens.push_back(no_comments_token.nextToken());
  return tokens;
}
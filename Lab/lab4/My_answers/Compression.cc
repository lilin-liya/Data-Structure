#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

int main(int argc, char* argv[]) 
{
  int i;
  string inputFilename, outputFilename;
  bool isDecompress = false;
  for (i = 1; i < argc; i++) 
  {
    if (argv[i] == string("-d")) 
      isDecompress = true;
    else if (inputFilename == "") 
      inputFilename = argv[i];
    else if (outputFilename == "") 
      outputFilename = argv[i];
    else 
      usage(argv[0]);
  }
  if (outputFilename == "") 
    usage(argv[0]);
  if (isDecompress) 
    decompress(inputFilename, outputFilename);
  else 
  {
    compress(inputFilename, outputFilename);
  }
  return 0;
}
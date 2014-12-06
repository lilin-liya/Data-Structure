#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include "HuffmanTree.h"
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define UINT unsigned int 

int cmp(const pair<UINT,int>& x, const pair<UINT,int>& y)  
{  
  return x.second < y.second;  
}  
   
void sortMapByValue(map<UINT,int>& tMap, vector<pair<UINT,int> >& tVector)  
{  
  for (map<UINT,int>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)  
  {  
    tVector.push_back(make_pair(curr->first, curr->second));  
  }  
   
  sort(tVector.begin(), tVector.end(), cmp);  
}  

void naiveCopy(string inputFilename, string outputFilename) 
{
  char* result;
  map<UINT,int> test;
  //vector<char> vec;
  vector<pair<UINT,int> > vec;  
  map<UINT,string>::iterator its;

  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  //ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  char c;
  while (ifs.get(c)) 
    //cout<<(unsigned int)(c)<<endl;
    test[c]++;
    //ofs.put(c);
  ifs.close();
  //ofs.close();

  // for (its = test.begin(); its != test.end(); its++)
  // {
  //   cout<<(unsigned int)(its->first)<<": "<<its->second<<endl;
  // }

  sortMapByValue(test,vec);
  //cout<<"---------"<<endl;
  HuffmanTree huffmantree(vec);
  //cout<<"---------"<<endl;
  huffmantree.SetHuffmanCode(huffmantree.get_root(),result,0);
  for (its = huffmantree.huffmancode.begin(); its != huffmantree.huffmancode.end(); its++)
  {
    cout<<its->first<<": "<<its->second<<endl;
  }
}

void compress(string inputFilename, string outputFilename) 
{
  //cout<<"---------"<<endl;  
  naiveCopy(inputFilename, outputFilename);
}

void decompress(string inputFilename, string outputFilename) 
{
  naiveCopy(inputFilename, outputFilename);
}

void usage(string prog) 
{
  cerr << "Usage: " << endl
      << "    " << prog << "[-d] input_file output_file" << endl;
  exit(2);
}

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

// int main()
// {
//   naiveCopy("trace03.txt","out.txt");
//   return 0;
// }

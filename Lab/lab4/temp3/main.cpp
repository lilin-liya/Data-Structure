#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;

#define UINT unsigned int 

int cmp(const pair<UINT,int>& x, const pair<UINT,int>& y)  
{  
 	return x.second < y.second;  
}  
   
void sortMapByValue(const map<UINT,int>& tMap, vector<pair<UINT,int> >& tVector)  
{  
	for (map<UINT,int>::const_iterator curr = tMap.begin(); curr != tMap.end(); curr++)  
	{  
		tVector.push_back(pair<UINT,int>(curr->first, curr->second));  
	}
   
 	sort(tVector.begin(), tVector.end(), cmp);  
}  

void compress(string inputFilename, string outputFilename) 
{
  char* result;
  string result_str = "";
  map<UINT,int> test;
  vector<pair<UINT,int> > vec;  
  map<UINT,string>::iterator its;

  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  char c;
  while (ifs.get(c)) 
  {
    test[c]++;
  }
  ifs.close();

  sortMapByValue(test,vec);

  HuffmanTree huffmantree(vec);

  huffmantree.SetHuffmanCode(huffmantree.get_root(),result,0);
  // for (its = huffmantree.huffmancode.begin(); its != huffmantree.huffmancode.end(); its++)
  // {
		// cout<<its->first<<": "<<its->second<<endl;
  // }

  ifs.open(inputFilename.c_str(), ios::in | ios::binary);
  while (ifs.get(c)) 
  {
  	result_str += huffmantree.huffmancode[c];
  }
  ifs.close();

  //cout<<result_str<<endl;
  //reverse(result_str.begin(),result_str.end());
  bitset<128> bitvec(result_str);
  cout<<bitvec<<endl;

  unsigned char outbyte;
  //int total_bits = 0;
  string str_buf = "";

  for (int i = 0; i < result_str.length(); i += 8)
  {
  	str_buf = "";
  	outbyte='\0';
  	for (int j = 0; j < 8; ++i)
  	{
  		str_buf += result_str[j+i];
  		outbyte = outbyte << 1;
  		if (result_str[j+i] == '1')
	  		outbyte |= 1;
  	}
  	//total_bits += 8;
  	ofs.write((char *)&outbyte,sizeof(unsigned char));
  }

  // if (total_bits < result_str.length())
  // {
  // 	str_buf = "";
  // 	outbyte='\0';
  // 	for (int i = total_bits; i < result_str.length(); ++i)
  // 	{
  // 		str_buf += result_str[i]; 
  // 		outbyte = outbyte << 1;
  // 		if (result_str[i] == '1')
	 //  		outbyte |= 1;
  // 	}
  // 	ofs.write((char *)&outbyte,sizeof(unsigned char));
  // }
  ofs.close();
}

int main()
{
	compress("trace03.txt","out.txt");
	// char* result;
	// vector<UINT> vec;
	// map<UINT,int> test;
	// vector<pair<UINT,int> > temp_vec;
	// map<UINT,string>::iterator its;
	// vec.push_back('a');
	// vec.push_back('b');
	// vec.push_back('c');
	// vec.push_back('c');
	// vec.push_back('c');
	// vec.push_back('d');
	// vec.push_back('d');
	// vec.push_back('d');
	// vec.push_back('d');
	// vec.push_back('d');
	// vec.push_back('d');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('e');
	// vec.push_back('f');
	// vec.push_back('d');
	// vec.push_back('h');
	// vec.push_back('d');
	// vec.push_back('h');
	// vec.push_back('g');	
	// vec.push_back('j');
	// vec.push_back('j');
	// vec.push_back('j');
	// vec.push_back('j');
	// vec.push_back('j');
	// vec.push_back('j');
	// vec.push_back(10);
	// vec.push_back(13);

	// // trick
	// sin(test[0]);

	// for (int i = 0; i < vec.size(); ++i)
	// {
	// 	test[vec[i]]++;
	// }

 //  	sortMapByValue(test,temp_vec);  

	// HuffmanTree huffmantree(temp_vec);

	// huffmantree.SetHuffmanCode(huffmantree.get_root(),result,0);

	// for (its = huffmantree.huffmancode.begin(); its != huffmantree.huffmancode.end(); its++)
	// {
	// 	cout<<its->first<<": "<<its->second<<endl;
	// }
	return 0;
}
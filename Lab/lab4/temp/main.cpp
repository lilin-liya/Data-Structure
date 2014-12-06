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
  //char buf[10000];
  //char* result = (char *)malloc(10000 * sizeof(char));
  string result_str = "";
  map<UINT,int> test;
  vector<pair<UINT,int> > vec;  
  map<UINT,string>::iterator its;
  map<UINT,int>::iterator itc;

  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  char c;
  int char_nums = 0;
  while (ifs.get(c)) 
  {
    test[c]++;
    char_nums++;
  }
  ifs.close();

  char* result = (char *)malloc(4 * char_nums);

  // for (itc = test.begin(); itc != test.end(); itc++)
  // {
  // 	cout<<itc->first<<": "<<itc->second<<endl;
  // }

  sortMapByValue(test,vec);
  // cout<<"-----------"<<endl;

  // for (int i = 0; i < vec.size(); i++)
  // {
  // 	cout<<vec[i].first<<": "<<vec[i].second<<endl;
  // }

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

   cout<<result_str.length()<<endl;
  // cout<<test.size()<<endl;
  // cout<<vec.size()<<endl;
   cout<<result_str<<endl;

  unsigned char outbyte;
  int total_bits = 0;
  unsigned char lackbits = 0;
  string str_buf = "";

  unsigned char result_str_len = result_str.length();
  ofs.write((char *)&result_str_len,sizeof(unsigned char));
  unsigned char unique_char_nums = test.size();
  ofs.write((char *)&unique_char_nums,sizeof(unsigned char));
  unsigned char temp_char;
  unsigned char temp_char_fre;
  for (int i = 0; i < vec.size(); i++)
  {
  	temp_char = vec[i].first;
  	ofs.write((char *)&temp_char,sizeof(unsigned char));
  }
  for (int i = 0; i < vec.size(); i++)
  {
  	temp_char_fre = vec[i].second;
  	ofs.write((char *)&temp_char_fre,sizeof(unsigned char));
  }	

  // for (int i = 0; i < result_str.length(); i += 8)
  // {
  // 	str_buf = "";
  // 	outbyte='\0';
  // 	for (int j = 0; j < 8; ++j)
  // 	{
  // 		total_bits++;
  // 		str_buf += result_str[j+i];
  // 		outbyte = outbyte << 1;
  // 		if (result_str[j+i] == '1')
	 //  		outbyte |= 1;
  // 	}
  // 	//total_bits += 8;
  // 	ofs.write((char *)&outbyte,sizeof(unsigned char));
  // }

  // //cout<<total_bits<<endl;
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
  // 	lackbits = 8-result_str.length()+total_bits;
  // 	cout<<lackbits<<endl;
  // 	ofs.write((char *)&lackbits,sizeof(unsigned char));
  // }
  // else
  // {
  // 	lackbits = 0;
  // 	ofs.write((char *)&lackbits,sizeof(unsigned char));
  // }
  if (result_str.length() % 8 == 0)
  {
  	for (int i = 0; i < result_str.length(); i += 8)
	{
	  //str_buf = "";
	  outbyte='\0';
	  for (int j = 0; j < 8; ++j)
	  {
	  	//str_buf += result_str[j+i];
	  	outbyte = outbyte << 1;
	  	if (result_str[j+i] == '1')
		  	outbyte |= 1;
	  }
	  lackbits = 0;
	  ofs.write((char *)&outbyte,sizeof(unsigned char));
	}
  }
  else
  {
  	lackbits = 	8 - (result_str.length() - ((result_str.length() / 8) * 8));
  	for (int i = 0; i < lackbits; ++i)
  	{
  		result_str += "0";
  	}
  	//cout<<result_str.length()<<endl;
  	for (int i = 0; i < result_str.length(); i += 8)
	{
	  //str_buf = "";
	  outbyte='\0';
	  for (int j = 0; j < 8; ++j)
	  {
	  	//str_buf += result_str[j+i];
	  	outbyte = outbyte << 1;
	  	if (result_str[j+i] == '1')
		  	outbyte |= 1;
	  }
	  ofs.write((char *)&outbyte,sizeof(unsigned char));
	}
  }
  ofs.write((char *)&lackbits,sizeof(unsigned char));
  ofs.close();
}

void decompress(string inputFilename, string outputFilename) 
{
	ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  	//ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);

	unsigned char temp_num;
	UINT result_str_len;
  	UINT unique_char_nums;
  	UINT temp_char;
  	UINT temp_char_fre;
  	vector<UINT> char_vec;
  	vector<UINT> char_fre_vec;

	ifs.read((char*)&temp_num, sizeof(unsigned char));
	result_str_len = temp_num;

	//cout<<result_str_len<<endl;

  	ifs.read((char*)&temp_num, sizeof(unsigned char));
  	unique_char_nums = temp_num;
  	for (int i = 0; i < unique_char_nums*8; i += 8)
  	{
  		ifs.read((char*)&temp_num, sizeof(unsigned char));
  		temp_char = temp_num;
  		//cout<<temp_char<<endl;
  		char_vec.push_back(temp_char);
  	}
  	//cout<<"--------"<<endl;
  	for (int i = 0; i < unique_char_nums*8; i += 8)
  	{
  		ifs.read((char*)&temp_num, sizeof(unsigned char));
  		temp_char_fre = temp_num;
  		//cout<<temp_char_fre<<endl;
  		char_fre_vec.push_back(temp_char_fre);
  	}
  	//cout<<"--------"<<endl;
  	//cout<<unique_char_nums<<endl;
  	//ifs.close();

  	vector<pair<UINT,int> > vec; 
  	for (int i = 0; i < unique_char_nums; ++i)
  	{
  		vec.push_back(pair<UINT,int>(char_vec[i],char_fre_vec[i]));
  	}

  	HuffmanTree huffmantree(vec);

  	// int str_len = 0;
  	// if (result_str_len % 8 == 0)
  	// 	str_len = result_str_len;
  	// else
  	// 	str_len = (((result_str_len / 8) + 1) * 8);	
  	// cout<<str_len<<endl;
  	string result_str = "";
  	for (int i = 0; i < result_str_len; i+=8)
  	{
		ifs.read((char*)&temp_num, sizeof(unsigned char));
		UINT each_char = temp_num;
		bitset<8> bitvec(each_char);
		result_str += bitvec.to_string();
	}
	//cout<<result_str.length()<<endl;
	ifs.read((char*)&temp_num, sizeof(unsigned char));
	UINT lackbits = temp_num;
	for (int i = 0; i < lackbits; ++i)
	{
		result_str.erase(result_str.end()-1);
	}
	//cout<<result_str<<endl;
	//cout<<lackbits<<endl;
	vector<char> all_file_chars;
	huffmantree.GetoriginChar(huffmantree.get_root(),result_str,0);
	// for (int i = 0; i < huffmantree.chars_get.size(); ++i)
	// {
	// 	all_file_chars.push_back(huffmantree.chars_get[i]);
	// 	cout<<huffmantree.chars_get[i];
	// }
}

int main()
{
	//compress("trace03.txt","out.txt");
	decompress("out.txt","out2");
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
	// //sin(test[0]);

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
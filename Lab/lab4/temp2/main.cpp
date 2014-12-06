#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>

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
    //ofs.put(c);
  ifs.close();
  //ofs.close();

  sortMapByValue(test,vec);

  for (int i = 0; i < vec.size(); ++i)
  {
  	cout<<vec[i].first<<": "<<vec[i].second<<endl;
  }

  HuffmanTree huffmantree(vec);
  huffmantree.SetHuffmanCode(huffmantree.get_root(),result,0);

  //cout<<"-------"<<endl;
  // ifs.open(inputFilename.c_str(), ios::in | ios::binary);
  // while (ifs.get(c)) 
  // {
  // 	result_str += huffmantree.huffmancode[c];
  // }
  // ifs.close();
  // reverse(result_str.begin(),result_str.end());
  // bitset<128> bitvec(result_str);
  // cout<<bitvec<<endl;
  // cout<<result_str<<endl;
  // for (its = huffmantree.huffmancode.begin(); its != huffmantree.huffmancode.end(); its++)
  // {
  //   cout<<its->first<<": "<<its->second<<endl;
  // }
}

int main()
{
	//compress("trace03.txt","out.txt");
	char* result;
	vector<UINT> vec;
	map<UINT,int> test;
	vector<pair<UINT,int> > temp_vec;  
	map<UINT,string>::iterator its;
	vec.push_back('a');
	vec.push_back('b');
	vec.push_back('c');
	vec.push_back('c');
	vec.push_back('c');
	vec.push_back('d');
	vec.push_back('d');
	vec.push_back('d');
	vec.push_back('d');
	vec.push_back('d');
	vec.push_back('d');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	// vec.push_back('f');
	// vec.push_back('d');
	// vec.push_back('h');
	// vec.push_back('d');
	// vec.push_back('h');
	// vec.push_back('g');
	// vec.push_back('j');
	// vec.push_back(10);
	// vec.push_back(13);
	for (int i = 0; i < vec.size(); ++i)
	{
		test[vec[i]]++;
	}

 	sortMapByValue(test,temp_vec);  

 	for (int i = 0; i < temp_vec.size(); ++i)
  	{
  		cout<<temp_vec[i].first<<": "<<temp_vec[i].second<<endl;
  	}

	HuffmanTree huffmantree(temp_vec);

	huffmantree.SetHuffmanCode(huffmantree.get_root(),result,0);
	for (its = huffmantree.huffmancode.begin(); its != huffmantree.huffmancode.end(); its++)
	{
		cout<<its->first<<": "<<its->second<<endl;
	}
	return 0;
}
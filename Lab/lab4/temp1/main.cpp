#include "HuffmanTree.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int cmp(const pair<char,int>& x, const pair<char,int>& y)  
{  
 	return x.second < y.second;  
}  
   
void sortMapByValue(map<char,int>& tMap, vector<pair<char,int> >& tVector)  
{  
	for (map<char,int>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)  
	{  
		tVector.push_back(make_pair(curr->first, curr->second));  
	}  
   
 	sort(tVector.begin(), tVector.end(), cmp);  
}  

int main()
{
	char* result;
	vector<char> vec;
	map<char,int> test;
	vector<pair<char,int> > temp_vec;  
	map<char,string>::iterator its;
	vec.push_back('a');
	vec.push_back('f');
	vec.push_back('b');
	vec.push_back('b');
	vec.push_back('c');
	vec.push_back('c');
	vec.push_back('c');
	vec.push_back('d');
	vec.push_back('d');
	vec.push_back('d');
	vec.push_back('d');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('e');
	vec.push_back('f');
	vec.push_back('f');
	vec.push_back('a');
	vec.push_back('c');
	for (int i = 0; i < vec.size(); ++i)
	{
		test[vec[i]]++;
	}

 	sortMapByValue(test,temp_vec);  

	HuffmanTree huffmantree(temp_vec);
	huffmantree.SetHuffmanCode(huffmantree.get_root(),result,0);
	for (its = huffmantree.huffmancode.begin(); its != huffmantree.huffmancode.end(); its++)
	{
		cout<<its->first<<": "<<its->second<<endl;
	}
	return 0;
}
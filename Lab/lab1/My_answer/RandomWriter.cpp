/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name: 李林
 * Student ID: 5130379091
 * This file is the starter project for the random writer problem.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
//#include "map.h"
#include <map>
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "filelib.h"
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

// int count_str(vector<string>& vec,string& str)
// {
// 	int result = 0;
// 	for (int i = 0; i < vec.size(); ++i)
// 	{
// 		if(vec[i] == str)
// 			result++;
// 	}
// 	return result;
// }

// int count_char(vector<char>& vec,char& ch)
// {
// 	int result = 0;
// 	for (int i = 0; i < vec.size(); ++i)
// 	{
// 		if(vec[i] == ch)
// 			result++;
// 	}
// 	return result;
// }

// int get_value(vector<int>& vec)
// {
// 	int result = 0 ;
// 	for (int i = 0; i < vec.size(); ++i)
// 	{
// 		if(vec[i] >= result)
// 			result = vec[i];
// 	}
// 	return result;
// }

// vector<char> get_next_char(vector<char>& vec,string& str)
// {
// 	vector<char> result;
// 	int _size = vec.size();
// 	int len = str.length();
// 	bool judge = true;
// 	for (int i = 0; i < _size-len; ++i)
// 	{
// 		judge = true;
// 		for(int j = 0; j < len; ++j)
// 		{
// 			if(vec[i+j] != str[j])
// 			{
// 				judge = false;
// 				break;
// 			}
// 		}
// 		if(judge)
// 			result.push_back(vec[i+len+1]);
// 	}
// 	return result;
// }

int main() {

	string filename;					//file name
	int order;							//Markov order
	char ch;
	ifstream ist;
	string temp = "";
	int stop = 0;						//time to stop

	vector<char> all_char;				//all chars in the article
	vector<string> order_k_str;			//the vector stores all order-k strs

	map<string,int>init_str_map;		//the map stores all order-k strs and their frequency
	map<string,int>::iterator its;		//map iterator
	vector<string> init_str;			//the vector stores the init_str(s)

	//map<int,string> random_str;
	map<char,int> next_char_map;		//the map stores all next chars and their frequency
	map<char,int>::iterator itc;
	//vector<int> next_char_fre;				//the vector stores the next char(s)

	vector<char> result_file;			//the output vector

	string now_str_seed;				//the current str seed
	char now_char_seed;					//the current char

	while(1)
	{
		cout<<"Enter the source text: ";
		cin>>filename;
		ist.open(filename.c_str());
		if(!ist)
			cout<<"Unable to open that file.  Try again."<<endl;
		else
		{
			cout<<"Enter the Markov order [0-10]: ";
			cin>>order;
			break;
		}
	}

	while(ist.get(ch))
	{
		all_char.push_back(ch);
	}

	ist.close();

	for (int i = 0; i < all_char.size(); ++i)
	{
		if(i % order == 0)
			temp = "";

		temp += all_char[i];

		if(((i+1) % order == 0) || (i == all_char.size()-1))
			order_k_str.push_back(temp);
	}

	for (int i = 0; i < order_k_str.size(); ++i)
	{
		init_str_map[order_k_str[i]]++;
	}

	int maxcount = 0;
	for (its = init_str_map.begin(); its != init_str_map.end(); its++)
	{
		if (maxcount < its->second)
		{
			maxcount = its->second;
		}
	}

	for (its = init_str_map.begin(); its != init_str_map.end(); its++)
	{
		if (maxcount == its->second)
		{
			init_str.push_back(its->first);
		}
	}

	now_str_seed = init_str[0];

	for (int i = 0; i < order; ++i)
	{
		result_file.push_back(now_str_seed[i]);	
	}

	int _size = all_char.size();
	int _len = order;

	while(stop <= 2000)
	{
		next_char_map.clear();
		//next_char_fre.clear();

		for (int i = 0; i < _size-_len; ++i)
		{
			bool judge = true;
			for (int j = 0; j < _len; ++j)
			{
				if (all_char[i+j] != now_str_seed[j])
				{
					judge = false;
					break;
				}
			}
			if (judge)
			{
				next_char_map[all_char[i+_len]]++;
			}
		}

		if(next_char_map.size() == 0)
			break;

		int sumcount = 0;

		//cout<<"---------"<<endl<<next_char_map.size()<<endl;
		for (itc = next_char_map.begin(); itc != next_char_map.end(); itc++)
		{
			//next_char_fre.push_back(itc->second);
			sumcount += itc->second;
		}

		//cout<<"---------"<<endl;

		srand((unsigned)time(NULL));//setRandomSeed(1);
		int temp = randomInteger(0,sumcount-1);
		//cout<<temp<<endl;
		int pre_count = 0;

		for (itc = next_char_map.begin(); itc != next_char_map.end(); itc++)
		{
			if((temp >= pre_count) && (temp < (pre_count+itc->second)))
				now_char_seed = itc->first;
			pre_count += itc->second;
		}

		//cout<<"--------"<<endl;

		//now_char_seed = next_char[0];
		result_file.push_back(now_char_seed);

		for (int i = 0; i < order-1; ++i)
		{
			now_str_seed[i] = now_str_seed[i+1];
		}
		now_str_seed[order-1] = now_char_seed;

		//cout<<"-----------"<<endl<<now_str_seed<<endl;

		stop = result_file.size();
	}

	//cout<<next_char.size()<<endl;
	for (int i = 0; i < result_file.size(); ++i)
	{
		cout<<result_file[i];
	}
	//cout<<maxcount<<endl<<maxstr<<endl;
	cout<<endl;
  	return 0;
}

//aaa aaa aaa aax aaa aaa aaa aaa x
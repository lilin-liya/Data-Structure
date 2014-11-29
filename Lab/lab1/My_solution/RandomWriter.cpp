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
#include <map>
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "filelib.h"

using namespace std;

int main() {

	string filename;					//file name
	string input_order;
	int order;							//Markov order
	char ch;
	ifstream ist;
	string temp = "";
	int stop = 0;						//time to stop

	vector<char> all_char;				//all chars in the article
	vector<string> order_k_str;			//the vector stores all order-k strs

	map<char,int>order_0_map;			//the map stores all chars and their frequency in the file
	map<char,int>::iterator order_0_it;	

	map<string,int>init_str_map;		//the map stores all order-k strs and their frequency
	map<string,int>::iterator its;		//map iterator
	vector<string> init_str;			//the vector stores the init_str(s)

	map<char,int> next_char_map;		//the map stores all next chars and their frequency
	map<char,int>::iterator itc;
	
	vector<char> result_file;			//the output vector

	string now_str_seed;				//the current str seed
	char now_char_seed;					//the current char

	//test the input
	while(1)
	{
		cout<<"Enter the source text: ";
		cin>>filename;
		ist.open(filename.c_str());
		if(ist)
			break;
		if(!ist)
			cout<<"Unable to open that file.  Try again."<<endl;
	}
	while(1)
	{
		cout<<"Enter the Markov order [0-10]: ";
		cin>>order;

		if (!cin)
		{
			cin.clear();
			cin.sync();
			cin.ignore(0x7FFFFFFF, '\n');
			cout<<"Illegal integer format.  Try again"<<endl;
		}
		else
		{
			if((order >= 0) && (order <= 10))
				break;
			if((order < 0) || (order > 10))
				cout<<"The value is out of range."<<endl;
		}
	}

	//read file and store it into the vector
	while(ist.get(ch))
	{
		all_char.push_back(ch);
		order_0_map[ch]++;					//this map is for the order 0
	}

	ist.close();			//close the file

	//when order is 0
	if(order == 0)
	{
		int sumcount = 0;

		for (order_0_it = order_0_map.begin(); order_0_it != order_0_map.end(); order_0_it++)
		{
			sumcount += order_0_it->second;
		}
		//srand((unsigned)time(NULL));//setRandomSeed(0);
		while(stop < 2000)
		{
			//set time seed
			
			int temp = randomInteger(0,sumcount-1);

			int pre_count = 0;

			//choose next char according their frequency
			for (order_0_it = order_0_map.begin(); order_0_it != order_0_map.end(); order_0_it++)
			{
				if((temp >= pre_count) && (temp < (pre_count+order_0_it->second)))
					result_file.push_back(order_0_it->first);
				pre_count += order_0_it->second;
			}
			stop = result_file.size();
		}
	}

	//when order isn't 0
	if(order != 0)
	{
		//choose the init str seed
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

		while(stop < 2000)
		{
			next_char_map.clear();

			//get next char(s)
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

			for (itc = next_char_map.begin(); itc != next_char_map.end(); itc++)
			{
				sumcount += itc->second;
			}

			//choose next char according to their frequency
			//srand((unsigned)time(NULL));//setRandomSeed(0);
			int temp = randomInteger(0,sumcount-1);
			//cout<<"-------------"<<endl<<temp<<endl;
			int pre_count = 0;

			for (itc = next_char_map.begin(); itc != next_char_map.end(); itc++)
			{
				if((temp >= pre_count) && (temp < (pre_count+itc->second)))
					now_char_seed = itc->first;
				pre_count += itc->second;
			}

			result_file.push_back(now_char_seed);

			for (int i = 0; i < order-1; ++i)
			{
				now_str_seed[i] = now_str_seed[i+1];
			}
			now_str_seed[order-1] = now_char_seed;

			stop = result_file.size();
		}
	}

	//cout the result
	for (int i = 0; i < result_file.size(); ++i)
	{
		cout<<result_file[i];
	}

  	return 0;
}
/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name: 李林
 * Student ID: 5130379091
 * This file is the starter project for the word ladder problem.
 * [TODO: extend the documentation]
 */


 /*由于个人水平有限，程序算法不是很好，过长的ladder所需时间较长，
   例如从"sleep"转换到"awake"，以及从"awake"转换到"sleep"，
   但make score显示全部pass，测试所耗时间大概为30S+左右，
   所以，还请老师在最终测试程序时耐心等待一会儿，谢谢！*/

#include "lexicon.h"
#include "queue.h"
#include "vector.h"
#include <iostream>
#include <string>
#include "stdio.h"

using namespace std;

bool match(Vector<string>& vec,string& str)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == str)
		{
			return true;
		}
		else
			continue;
	}
}

int main() {
	string start_word;
	string dest_word;
	Queue<Vector<string> > ladder_store;

	Vector<string> now_ladder;
	Vector<string> solut_ladder;

	Lexicon test_words;
	test_words.addWordsFromFile("EnglishWords.dat");
	
	while(1)
	{

		Vector<string> temp_ladder;

		string temp_word;
		Vector<string> pos_ladder;
		Vector<string> about_last_word;

		start_word = "";
		dest_word = "";
		cout<<"Enter start word (RETURN to quit): ";
		
		getline(cin,start_word);

		if (start_word == "")
		{
			cout<<"Goodbye!"<<endl;
		 	break;
		}

		cout<<"Enter destination word: ";
		getline(cin,dest_word);

		now_ladder.clear();
		solut_ladder.clear();
		ladder_store.clear();

		for (int i = 0; i < dest_word.length(); ++i)
		{
			string tmp = dest_word;
			for (char j = 'a'; j <= 'z'; ++j)
			{
				if (dest_word[i] == j)
					continue;
				tmp[i] = j;
				if (test_words.contains(tmp))
				{
				about_last_word.push_back(tmp);	
				}
			}
		}

		if((start_word.length() == dest_word.length())
			&& test_words.contains(start_word)
			&& test_words.contains(dest_word)
			&& about_last_word.size() != 0)
		{	
			now_ladder.push_back(start_word);
			ladder_store.enqueue(now_ladder);
		}

		while(!ladder_store.isEmpty())
		{
			Vector<string> old_pos = pos_ladder;

			pos_ladder.clear();
			temp_ladder.clear();

			temp_ladder = ladder_store.dequeue();
			temp_word = temp_ladder.get(temp_ladder.size()-1);

			if (solut_ladder.size() != 0)
			{
				break;
			}
			if (temp_word == dest_word)
			{
				solut_ladder = temp_ladder;
				break;
			}

			for (int i = 0; i < temp_word.length(); ++i)
			{
				string tmp = temp_word;
				for (char j = 'a'; j <= 'z'; ++j)
				{
					if (temp_word[i] == j)
						continue;
					tmp[i] = j;
					if (test_words.contains(tmp))
					{
						pos_ladder.push_back(tmp);
					}
				}
			}

			for (int i = 0; i < pos_ladder.size(); ++i)
			{
				if ((!match(temp_ladder,pos_ladder[i])) && !match(old_pos,pos_ladder[i]))
				{
					Vector<string> copy_temp_ladder;
					copy_temp_ladder = temp_ladder;
					copy_temp_ladder.push_back(pos_ladder[i]);
					ladder_store.enqueue(copy_temp_ladder);

					copy_temp_ladder.clear();
				}
				if (pos_ladder[i] == dest_word)
				{
					solut_ladder = temp_ladder;
					solut_ladder.push_back(pos_ladder[i]);
					break;
				}
			}

			old_pos.clear();
		}

		if (solut_ladder.size() != 0)
		{
			for (int i = 0; i < solut_ladder.size(); ++i)
			{
				cout<<solut_ladder[i]<<" ";
			}
			cout<<endl;
		}
		else
			cout<<endl;

	}
 	return 0;
}

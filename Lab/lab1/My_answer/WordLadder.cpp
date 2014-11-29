/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name: 李林
 * Student ID: 5130379091
 * This file is the starter project for the word ladder problem.
 * [TODO: extend the documentation]
 */

#include "lexicon.h"
#include "queue.h"
#include "vector.h"
#include <iostream>
#include <string>
#include "stdio.h"

using namespace std;

bool match(Vector<string> vec,string str)
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
	cout<<"Enter start word (RETURN to quit):";
	cin>>start_word;
	cout<<"Enter destination word:";
	cin>>dest_word;

	now_ladder.clear();
	ladder_store.clear();
	
	now_ladder.push_back(start_word);
	ladder_store.enqueue(now_ladder);

	Vector<string> temp_ladder;
	string temp_word;
	Vector<string> pos_ladder;

	while(!ladder_store.isEmpty())
	{

		Vector<string> old_pos = pos_ladder;

		pos_ladder.clear();
		temp_ladder.clear();

		temp_ladder = ladder_store.dequeue();
		temp_word = temp_ladder.get(temp_ladder.size()-1);

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
			//cout<<pos_ladder[i]<<" ";
			if ((!match(temp_ladder,pos_ladder[i])) && !match(old_pos,pos_ladder[i]))
			{
				Vector<string> copy_temp_ladder;
				copy_temp_ladder = temp_ladder;
				copy_temp_ladder.push_back(pos_ladder[i]);
				ladder_store.enqueue(copy_temp_ladder);

				// for (int i = 0; i < copy_temp_ladder.size(); ++i)
				// {
				// 	cout<<copy_temp_ladder[i]<<" ";
				// }

				copy_temp_ladder.clear();
			}
			//cout<<endl;
		}

		old_pos.clear();
	}

	if (solut_ladder.size() != 0)
	{
		cout<<"Found ladder:";
		for (int i = 0; i < solut_ladder.size(); ++i)
		{
			cout<<solut_ladder[i]<<" ";
		}
		cout<<endl;
	}
	else
		cout<<"no word ladder exists."<<endl;

	}
 	return 0;
}

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAXSIZE = 256;		//The max size of the hashtable;set as 256 because of the ASCII

class HashTable
{
private:
	char elem[MAXSIZE];			//all the chars
	int ele_times[MAXSIZE];		//the showing times of each char 
	bool flag[MAXSIZE];			//is the position be taken
	int Hash(char ch);			//Hash function
public:
	HashTable();
	int Search(char ch);		//return every chars show time
	void Insert(char ch);		//add new eles into the hashtable
	void clear();				//clear the hashtable
	~HashTable();
};

//all the eles be inited as 0
HashTable::HashTable()
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		ele_times[i] = 0;
		flag[i] = 0;
	}
}

//just use the char's ASCII as the Hash function
int HashTable::Hash(char ch)
{
	int result = (int)ch;
	return result;
}

void HashTable::Insert(char ch)
{
	int pos = Hash(ch);			//get position
	ele_times[pos]++;			//this char's show time ++
	if (!flag[pos])				//insert into the hashtable if this place isn't be taken
	{
		elem[pos] = ch;
		flag[pos] = 1;
	}
}

int HashTable::Search(char ch)	//return ele_times[pos]
{
	int pos = Hash(ch);
	return ele_times[pos];
}

void HashTable::clear()
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		ele_times[i] = 0;		//char's show time set as 0
		flag[i] = 0;			//all the position isn't used
		elem[i] = '\0';			//clear the elem
	}
}

HashTable::~HashTable()
{
}

int main()
{
	string input = "hash.in";
	string output = "hash.out";
	int n;
	int num;		//numbers of test cases

	ifstream ist(input.c_str());
	if (!ist)
	{
		cout << "can't open input file" << endl;
	}
	while (ist >> n)
	{
		num = n;
	}
	ist.close();

	if (num == 0)
	{
		cout << "The input file is empty" << endl;
	}
	string str;
	int judge = 0;
	string* test_cases = new string[num+1];		//all the test cases
	string* test_results = new string[num];		//all the results
	ist.open(input.c_str());

	while ((ist >> str) && (judge <= num))
	{
		test_cases[judge] = str;
		judge++;
	}
	ist.close();

	HashTable myhash;
	for (int order = 0; order < num; order++)
	{
		bool exist = 0;
		string test_str = test_cases[order+1];
		int len = test_str.length();
		for (int i = 0; i < len; i++)
		{
			myhash.Insert(test_str[i]);
		}
		for (int i = 0; i < len; i++)
		{
			if (myhash.Search(test_str[i]) == 1)
			{
				exist = 1;
				string temp = "";
				temp += test_str[i];
				test_results[order] = temp;
				break;
			}
		}
		if (!exist)
		{
			test_results[order] = "None";
		}
		myhash.clear();
	}
	ofstream ost(output.c_str());
	if (!ost)
	{
		cout << "can't open output file" << endl;
	}
	for (int i = 0; i < num; i++)
	{
		ost << test_results[i] << endl;
	}
	ost.close();
	cout << "All the answers are wrote into ""\"hash.out\"." << endl;
	cout << "Please check the file." << endl;

	delete[] test_cases;
	delete[] test_results;
	
	return 0;
}

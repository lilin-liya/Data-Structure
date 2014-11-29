#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class City
{
private:
	int row;			//the row of the city ground
	int col;			//the col of the city ground
	int population;		//the current population of the city
public:
	City(int m, int n);
	int max_population;	//max population of the city
	int **ground;		//the city ground
	int **result;		//the result construction ground
	vector<int> get_nearby(int m, int n);	//to get the four squares which are near the (m,n)
	bool check_red(int m, int n);			//check if there is suitable for red house
	bool check_green(int m, int n);			//check if there is suitable for green house
	bool check_blue(int m, int n);			//check if there is suitable for blue house
	bool check();							//check if all the construction plan is correct

	void Construct(int m, int n);			//this is my recursive function
	~City();
};
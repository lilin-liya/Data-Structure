#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class City
{
private:
	int row;
	int col;
	//int **ground;
	int population;
	int three_num;
	//int count;
	bool is_full;
public:
	City(int m, int n);
	int max_population;
	int **ground;
	int **result;
	vector<int> get_nearby(int m, int n);
	bool check_red(int m, int n);
	bool check_green(int m, int n);
	bool check_blue(int m, int n);
	bool check();

	void Construct(int m, int n);
	void clear();
	~City();
};
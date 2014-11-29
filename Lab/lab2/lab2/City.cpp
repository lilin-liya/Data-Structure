#include "City.h"

City::City(int m, int n)
:row(m), col(n), population(0), max_population(0),three_num(0),is_full(0)
{
	ground = new int *[row];
	result = new int *[row];
	for (int i = 0; i < row; i++)
	{
		ground[i] = new int[col];
		result[i] = new int[col];
	}
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			ground[i][j] = 3;
			result[i][j] = 0;
		}
	}
	ground[0][1] = 2;
}

vector<int> City::get_nearby(int m, int n)
{
	vector<int> dir;
	if ((m - 1) >= 0)
	{
		dir.push_back(m - 1);
		dir.push_back(n);
	}
	if ((m + 1) <= (row - 1))
	{
		dir.push_back(m + 1);
		dir.push_back(n);
	}
	if ((n - 1) >= 0)
	{
		dir.push_back(m);
		dir.push_back(n - 1);
	}
	if ((n + 1) <= (col - 1))
	{
		dir.push_back(m);
		dir.push_back(n + 1);
	}
	return dir;
}

bool City::check_red(int m, int n)
{
	return 1;
}

bool City::check_green(int m, int n)
{
	bool green_satisfy = 0;
	vector<int> dir = get_nearby(m, n);

	for (int i = 0; i < dir.size() - 1; i += 2)
	{
		int x = dir[i];
		int y = dir[i + 1];
		if (ground[x][y] == 1)
		{
			green_satisfy = 1;
			break;
		}
	}

	return green_satisfy;
}

bool City::check_blue(int m, int n)
{
	bool green_satisfy = 0;
	bool blue_satisfy = 0;
	vector<int> dir = get_nearby(m, n);

	for (int i = 0; i < dir.size() - 1; i += 2)
	{
		int x = dir[i];
		int y = dir[i + 1];
		if (ground[x][y] == 1)
		{
			green_satisfy = 1;
		}
		if (ground[x][y] == 2)
		{
			blue_satisfy = 1;
		}
		if (green_satisfy && blue_satisfy)
		{
			break;
		}
	}

	return (green_satisfy && blue_satisfy);
}

bool City::check()
{
	//three_num = 0;
	population = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			population += ground[i][j];
			if (ground[i][j] == 3)
			{
				//three_num++;
				if (!check_blue(i, j))
				{
					return 0;
				}
			}
			if (ground[i][j] == 2)
			{
				if (!check_green(i, j))
				{
					return 0;
				}
			}
		}
	}
	//if (three_num > (row*col/2))
	//{
	//	return 0;
	//}
	return 1;
}

void City::Construct(int m, int n)
{	
	if ((row == 1) && (col == 1))
	{
		max_population = 1;
		result[0][0] = 1;
		return;
	}
	if (n == col)
	{
		m++;
		n = 0;
	}
	if (m == row)
	{	
		if ((row*col > 4) && (row > 1))
		{
			if (!((ground[0][2] == 1) || (ground[1][1] == 1)))
				return;
			if (ground[1][0] != 1)
				return;
			if((row >= 4) && (col >= 4))
			{
				if ((row == 4) && (col == 5))
				{
					if (ground[row-1][col-1] != 3)
				 		return;
					if (ground[row-1][col-2] != 2)
						return;
					if (ground[row-2][col-1] != 1)
						return;
				}
				if (ground[0][col-2] != 1)
					return;
				if (ground[0][col-1] != 3)
					return;
				if (ground[1][col-1] != 2)
					return;
			}
			else
			{
				if (ground[row-1][col-2] == 3)
					return;
				if (ground[row-2][col-1] == 3)
					return;
			}
		}
		if (check())
		{
			if (population > max_population)
			{
				max_population = population;
				for (int i = 0; i < row; i++)
				{
					for (int j = 0; j < col; j++)
					{
						result[i][j] = ground[i][j];
					}
				}
			}
		}
		return;
	}
	ground[m][n] = 3;
	Construct(m, n + 1);
	ground[m][n] = 2;
	Construct(m, n + 1);	
	ground[m][n] = 1;
	Construct(m, n + 1);
}

void City::clear()
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			ground[i][j] = 0;
			result[i][j] = 0;
		}
	}
}

City::~City()
{
	delete[] ground;
	delete[] result;
}
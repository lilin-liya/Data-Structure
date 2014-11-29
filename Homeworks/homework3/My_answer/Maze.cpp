/*
 * [TODO] delte this comment
 * Our test compiler is g++,
 * you can use '$ g++ -v' to see version, suggest 4.8 or newest,
 * add any header file you need from standard C++ library
 * and create any class or function you need to use
 */

/*
 * Use standard I/O to read test file and output answer.
 * There are three test file: testmap_1.txt, testmap_2.txt, testmap_3.txt,
 * and your output should like:
 * testmap_1: (1,1) (1,2) (1,3) (2,3) ...
 * More detail on course websit
 */

#include <fstream>
#include <iostream>
#include <string>
#include "point.h"
#include "direction.h"
#include "vector.h"
#include "strlib.h"

using namespace std;

class Maze
{
private:
	int length;				//length of the maze
	int width;				//width of the maze
	char **maze;			//this maze
	bool **mark;			//mark is to record if this point has been marked
	Vector<Point> path;		//store the solution
	Point move(Point start, Direction dir);		//get next point
	bool isOutside(Point start);
	bool wallExists(Point start, Direction dir);
	void markSquare(Point start);
	void unmarkSquare(Point start);
	bool isMarked(Point start);
public:
	Maze(string filename);
	Point getStartPosition();
	bool solveMaze(Maze & my_maze, Point start);
	void get_path();		//cout the path
	~Maze();
};

Maze::Maze(string filename)
{
	ifstream ist(filename.c_str());		//open the file and get maze
	int n;								
	string str;

	Vector<string> temp;			
	Vector<int> temp_int;				//temp_int stores the length and width in the file
	while(getline(ist,str))
	{
		temp.push_back(str);
	}
	stringstream is(temp[0]);
	while(is>>n)
	{
		temp_int.push_back(n);
	}
	length = temp_int[0];
	width = temp_int[1];

	maze = new char *[length];				//init the maze
	for(int i = 0;i < length; i++)
		maze[i] = new char[width];

	mark = new bool *[length];				//init the mark
	for(int i = 0;i < length; i++)
		mark[i] = new bool[width];

	for (int i = 0;i < width; i++)
	{
		stringstream ss(temp[i+1]);
		for (int j = 0;j < length; j++)
		{
			ss.get(maze[j][i]);
			mark[j][i] = 0;
		}
	}
}

Point Maze::getStartPosition()
{
	int px;
	int py;
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if(maze[i][j] == 'S')
			{
				px = i;
				py = j;
				break;
			}
		}
	}
	return Point(px,py);
}

bool Maze::isOutside(Point start)		//isOutside means the point is 'E'
{
	int px = start.getX();
	int py = start.getY();
	return (maze[px][py] == 'E');
}

bool Maze::wallExists(Point start, Direction dir)
{
	int px = start.getX();
	int py = start.getY();

	if ((dir == NORTH) && (py == 0))
		return true;
	if ((dir == EAST) && (px == length-1))
		return true;
	if ((dir == SOUTH) && (py == width-1))
		return true;
	if ((dir == WEST) && (px == 0))
		return true;

	if ((dir == NORTH) && (py > 0))
		py--;
	if ((dir == EAST) && (px < length-1))
		px++;
	if ((dir == SOUTH) && (py < width-1))
		py++;
	if ((dir == WEST) && (px > 0))
		px--;
	return ((maze[px][py] == '+') || (maze[px][py] == '-') || (maze[px][py] == '|'));
}

Point Maze::move(Point start, Direction dir)		//get next point depend on the dir
{
	int px = start.getX();
	int py = start.getY();
	if ((dir == NORTH) && (py > 0))
		py--;
	if ((dir == EAST) && (px < length-1))
		px++;
	if ((dir == SOUTH) && (py < width-1))
		py++;
	if ((dir == WEST) && (px > 0))
		px--;
	return Point(px,py);
}

void Maze::markSquare(Point start)			//marksquare means the same point in mark is 1
{
	int px = start.getX();
	int py = start.getY();
	mark[px][py] = 1;
}

void Maze::unmarkSquare(Point start)		//unmarkSquare is the opposite of markSquare
{
	int px = start.getX();
	int py = start.getY();
	mark[px][py] = 0;	
}

bool Maze::isMarked(Point start)
{
	int px = start.getX();
	int py = start.getY();
	return mark[px][py];
}

//solveMaze uses the recursive to get a solution of the maze
bool Maze::solveMaze(Maze & my_maze, Point start)
{
	if(my_maze.isOutside(start)) 
		return true;
	if(my_maze.isMarked(start))
		return false;
	my_maze.markSquare(start);
	for(Direction dir = NORTH; dir <= WEST; dir++)
	{
		if(!my_maze.wallExists(start,dir))
		{
			Point next_point = move(start,dir);		//get next point
			if (!my_maze.isMarked(next_point))		//if the point hasn't been marked
			{
				path.push_back(next_point);			//then push_back in path
			}
			if(solveMaze(my_maze,next_point))
			{
				return true;
			}
		}
	}
	my_maze.unmarkSquare(start);
	return false;
}

void Maze::get_path()
{
	int _size = path.size();
	for (int i = 0; i < _size-1; ++i)
	{
		cout<<'('<<path[i].getX()<<','<<path[i].getY()<<')'<<' ';
	}
	cout<<'('<<path[_size-1].getX()<<','<<path[_size-1].getY()<<')';
}

Maze::~Maze()
{
	delete[] maze;
	delete[] mark;
}

int main()
{
	Maze my_maze1("testmap_1.txt");
	Maze my_maze2("testmap_2.txt");
	Maze my_maze3("testmap_3.txt");
	Point start1 = my_maze1.getStartPosition();
	Point start2 = my_maze2.getStartPosition();
	Point start3 = my_maze3.getStartPosition();
	if(my_maze1.solveMaze(my_maze1,start1))
	{
		cout<<"testmap_1: ";
		my_maze1.get_path();
		cout<<endl;
	}
	else
		cout<<"This maze has no solution"<<endl;
	if(my_maze2.solveMaze(my_maze2,start2))
	{
		cout<<"testmap_2: ";
		my_maze2.get_path();
		cout<<endl;
	}
	else
		cout<<"This maze has no solution"<<endl;
	if(my_maze3.solveMaze(my_maze3,start3))
	{
		cout<<"testmap_3: ";
		my_maze3.get_path();
		cout<<endl;
	}
	else
		cout<<"This maze has no solution"<<endl;
	return 0;
}
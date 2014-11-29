#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "KQueens.h"
#include "Chessboard.h"

/*
 * You should modify this function. Before you start, make
 * sure you have a clear idea of what you are doing.
 * Good Luck!
 */

using namespace std;

vector<int> queenlist;

bool check(int row)
{
	for (int i = 0; i < row; ++i)
	{
		if (queenlist[i] == queenlist[row])
		{
			return false;
		}
		if ((queenlist[i] - queenlist[row]) == (row - i))
		{
			return false;
		}
		if ((queenlist[i] - queenlist[row]) == (i - row))
		{
			return false;
		}
	}
	return true;
}

void place(int row,int board_row,int board_col,Chessboard *c,bool& get_one)
{
	for (int i = 0; i < board_col; ++i)
	{
		if (row == board_row && get_one)
		{
			get_one = 0;
			for (int a = 0; a < board_row; a++)
			{
				for (int b = 0; b < board_col; b++)
				{
					if (b == queenlist[a])
						c->board[a][b] = 1;
					else
						c->board[a][b] = 0;
				}
			}
			return;
		}
		queenlist[row] = i;
		if (check(row))
		{
			place(row+1,board_row,board_col,c,get_one);
			if(get_one == 0)
				return;
		}
	}
}

int KQueens(Chessboard *c)
{
	int result = 0;
	bool get_one=1;
	int row = c->rows;
	int col = c->cols;
	int min = row < col ? row : col;

	for (int i = 0; i < min; ++i)
	{
		queenlist.push_back(-1);
	}
	if (row <= col)
	{
		place(0,row,col,c,get_one);
	}
	else
	{	
		Chessboard *temp;
		temp = new Chessboard(col,row);
		place(0,col,row,temp,get_one);
		for (int i = 0; i < col; ++i)
		{
			for (int j = 0; j < row; ++j)
			{
				c->board[j][i] = temp->board[i][j];
			}
		}
	}
	
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (c->board[i][j] != 0)
			{
				result++;
			}
		}
	}
  	return result;
}
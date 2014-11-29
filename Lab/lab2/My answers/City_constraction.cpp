#include "City.h"
#include "time.h"
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{

	//if input is illegal,then error and exist
	if (argc != 3)
	{
		cout<<"Please enter right input and output filenames."<<endl;
		cout<<"such as: ./City input.txt output.txt"<<endl;
	}

	//continue when input is legal
	if (argc == 3)
	{
		string input = argv[argc-2];
		string output = argv[argc-1];

		int num;
		int case_num;
		vector<int> input_nums;

		ifstream ist;
		ist.open(input.c_str());

		while(ist>>num)
		{
			input_nums.push_back(num);
		}

		ist.close();

		case_num = input_nums[0];

		ofstream ost;
		ost.open(output.c_str());

		City* mycity;

		//I will explain why in "README"
		for (int i = 0; i < case_num; ++i)
		{
			int row = input_nums[i*2+1];
			int col = input_nums[i*2+2];
			int max = row > col ? row : col;
			int min = row <= col ? row : col;

			mycity = new City(min, max);	

			//if data is small ,go to this part
			if (min*max <= 16)
			{
				mycity->Construct(0,0);
			}
			else if (min == 4 && max == 5)
			{
				mycity->Construct(0,3);
			}			
			//if is 5*5 ,go to this part
			else if (min == 5 && max == 5)
			{
				City* tempcity;
				tempcity = new City(min-1,max);
				tempcity->Construct(0,3);
				for (int i = 0; i < (row-2); ++i)
				{
					for (int j = 0; j < col; ++j)
					{
				 		mycity->ground[i][j] = tempcity->result[i][j];
					}
				}
				mycity->Construct(row-3,col-1);
			}

			//else test cases go to this part
			else
			{
				mycity->Construct(0,3);
			}

			ost << mycity->max_population << endl;	

			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					if (row < col)
					{
			 			ost << mycity->result[i][j] << " ";
			 		}
			 		else
					{
			 			ost << mycity->result[j][i] << " ";
			 		}
				}
				ost << endl;
			}
		}

		ost.close();

		delete mycity;

		cout<<"All results are wrote into output.txt."<<endl;
		cout<<"Please check the file!"<<endl;
	}

  	return 0;
}
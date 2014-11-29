#include <iostream>  
#include <time.h>
#include <algorithm>

using namespace std;

//Merge two arrays
//one array is from data[low] to data[pivot]
//another array is from data[pivot+1] to data[high]
void Merge(int* data, int low, int pivot, int high)
{
	int i = low, j = pivot + 1;		//start at the begin of the two arrays
	while (i <= pivot && j <= high)
	{
		if (data[i] > data[j])  	//if some ele of the front array is larger than the behind
		{
			//right shift (data[i] to data[j]) and data[i] = data[j]
			//such as 1 3 5 7 2;i = 1,j=4
			//after right shift:it becomes 1 2 3 5 7 
			int tmp = data[j];			
			for (int t = j; t>i; t--)
				data[t] = data[t - 1];
			data[i] = tmp;
			++pivot;
			++j;
		}
		++i;
	}
}

//use recursive to realize In place Merge Sort
//In_place_MergeSort get the begin and end index of the array as its parameters
void In_place_MergeSort(int* data, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = (low + high) / 2;
		In_place_MergeSort(data, low, pivot);
		In_place_MergeSort(data, pivot + 1, high);
		Merge(data, low, pivot, high);
	}
}

//This is for testing In place Merge Sort
void test_sort()
{
	int data[100];
	int	copy_data[100];
	bool judge = 1;

	/*rand 100 numbers between 0 to 100,get the results of In place Merge Sort 
	and System Sort(),see if there is some thing different*/
	srand((unsigned)time(NULL));
	for (int i = 0; i < 100; i++)
	{
		int temp = rand() % 100;
		data[i] = temp;
		copy_data[i] = temp;
	}

	cout << "Before Sort:" << endl;
	//cout the init array
	for (int i = 0; i < 100; i++)
	{
		cout << data[i] << '\t';
	}
	cout << endl;

	cout << "After Sort:" << endl;

	cout << "Using In place Merge Sort:" << endl;
	In_place_MergeSort(data, 0, 99);			//here use In place Merge Sort to sort the array
	for (int i = 0; i < 100; i++)
	{
		cout << data[i] << '\t';
	}
	cout << endl;

	cout << "Using Sort():" << endl;
	sort(&copy_data[0], &copy_data[100]);		//here use System Sort to sort the array
	for (int i = 0; i < 100; i++)
	{
		cout << copy_data[i] << '\t';
	}
	cout << endl;

	for (int i = 0; i < 100; i++)
	{
		if (data[i] != copy_data[i])
			judge = 0;
	}
	if (judge)
		cout << "The results of two sorts are same" << endl;
	else
		cout << "something unexpended happen!!!" << endl;
}

int main(){
	test_sort();
	return 0;
}
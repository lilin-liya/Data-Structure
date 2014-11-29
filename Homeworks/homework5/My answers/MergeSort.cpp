#include <iostream>
#include <time.h>
#include <algorithm>

using namespace std;

//Merge two arrays
//one array is from data[first] to data[second-1]
//another array is from data[second] to data[high]
void Merge(int *data, int first, int second, int high)
{
	int *temp = new int[high + 1];
	int pivot = second - 1;
	int last = 0;
	int low = first;
	while (first <= pivot && second <= high)
	{
		if (data[first] <= data[second])
		{
			temp[last++] = data[first++];
		}
		else
			temp[last++] = data[second++];
	}
	if (first > pivot)
	{
		while (second <= high)
			temp[last++] = data[second++];
	}
	else
	{
		while (first <= pivot)
			temp[last++] = data[first++];
	}
	for (int i = 0; i < last; i++)
	{
		data[low++] = temp[i];
	}
	delete[] temp;
}

//use recursive to realize Merge Sort
void RecursiveMergeSort(int *data,int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = (low + high) / 2;
		RecursiveMergeSort(data, low, pivot);
		RecursiveMergeSort(data, pivot + 1, high);
		Merge(data, low, pivot+1, high);
	}
}

//MergeSort get one array which is to be sorted and its length as its parameters
void MergeSort(int *data,int length)
{
	RecursiveMergeSort(data, 0, length - 1);
}

//This is for testing Merge Sort
void test_sort()
{
	int data[100];
	int	copy_data[100];
	bool judge = 1;

	/*rand 100 numbers between 0 to 100,get the results of Merge Sort
	and System Sort(),see if there is some thing different*/
	srand((unsigned)time(NULL));
	for (int i = 0; i < 100; i++)
	{
		int temp = rand() % 100;
		data[i] = temp;
		copy_data[i] = temp;
	}

	cout << "Before Sort:" << endl;			//cout the init array
	for (int i = 0; i < 100; i++)
	{
		cout << data[i] << '\t';
	}
	cout << endl;

	cout << "After Sort:" << endl;

	cout << "Using Merge Sort:" << endl;
	MergeSort(data, 100);					//here use Merge Sort to sort the array
	for (int i = 0; i < 100; i++)
	{
		cout << data[i] << '\t';
	}
	cout << endl;

	cout << "Using Sort():" << endl;
	sort(&copy_data[0], &copy_data[100]);	//here use System Sort to sort the array
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
		cout << "The results of two sorts are the same." << endl;
	else
		cout << "something unexpended happen!!!" << endl;
}

int main()
{
	test_sort();
	return 0;
}
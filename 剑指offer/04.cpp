#include <iostream>
using namespace std;
bool findX(int **arr, int x,int row, int col)
{
	bool find = false;
	int i = row-1,j = 0;
	if (arr != NULL && row > 0 && col > 0)
	{
		while (i >= 0 && j < col)
		{
			if (x > arr[i][j])
			{
				++j;
			}
			else if(x < arr[i][j])
			{
				--i;
			}
			else
			{
				cout << i+1 << "," << j+1 << endl;
				return true;
			}
		}
	}
	return false;
}
int main()
{
	int row, col, x;
	cin >> row >> col;
	int **arr = new int *[row];
	for(int i = 0; i < row; ++i)
	{
		arr[i] = new int[col];
	}
	for(int i = 0; i < row; ++i)
	{
		for(int j = 0; j < col; ++j)
		{
			cin >> arr[i][j];
		}
	}
	cin >> x;
	cout << findX(arr, x,row,col);
	for(int i = 0; i < row; ++i)
	{
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}

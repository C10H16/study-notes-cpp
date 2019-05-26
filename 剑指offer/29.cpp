#include <iostream>
using namespace std;

void PrintMatrixInCircle(int** matrix, int cols, int rows, int start)
{
	int endX = cols - 1 - start;
	int endY = rows - 1 - start;

	// 从左到右打印一行
	// 肯定会执行
	for (int i = start; i <= endX; ++i)
	{
		int number = matrix[start][i];
		cout << number << " ";
	}
	
	// 从上到下打印一列
	// 终止行号需大于起始行号
	if (start < endY)
	{
		for(int i = start + 1; i <= endY; ++i)
		{
			int number = matrix[i][endX];
			cout << number << " ";
		}
	}

	// 从右到左打印一行
	// 打印的前提是至少有两行
	if (start < endX && start < endY)
	{
		for(int i = endX-1; i >= start; --i)
		{
			int number = matrix[endY][i];
			cout << number << " ";
		}
	}

	// 从上到下打印一行
	// 需要至少3行2列，即终止行号比起始行号至少大2
	if (start < endX && start < endY -1)
	{
		for (int i = endY -1; i >= start + 1; --i)
		{
			int number = matrix[i][start];
			cout << number << " ";
		}
	}
}

void PrintMatrixColockWisely(int** matrix, int cols, int rows)
{
	if (matrix == nullptr || cols <=0 || rows <=0)
	{
		return;
	}
	int start = 0;
	while (cols > start * 2 && rows > start * 2) // 循环条件
	{
		PrintMatrixInCircle(matrix, cols, rows, start);
		++start;
	}
}


int main()
{
	int rows, cols;
	cin >> rows >> cols;
	int** matrix = new int*[rows];
	for(int i = 0; i < rows; ++i)
	{
		matrix[i] = new int[cols];
	}
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			cin >> matrix[i][j];
		}
	}

	PrintMatrixColockWisely(matrix, cols, rows);
	return 0;
}
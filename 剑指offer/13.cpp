#include <iostream>
using namespace std;

int getDigitSum(int num) // 计算数位和
{
    int sum = 0;
    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

bool check(int threshold, int rows, int cols, int row, int col, bool** visited) // 检查是否能进如该格子
{
    if (row >= 0 && row < rows && col >= 0 && col < cols && getDigitSum(row) + getDigitSum(col) <= threshold && !visited[row][col])
        return true;
    return false;
}

int movingCountCore(int threshold, int rows, int cols, int row, int col, bool** visited)
{
    int count = 0;
    if (check(threshold, rows, cols, row, col, visited))
    {
        visited[row][col] = true;
        count = 1 + movingCountCore(threshold, rows, cols, row, col+1, visited)
                  + movingCountCore(threshold, rows, cols, row+1, col, visited)
                  + movingCountCore(threshold, rows, cols, row, col-1, visited)
                  + movingCountCore(threshold, rows, cols, row-1, col, visited);
    }
    return count;
}

int movingCount(int threshold, int rows, int cols)
{
    if(threshold < 0 || rows <= 0 || cols <= 0)
        return 0;
    bool** visited = new bool* [rows];
    for(int i = 0; i < rows; ++i)
    {
        visited[i] = new bool [cols];
    }
    for (int i = 0; i < rows; ++i)
    {
    	for (int j = 0; j < cols; ++j)
    	{
    		visited[i][j] = false;
		}
	}
    int count = movingCountCore(threshold, rows, cols, 0, 0, visited);
    for (int i = 0; i < rows; ++i)
    {
        delete[] visited[i];
    }
    delete [] visited;
    return count;
}

int main()
{
    cout << "Input m, n, k: " << endl;
    int m, n, k;
    cin >> m >> n >> k;
    cout << movingCount(k, m, n);
    return 0;
}
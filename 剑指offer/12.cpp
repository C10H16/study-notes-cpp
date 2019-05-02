#include <iostream>
#include <string>
using namespace std;

bool hasPathCore(const char* const* matrix, int rows, int cols, int row, int col, const char* str, int& pathLength, bool** visited)
{
    if (str[pathLength] == '\0')
        return true;
    bool result = false;
    if (row >= 0 && row < rows && col >= 0 && col < cols 
        && matrix[row][col] == str[pathLength]
        && !visited[row][col])
    {
        ++pathLength;
        visited[row][col] = true;
        
        result = hasPathCore(matrix, rows, cols, row, col-1, str, pathLength, visited)
            || hasPathCore(matrix, rows, cols, row-1, col, str,pathLength, visited)
            || hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited)
            || hasPathCore(matrix, rows, cols, row+1, col, str, pathLength, visited);
        if (!result)
        {
            --pathLength;
            visited[row][col] = false;
        }
    }
    return result;
}

bool hasPath( char** matrix, int rows, int cols, char* str)
{
    if (matrix == nullptr || rows < 1 || cols < 1 || str == nullptr)
        return false;
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
    int pathLength = 0;
    for(int row = 0; row < rows; ++row)
    {
        for(int col = 0; col < cols; ++col)
        {
            if (hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited))
            {
                return true;
            }
        }
    }
    delete[] visited;
    return false;
}


int main()
{
    int x, y;
    cin >> x >> y;
    char** matrix = new char* [x];
    for(int i = 0; i < x; ++i)
    {
        matrix[i] = new char [y];
    }
    for(int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < x; ++i)
    {
    	for (int j = 0; j < y; ++j)
    	{
    		cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
    int n;
    cin >> n;
    char* path = new char[n + 1];
    for(int i = 0; i < n; ++i)
    {
        cin >> path[i];
    }
    path[n] = '\0';
	cout << hasPath(matrix, x,y,path);
    for(int i = 0; i < x; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}

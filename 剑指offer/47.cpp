#include <iostream>
using namespace std;

int findMaxValue(int **values, int rows, int cols)
{
    int **dp = new int*[rows];
    for(int i = 0; i < rows; ++i)
    {
        dp[i] = new int[cols];
    }
    for(int i = 1; i < rows; ++i)
    {   
        for(int j = 1; j < cols; ++j)
        {
            dp[i][j] = 0;
        }
    }
    int sum = 0;
    for(int i = 0; i < rows; ++i)
    {
        sum += values[i][0];
        dp[i][0] = sum;
    }
    sum = values[0][0];
    for(int j = 1; j < cols; ++j)
    {
        sum += values[0][j];
        dp[0][j] = sum;
    }
    for(int i = 1; i < rows; ++i)
    {
        for(int j = 1; j < cols; ++j)
        {
            dp[i][j] = max(dp[i-1][j],dp[i][j-1])+values[i][j];
            //cout << dp[i][j] << " ";
        }
        //cout << endl;
    }
    return dp[rows-1][cols-1];
}

int findMaxValue_2(int **values, int rows, int cols)
{
    int *dp = new int[cols];
    int sum = 0;
    for(int i = 0; i < rows; ++i)
    {
        sum += values[i][0];
        dp[i] = sum;
    }
    for(int i = 1; i < rows; ++i)
    {
        dp[0]=values[i][0]+dp[0];
        for(int j = 1; j < cols; ++j)
        {
            dp[j] = max(dp[j-1],dp[j])+values[i][j];
            //cout << dp[i][j] << " ";
        }
        //cout << endl;
    }
    return dp[cols-1];
}

int main()
{
    int rows, cols;
    cin >> rows >> cols;
    int **values = new int*[rows];
    for(int i = 0; i < rows; ++i)
    {
        values[i] = new int[cols];
    }
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            cin >> values[i][j];
        }
    }
    cout << findMaxValue(values, rows, cols);
    cout << findMaxValue_2(values, rows, cols);
    return 0;
}
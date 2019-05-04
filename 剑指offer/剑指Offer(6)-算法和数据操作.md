# 算法和数据操作

## 递归和循环

与循环相比，递归的代码简介，容易实现，但是每一次递归调用都会占用内存空间，调用次数很多时会导致调用栈溢出，且需要时间。从效率上来说，循环的速度更快。另外，递归有很多的重复计算。

### 斐波那契数列

> 写一个函数，输入n，返回斐波那契数列的第 n 项。
>
> f(n) = 0 n = 0
>
> f(n) = 1 n = 1
>
> f(n) = f(n-1)+f(n-2) n > 1

```C++
// 递归
long long Fibonacci(unsigned int n)
{
    if (n==0)
        return 0;
    else if(n==1)
        return 1;
    else
        return Fibonacci(n-1)+Fibonacci(n-2);
}
// 递归方法的时间复杂度以 n 的指数方式递增。
```

```C++
// 循环 时间复杂度O(n)
#include <iostream>
using namespace std;
unsigned long long Fibonacci(unsigned int n)
{
	if (n == 0)
		return 0;
	else if(n==1)
		return 1;
	else 
	{
		unsigned long long num1 = 0;
		unsigned long long num2 = 1;
		unsigned long long re = num1 + num2;
		unsigned int i = 2;
		while(i<=n)
		{
			re = num1 + num2;
			num1 = num2;
			num2 = re;
			++i;
		}
		return re;
	}
		
} 
int main()
{
	//unsigned int n;
	//cin >> n;
	for(unsigned int n = 0; n < 10; ++n)
		cout << Fibonacci(n)<<endl;
	return 0;
}
```

#### 青蛙跳台阶问题（斐波那契数列的应用）

> 一只青蛙一次可以上一阶台阶，也可以上两阶台阶，求该青蛙上n阶台阶有多少种跳法。

当上一阶台阶时，只有一种跳法，即跳一阶台阶。

当上两阶台阶时，有两种跳法，一阶和两阶。

当上 n 阶台阶时，可以看作 n 的函数 f(n)，可以看出，f(n) = f(n-1) + f(n-2)，即跳 n-2 阶台阶的跳法加上跳 n-1 阶台阶的跳法，即斐波那契数列。

## 查找和排序

不同的排序算法适用的场合不同。

### 旋转数组的最小数字

> 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转，输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如{3，4，5，1，2}为数组{1，2，3，4，5}的一个旋转，该数组的最小值为1。

```C++
// v1
// 没有考虑有重复数字的情况。
// 使用递归实现。
#include <iostream>
using namespace std;
int findMin(int* num,int start, int end)
{
	int mid = (start + end)/2;
	if (mid == 0 || (mid > 0 && num[mid] < num[mid-1]))
		return num[mid];
	if (num[mid] > num[start])
		findMin(num, mid, end);
	else 
		findMin(num, start, mid);
}

int main()
{
	int n;
	cin >> n;
	int *num = new int[n];
	for(int i = 0; i < n; ++i)
	{
		cin >> num[i];
	}	
	cout << findMin(num, 0, n);
	delete[] num;
	return 0;
}
```

当数组为 {1，1，1，0，1} 或{1，0，1，1，1}等形式时，上面的方法则不能找出数组中的最小值。

```C++
// v2
// 迭代实现，若出现上述情况则只能顺序查找。
#include <iostream>
using namespace std;

int MinInOrder(int* num, int index1, int index2)
{
	int min = num[index1];
	for (int i = index1+1; i <= index2; ++i)
	{
		if (num[i] < min)
			min = num[i];
	}
	return min;
} 
int findMin(int *num, int length)
{
	if (num == nullptr || length <=0)
	{
		throw ("Invalid parameters");
	}
	int index1 = 0;
	int index2 = length -1;
	int indexMid = index1;
	while (num[index1]>=num[index2])
	{
		if (index2 - index1 == 1)
		{
			indexMid = index2;
			break;
		}
		indexMid = (index1 + index2)/2;
		if (num[index1]==num[index2]&&num[indexMid]==num[index1]) // 三个数字相等时，只能顺序查找 
		{
			return MinInOrder(num,index1,index2);
		}
		if (num[indexMid]>=num[index1])
		{
			index1 = indexMid;
		}
		else if(num[indexMid]<=num[index2])
		{
			index2 = indexMid;
		}
	}
	return num[indexMid];
}



int main()
{
	int n;
	cin >> n;
	int* num = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> num[i];
	}
	cout << findMin(num, n);
	delete[] num;
	return 0;
}
```

## 回溯法

回溯法适合由多个步骤组成的问题，每个步骤都有多个选项。当我们在某一步选择了其中一项时，就进入下一步，直到达到最终状态。如果最终状态不满足条件，则回退到上一步，选择别的选项。当这一步的所有选项都不能满足条件，则再次回退到上一步。如果所有选项都不满足，则该问题无解。

### 矩阵中的路径

> 设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进如该格子。

使用回溯法。由于其递归特性，可以将路径看作一个栈。同时，需要一个和字符矩阵同样大的矩阵，用来记录路径是否访问了该格子。

```C++
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
```

### 机器人的运动范围

> 地上有一个 m 行 n 列的方格。一个机器人从坐标（0，0）的格子开始移动，它每次可以向左、右、上、下移动一个，但不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进如方格（35，37），因为3+5+3+7 = 18。但它不能进如方格（35，38）问该机器人能够到达多少个格子。

设机器人从（0，0）开始移动，当机器人准备进如下一个格子时，检查该格子能否进入。如果能够进入，则继续检查能否进如该格子四周的格子。

```C++
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
```


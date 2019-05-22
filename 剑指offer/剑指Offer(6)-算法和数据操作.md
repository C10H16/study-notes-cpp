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

## 动态规划与贪婪算法

### 动态规划

如果要求一个问题的最优解，且该问题能够分解成若干个子问题，且子问题之间还有重叠的更小的子问题，则可以考虑使用动态规划。使用动态规划时，需要分析能否把大问题分解成小问题，每个小问题也要存在最优解。且如果把小问题的最优解组合起来能够得到整个问题的最优解，就可以使用动态规划。

### 贪婪算法

使用贪婪算法解决问题时，每一步都可以做出一个贪婪的选择。基于这个选择，我们确定能够得到最优解。使用贪婪算法时，需要用数学方式来证明贪婪选择是正确的。

###　剪绳子

> 一段长度为n的绳子，剪成m段（m,，n都是整数，且m>1，n>1）。每段绳子的长度记为k[0]，k[1]，...k[m]，求k[0]\*k[1]\*...\*k[m]的最大值。

#### 动态规划法

可以设`f(n)=max(f(i)*f(n-i))`

可以先得到f(2)、f(3)，再计算f(4)，f(5)，直到得到f(n)

当绳子长度为2时，只能剪成长度为1的两段，因此，f(2) = 1

当绳子长度为3时，可以剪成长度为1和2或1，1和1，f(3) = 2

#### 贪婪算法

因为当绳子长度大于3时，如4，分成2\*2时最优，5，分成2\*3时最优……因此，将绳子尽可能分成长度为3的绳子，而绳子长度剩下4时，则分成2*2的绳子。

```C++
#include <iostream>
#include <math.h>
using namespace std;
int maxProduct_1(int length) //动态规划
{
    if (length < 2)
    return 0;
    else if(length == 2)
    return 1;
    else if(length ==3)
    return 2;

    int *products = new int[length+1]; // 存储最优解
    products[0] = 0;
    products[1] = 1;
    products[2] = 2;
    products[3] = 3;

    int max = 0;
    for(int i = 4; i <= length; ++i)
    {
        max = 0;
        for(int j = 1; j <= i/2; ++j)
        {
            int product = products[j]*products[i-j];
            if (product > max)
            {
                max = product;
            }
        }
        products[i] = max;
    }
    max = products[length];
    delete[] products;
    return max;
}

int maxProduct_2(int length) // 贪婪算法
{
    if (length < 2)
        return 0;
    else if(length == 2)
        return 1;
    else if(length ==3)
        return 2;

    int timesOf3 = length/3;
    if (length - 3*timesOf3 == 1) // 如果会剩下长度为4的绳子，则不能分成1*3
    {
        timesOf3 -= 1;
    }
    int timesOf2 = (length - 3*timesOf3)/2;
    return (int) (pow(3,timesOf3))*(int)(pow(2,timesOf2));
}
int main()
{
    int length;
    cin >> length;
    cout << "method_1: " << maxProduct_1(length) << endl;
    cout << "method_2: " << maxProduct_2(length) << endl;
    return 0; 
}
```

## 位运算

| | | | | |
|--|--|--|--|--|
| 与（&）| 0&0=0 | 1&0=0 | 0&1=0 | 1&1=1|
|或（\|）| 0\|0=0 | 1\|0=1 | 0\|1 =1 | 1\|1=1|
|异或（^）| 0^0=0| 1^0=1 | 0^1=1 | 1^1=0|

左移（m<<n）将m向左移n位，最左边的n位将被丢弃，右边补0

右移（m>>n）将m向右移n位，最右边的n位将被丢弃，如果数字是无符号数，左边补0；如果是有符号数，则用符号位填补最左边的n位。

### 二进制中1的个数

> 请实现一个函数，输入一个整数，输出该二进制表示中1的个数。

如果将数字右移，当数字为负数时，最高位会补1，使程序陷入死循环。可以保持数字不动，将数字与1进行按位与，如果结果为1，则数字最后一位为1。接着将1左移，继续与数字进行按位与，如果结果为1则该数字的倒数第二位为1。这种方法循环的次数取决于整数二进制的位数。

```C++
int NumberOf1(int n)
{
    int count = 0;
    unsigned flag = 1;
    while (flag)
    {
        if(n&flag)
            count ++;
        flag = flag << 1;
    }
    return count;
}
```

另一种方法是把整数n减一，再与减一前的值按位与。如 :

1011-1 = 1010, 1010&1011=1010

1010-1 = 1001, 1001&1010=1000

1000-1 = 0000, 0000&1000=0000

可以发现，当每进行一轮这样的操作后，都可以消去该整数从右往左数的第一个1。可以通过这个方法统计该整数中1的个数。

```C++
#include <iostream>
using namespace std;
int numberOf1(int n)
{
    int m = 0;
    int count = 0;
    while(n)
    {
        ++count;
        m = n-1;
        n = m&n;
    }
    return count;
}
int main()
{
    int n;
    cin >> n;
    cout << numberOf1(n) << endl;
    return 0;
}
```


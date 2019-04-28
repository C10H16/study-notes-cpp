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


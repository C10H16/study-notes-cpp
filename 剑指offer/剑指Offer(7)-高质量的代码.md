# 剑指Offer

## 高质量的代码

从三个方面确保代码的完整性：

- 功能测试
- 边界测试
- 负面测试

三种错误的处理方法：

- 函数使用返回值来告知调用者是否出错
- 使用全局变量传递参数
- 抛出异常

### 数值的整数次方

> 实现函数 double Power(double base, int exponent)，求 base 的 exponent 次方。不得使用函数库，同时不需要考虑大数问题。

需要注意 exponent为0或复数的情况。

```C++
#include <iostream>
using namespace std;
bool InvalidInput = false;
double Power(double base, int exponent)
{
    double result = 1.0;
    if (base > 0 || base < 0)
    {
        bool negative = false;
        int absExponent = exponent;
        if (exponent==0)
        {
            return 1.0;
        }
        else if(exponent < 0)
        {
            negative = true;
            absExponent = -exponent;
        }
        for (int i = 0; i < absExponent; ++i)
        {
            result *= base;
        }
        if (negative)
        {
            result = 1.0/result;
        }
        return result;

    }
    else
    {
        if (exponent < 0)
        {
            InvalidInput = true;
        }
        return 0.0;
    }
}
int main()
{
    double base;
    int exponent;
    cin >> base >> exponent;
    double result = 0.0;
    result = Power(base, exponent);
    if (!InvalidInput)
    {
        cout << result << endl;
    }
    else
        cout << "Invalid input!" << endl;
    return 0;
}
```

### 打印从1到最大的n位数

> 输入数字n，按顺序打印出从1到最大的n位十进制数。比如输入3，则输出1到999。

要考虑n的大小，如果n过大，则使用int或long long 会溢出。

使用字符串模拟加法

```C++
#include <iostream>
#include <cstring>
using namespace std;
bool Increment(char* number)
{
    bool isOverflow = false;
    int nTakeOver = 0;
    int nLength = strlen(number);
    for(int i = nLength-1; i >=0; --i)
    {
        int nSum = number[i]-'0'+nTakeOver;
        if(i==nLength-1)
        	nSum++;
        if (nSum>=10)
        {
            if (i==0)
                isOverflow = true; // 检查是否溢出
            else
            {
                nSum-=10;
                nTakeOver=1;
                number[i]='0'+nSum;
            }
        }
        else
        {
            number[i]='0'+nSum;
            break;
        }
    }
    return isOverflow;
}

void PrintNumber(char* number)
{
    bool isBeginning0 = true;
    int nLength = strlen(number);
    for(int i = 0; i < nLength; ++i)
    {
        if (isBeginning0 && number[i]!='0')
            isBeginning0 = false;
        if (!isBeginning0)
        {
            cout << number[i];
        }
    }
    cout << endl;
}

void Print1ToMaxOfDigits(int n)
{
    if (n<=0)
    	return;
    char *number = new char[n+1];
    for(int i = 0; i < n; ++i)
    {
        number[i]='0';
    }
    number[n] = '\0';
    while(!Increment(number))
    {
        PrintNumber(number);
    }
    delete[] number;
}


int main()
{
    int n;
    cin >> n;
    Print1ToMaxOfDigits(n);
    return 0;
}
```

另一种方法 输出从1到n位最大数实际上就是n个0-9的全排列。

```C++
#include <iostream>
using namespace std;

void printNum(int *num,int n)
{
    int i = n-1;
    while (num[i]==0)
    {
        --i;
    }
    for(i; i >= 0; --i)
    {
        cout << num[i];
    }
    cout << '\t';
}

void Print1ToMaxOfNDigitsCore(int index, int* num, int n)
{
    if(index<0)
    {
        printNum(num,n);
        return;
    }
    for(int i = 0; i < 10; ++i)
    {
        num[index] = i;
        Print1ToMaxOfNDigitsCore(index-1, num, n);
    }
}

void print1ToMaxOfNDigits(int n)
{
    int *num = new int[n];
    for(int i = 0; i < n; ++i)
    {
        num[i] = 0;
    }
    Print1ToMaxOfNDigitsCore(n-1,num,n);
    delete[] num;
}

int main()
{
    int n;
    cin >> n;
    print1ToMaxOfNDigits(n);
    return 0;
}
```


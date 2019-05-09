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

### 删除链表的节点

#### 题目一：在O(1)时间内删除链表节点

> 给定单向链表的头指针和一个节点指针，定义一个函数在O(1)时间内删除该节点。链表节点与函数的定义如下：

```C++
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};
void DeleteNode(List** pListHead, ListNode* pToBeDeleted);
```

单向链表中删除节点需要将被删除节点的前一节点连接到被删除节点的下一节点，这就需要从头开始寻找被删除节点的前以节点，这样的实现复杂度为O(n)。可以将被删除节点的下一节点的值赋给被删除节点，然后删除被删除节点的下一节点，这样就可以在O(1)内完成删除。但是当要删除的节点为尾节点时，只能从头节点开始依次寻找。

总平均复杂度为 [(n-1)*O(1)+O(n)]/n = O(1)

```C++
#include <iostream>
using namespace std;
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

void AddToTail(ListNode** pHead, int value)
{
    ListNode* pNew = new ListNode();
    pNew->m_nValue = value;
    pNew->m_pNext = nullptr;
    
    if (*pHead == nullptr)
    {
        *pHead = pNew;
    }
    else
    {
        ListNode* pNode = *pHead;
        while(pNode->m_pNext != nullptr)
        {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = pNew;
    }
}

void PrintList(ListNode* pHead)
{
    ListNode* p = pHead;
    while (p)
    {
        cout << p->m_nValue << " ";
        p = p->m_pNext;
    }
    cout << endl;
}

void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
    if (!pToBeDeleted||!pListHead)
    {
        return;
    }
    if (pToBeDeleted->m_pNext != nullptr) // 如果不是尾节点
    {
        ListNode* pToBeDeletedNext = pToBeDeleted->m_pNext;
        pToBeDeleted->m_nValue = pToBeDeleted->m_pNext->m_nValue;
        pToBeDeleted->m_pNext = pToBeDeleted->m_pNext->m_pNext;

        delete pToBeDeletedNext;
        return;
    }
    else if (pToBeDeleted == *pListHead) // 要删除的节点是尾节点又是头节点（即链表只有一个节点）
    {
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        *pListHead = nullptr;
        return;
    }
    else
    {
        ListNode* pNode = *pListHead;
        while (pNode->m_pNext != pToBeDeleted)
        {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = nullptr;
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        return;
    }
    
}

int main()
{
	int n, temp;
    cin >> n;
    while (n<3)
    {
        cout << "n must bigger than 3";
        cin >> n;
    }
	ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
    ListNode* d1, *d2, *d3,*ptemp;
    
	for(int i = 0; i < n; ++i)
	{
		cin >> temp;
		AddToTail(p,temp);
	}
    ptemp = pHead;
    for (int i = 0; i < n; ++i)
    {
        if (i == 0)
            d3 = ptemp;
        if (i == n/2)
            d1 = ptemp;
        if (i == n-1)
            d2 = ptemp;
        ptemp = ptemp->m_pNext;
    }
    // 删除分别删除链表的中间、头、尾节点。
    PrintList(pHead);
    DeleteNode(p,d1);
	PrintList(pHead);
    DeleteNode(p,d2);
    PrintList(pHead);
    DeleteNode(p,d3);
    PrintList(pHead);
    d1 = nullptr;
    d2 = nullptr;
    d3 = nullptr;
    ptemp = pHead;
    p = nullptr;
    while (ptemp)
    {
        ptemp = ptemp->m_pNext;
        delete pHead;
        pHead = ptemp;
    }

	return 0;	
}
```

#### 题目二：删除链表中的重复节点

> 在一个排序链表中，删除重复的节点。

首先要确定函数的参数。因为头节点可能和后面的节点重复而被删除，因此传入的参数应该为指向头节点指针的指针，而不是头节点的指针。

接下来从头开始遍历整个链表，如果当前节点的值与下一个节点的值相同，则它们为重复的节点，可以删掉。这时需要将当前节点的前一个节点和第一个大于当前节点的节点相连。

```C++
#include <iostream>
using namespace std;
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

void AddToTail(ListNode** pHead, int value)
{
    ListNode* pNew = new ListNode();
    pNew->m_nValue = value;
    pNew->m_pNext = nullptr;
    
    if (*pHead == nullptr)
    {
        *pHead = pNew;
    }
    else
    {
        ListNode* pNode = *pHead;
        while(pNode->m_pNext != nullptr)
        {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = pNew;
    }
}

void PrintList(ListNode* pHead)
{
    ListNode* p = pHead;
    while (p)
    {
        cout << p->m_nValue << " ";
        p = p->m_pNext;
    }
    cout << endl;
}

void deleteDuplication(ListNode** pHead)
{
    if(pHead == nullptr || *pHead == nullptr)
        return;
    ListNode* pPreNode = nullptr;
    ListNode* pNode = *pHead;
    while (pNode != nullptr)
    {
        ListNode *pNext = pNode->m_pNext;
        bool needDelete = false;
        if(pNext != nullptr && pNext->m_nValue == pNode->m_nValue)
            needDelete = true;
        if(!needDelete)
        {
            pPreNode = pNode;
            pNode = pNode->m_pNext;
        }
        else
        {
            int value = pNode->m_nValue;
            ListNode* pToBeDel = pNode;
            while(pToBeDel != nullptr && pToBeDel->m_nValue == value)
            {
                pNext = pToBeDel->m_pNext;

                delete pToBeDel;
                pToBeDel = nullptr;
                pToBeDel = pNext;
            }
            if (pPreNode == nullptr)
            {
                *pHead = pNext;
            }
            else
            {
                pPreNode->m_pNext = pNext;
            }
            pNode = pNext;
        }
        
    }
}

int main()
{
	int n, temp;
    cin >> n;
	ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
    ListNode* ptemp;
	for(int i = 0; i < n; ++i)
	{
		cin >> temp;
		AddToTail(p,temp);
	}
    PrintList(pHead);
    deleteDuplication(p);
    PrintList(pHead);
    ptemp = pHead;
    p = nullptr;
    while (ptemp)
    {
        ptemp = ptemp->m_pNext;
        delete pHead;
        pHead = ptemp;
    }
	return 0;	
}
```


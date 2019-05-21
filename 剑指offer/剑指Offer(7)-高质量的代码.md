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

### 正则表达式匹配

> 实现一个用函数来匹配包含 "." 和 "\*" 的正则表达式。模式中的字符 "." 表示任意一个字符，而 "\*"表示它前面的字符可以出现任意次（含0次），在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串 "aaa" 与模式 "a.a" 和 "ab\*ac\*a" 匹配，但与 "aa.a" 和 "ab\*a" 均不匹配。

字符串当前字符与模式串中当前字符相等或模式串中字符为 "." 时，可直接比较下一位。

当模式串当前字符的下一字符为 "*" 时，有三种可能需要考虑，一种是模式串与字符串的当前字符相等，且字符串的当前字符连续出现n次。第二种是模式串与字符串当前字符相等，而字符串的下一字符与当前字符不等。第三种是忽略模式串的当前字符（即出现0次）

要注意字符串"abcde" 与模式串 "ab\*c\*...e"是匹配的，因为可以忽略"b\*"和"c\*",而"..."匹配字符串中的"bcd"。

```C++
#include <iostream>
using namespace std;

bool matchCore(char* str, char* pattern)
{
    if (*str == '\0' && *pattern == '\0')
        return true;
    if (*str != '\0' && *pattern == '\0')
        return false;
    if (*(pattern + 1) == '*')
    {
        if (*pattern == *str || (*pattern == '.' && *str != '\0'))
        {
            return matchCore(str+1, pattern+2) // move to the next state
                || matchCore(str+1, pattern) // stay on current state
                || matchCore(str, pattern+2); // ignore a'*'
        }
        else
        {
            return matchCore(str, pattern + 2); // ignore a '*'
        }
    }
    if (*str == *pattern || (*pattern == '.' && *str != '\0'))
        return matchCore(str + 1, pattern+1);
    return false;
}

bool match(char* str, char* pattern)
{
    if (str == nullptr || pattern == nullptr)
        return false;
    matchCore(str, pattern);
}

int main()
{
    int n;
    cin >> n;
    char* str = new char[n+1];
    for(int i = 0; i < n; ++i)
    {
        cin >> str[i];
    }
    str[n] = '\0';
    cin >> n;
    char* pattern = new char[n+1];
    for(int i = 0; i < n; ++i)
    {
        cin >> pattern[i];
    }
    pattern[n] = '\0';
    cout << match(str, pattern);
    return 0;
}
```

### 表示数值的字符串

> 实现一个函数，用来判断字符串是否表示数值（包括整数和小数，例如，字符串“+100”、“5e2”、“-123”、“3.1416”、“-1E-16”都表示数值，但“12e”、“1a3.14”、“1.2.3”、“+-5”以及“12e+5.4”都不是。

表示数值的字符串遵循模式A[.\[B\]][e|EC]或者.B[e|EC]，其中，A为数值的整数部分，B为紧跟着小数点为数值的小数部分，C紧跟着‘e’或‘E’，为数值的指数部分。在小数里可能没有数值的整数部分，因此，A部分不是必须的。如果一个数没有整数部分，则它的小数部分不能为空。A和C都是可以以‘+’或‘-’开头的0-9组成的数位串，而B中只有0-9。

在扫描时，从头开始，扫描A部分，如果遇到小数点，则开始扫描B部分，如果遇到‘e’或‘E’，则开始扫描C部分。

```C++
#include <iostream>
#include <string>
using namespace std;
bool scanUnsignedInteger(const char** str)
{
    const char* before = *str;
    while (**str != '\0' && **str >= '0' && **str <= '9')
    {
        ++(*str);
    }
    return *str>before;
}
bool scanInteger(const char** str)
{
    if (**str=='+'||**str=='-')
        ++(*str);
    return scanUnsignedInteger(str);
}
bool isNumeric(const char* str)
{
    if (str==nullptr)
    {
        return false;
    }
    bool numeric = scanInteger(&str);
    // 如果出现'.'，接下来是数字的小数部分
    if (*str == '.')
    {
        ++str;
        // 下面代码用||的原因：
        // 1.小数可以没有整数部分，如 .123 等于 0.123
        // 2.小数点后面可能没有数字，如 233. 等于 233.0
        // 3.小数点后面可能有数字，233.666
        numeric = scanUnsignedInteger(&str) || numeric;
    }

    // 如果出现 'e' 或 'E'，则接下来是数字的整数部分
    if (*str == 'e' || *str == 'E')
    {
        ++str;
        // 下面代码使用&&的原因：
        // 1.当 e 或 E 前面没有数字时，整个字符串不能表示数字，如.e1，e1
        // 2.当 e 或 E 后面没有整数时，整个字符串不能表示数字，如12e，12e+5.4
        numeric = numeric && scanInteger(&str);
    }
    return numeric && *str == '\0';
}

int main()
{
    string test;
    cin >> test;
    cout << isNumeric(&test[0]) << endl;
    return 0;
}
```

### 调整数组顺序使奇数位于偶数前面

> 输入一个整数数组，实现一个函数来调整改数组中数字的顺序，使得所有奇数位于数组的前半部分，偶数位于数组的后半部分。

使用两个指针，一个从前往后扫描数组，一个从后往前扫描，当前面的指针指向的元素为偶数，且后面的指针指向的元素为奇数时，交换两个元素的值，直到两个指针重合，结束循环。

```C++
#include <iostream>
using namespace std;

void ReorderOddEven(int *nums, unsigned length)
{
    if (nums == nullptr || length == 0)
        return;
    int* p_left = nums;
    int* p_right = nums+length-1;
    int temp;
    while (p_left < p_right)
    {
        while (p_left < p_right && *p_left%2!=0)
        {
            ++p_left;
        }
        while (p_left < p_right && *p_right%2==0)
        {
            --p_right;
        }
        if (p_left < p_right)
        {
            temp = *p_left;
            *p_left = *p_right;
            *p_right = temp;
        }
    }
}

int main()
{
    int n = 0;
    cin >> n;
    int *nums = new int[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    ReorderOddEven(nums, n);
    for(int i = 0; i < n; ++i)
    {
        cout << nums[i] << " ";
    }
    return 0;
}

//修改版，可扩展性更强
bool isEven(int n)
{
    return n%2!= 0 ? 1:0;
}

void ReorderOddEven(int *nums, unsigned length)
{
    if (nums == nullptr || length == 0)
        return;
    int* p_left = nums;
    int* p_right = nums+length-1;
    int temp;
    while (p_left < p_right)
    {
        while (p_left < p_right && isEven(*p_left))
        {
            ++p_left;
        }
        while (p_left < p_right && !isEven(*p_right))
        {
            --p_right;
        }
        if (p_left < p_right)
        {
            temp = *p_left;
            *p_left = *p_right;
            *p_right = temp;
        }
    }
}
```

## 代码的鲁棒性

防御性编程：预见在什么地方可能会出现问题，并为这些可能的问题制定处理方式。例如，试图打开文件时，发现文件不存在，可以提示用户检查文件名和路径。当服务器连接不上时，试图连接备用服务器等。

### 链表中倒数第k个节点

> 输入一个链表，输出该链表中倒数第k个节点。为了复合大多数人的习惯，本题从1开始计数。即链表的尾节点是倒数第一个节点。节点定义如下：

```C++
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
}
```

在已知链表长度的情况下，可以计算出链表中倒数第k个节点是链表的第几个节点，但是这样就需要扫描两遍链表，第一遍找出链表的长度，第二遍找到该节点。

另一种方法是，使用两个指针，第一个指针从头节点开始往后移动，当移动到第k个时，第二个指针从头节点和第一个指针一起移动。当第一个指针移动到链表末尾时，第二个指针指向的节点就是链表的倒数第k个节点。

```C++
#include <iostream>
using namespace std;
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
    if (pListHead == nullptr || k == 0)
    {
        return nullptr;
    }
    ListNode* pAhead = pListHead;
    ListNode* pBehind = nullptr;
    for (int i = 0; i < k-1; ++i)
    {
        if (pAhead->m_pNext != nullptr)
        {
            pAhead = pAhead->m_pNext;
        }
        else
        {
            return nullptr;
        }
    }
    pBehind = pListHead;
    while (pAhead->m_pNext != nullptr)
    {
        pAhead = pAhead->m_pNext;
        pBehind = pBehind->m_pNext;
    }
    return pBehind;
}

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

int main()
{
    int n, k;
    cin >> n >> k;
    ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
    int temp;
    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        AddToTail(p, temp);
    }
    ListNode* re = FindKthToTail(pHead, k);
    if (re)
        cout << re->m_nValue << endl;
    else
    {
        cout << "Error";
    }
    return 0;
}
```

### 链表中环的入口节点

> 题目：如果一个链表中包含环，如果找出环的入口节点。

可以使用一快一慢两个指针，当快指针和慢指针重合时，说明链表中有环。当两个节点重合时，这个节点一定在环中。从这个节点出发，边移动边计数，再次回到这个节点时，就可以得到环中节点的数目。

同样的，使用两个指针，假设环中有n个节点，使快指针先向前走n个节点，然后两个指针同时移动，当两个指针重合的节点即是入口节点。

```C++
#include <iostream>
using namespace std;
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* MeetingNode(ListNode* pHead)
{
    if (pHead == nullptr)
    {
        return nullptr;
    }
    ListNode* pSlow = pHead->m_pNext;
    if (pSlow == nullptr)
        return nullptr;
    ListNode* pFast = pSlow->m_pNext;
    while (pFast != nullptr && pSlow != nullptr)
    {
        if (pFast == pSlow)
        {
            return pFast;
        }
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;
        if (pFast != nullptr)
        {
            pFast = pFast->m_pNext;
        }
    }
    return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    ListNode* meetingNode = MeetingNode(pHead);
    if (meetingNode == nullptr)
    {
        return nullptr;
    }
    // 得到环中节点数目
    int nodesInLoop = 1;
    ListNode* pNode1 = meetingNode;
    while(pNode1->m_pNext != meetingNode)
    {
        pNode1 = pNode1->m_pNext;
        ++nodesInLoop;
    }
    // 先移动Node1，次数与环中节点数目相同
    pNode1 = pHead;
    for(int i = 0; i < nodesInLoop; ++i)
    {
        pNode1 = pNode1->m_pNext;
    }
    // 再移动Node1和Node2
    ListNode* pNode2 = pHead;
    while(pNode1 != pNode2)
    {
        pNode1 = pNode1->m_pNext;
        pNode2 = pNode2->m_pNext;
    }
    return pNode1;
}

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

int main()
{
    int n, k;
    cin >> n >> k;
    ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
    int temp;
    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        AddToTail(p, temp);
    }
    // 构造环
    ListNode* start = nullptr;
    ListNode* tail = pHead;
    for (int i = 1; i < n; ++i)
    {
        if (i==k)
            start = tail;
        tail = tail->m_pNext;
    }
    if (k==n)
        tail->m_pNext = tail;
    else
        tail->m_pNext = start;
    
    ListNode* re = EntryNodeOfLoop(pHead);
    if (re)
    {
        cout << re->m_nValue << endl;
    }
    else
    {
        cout << "Not found" << endl;
    }
    
    return 0;
}
```

### 反转列表

>定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。链表节点定义如下：

```C++
struct ListNode
{
    int m_nValue;
    int m_pNext;
}
```

直接对链表进行反转，即将当前节点的的Next指针指向前一个节点。同时，还需要记录指针原本指向的节点，防止链表断裂。因此，需要三个指针，分别指向前一节点、当前节点和后一节点。

```C++
#include <iostream>
using namespace std;
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* ReverseList(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;
    ListNode* pReversedHead = nullptr;
    ListNode* pNode = pHead;
    ListNode* pPrev = nullptr;
    ListNode* pNext = nullptr;
    while (pNode != nullptr)
    {
        pNext = pNode->m_pNext;
        
        if (pNext == nullptr)
        {
            pReversedHead = pNode;
        }
        pNode->m_pNext = pPrev;

        pPrev = pNode;
        pNode = pNext;
    }
    return pReversedHead;

}

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

int main()
{
    int n;
    cin >> n;
    ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
    int temp;
    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        AddToTail(p, temp);
    }
    
    ListNode* re = ReverseList(pHead);
    pHead = re;
    while (re)
    {
        cout << re->m_nValue << " ";
        re = re->m_pNext;
    }
    
    return 0;
}
```

#### 补充 头插法

在创建列表时，将新节点插入头部，输出时为反向。如， 插入顺序为1->2->3->4->5，输出时为5->4->3->2->1。也可以使用这种方法反转链表。

```C++
void AddToHead(ListNode** pHead, int value)
{
    ListNode* pNew = new ListNode();
    pNew->m_nValue = value;
    pNew->m_pNext = nullptr;
    ListNode* pNode = *pHead;
    if (pNode != nullptr)
        pNew->m_pNext = pNode;
    *pHead = pNew;
}
```

#### 补充 尾插法

将新节点插入链表的末尾，输出的顺序与插入时的顺序相同

```C++
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
```

### 合并两个排序的链表

> 输入两个递增排序的链表，合并这两个链表并使链表中的节点仍然是递增排序的。

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

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr)
        return pHead2;
    else if (pHead2 == nullptr)
        return pHead1;
    
    ListNode* pMergeHead = nullptr;
    if (pHead1->m_nValue < pHead2->m_nValue)
    {
        pMergeHead = pHead1;
        pMergeHead->m_pNext = Merge(pHead1->m_pNext, pHead2);
    }
    else
    {
        pMergeHead = pHead2;
        pMergeHead->m_pNext = Merge(pHead1, pHead2->m_pNext);
    }
    return pMergeHead;
    
}

int main()
{
    int n1,n2;
    cin >> n1;
    ListNode* pHead1 = nullptr;
	ListNode** p1;
	p1 = &pHead1;
    int temp;
    for (int i = 0; i < n1; ++i)
    {
        cin >> temp;
        AddToTail(p1, temp);
    }
    cin >> n2;
    ListNode* pHead2 = nullptr;
    ListNode** p2;
    p2 = &pHead2;
    for (int i = 0; i < n2; ++i)
    {
        cin >> temp;
        AddToTail(p2, temp);
    }
    ListNode* pMerge = Merge(pHead1, pHead2);
    ListNode* p=pMerge;
    while (p)
    {
        cout << p->m_nValue << " ";
        p = p->m_pNext;
    }
    return 0;
}
```

### 树的子结构

> 输入两棵二叉树A和B，判断B是不是A的子结构。二叉树节点的定义如下：

```C++
struct BinaryTreeNode
    double m_dbValue;
    BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
```

 ```C++
#include <iostream>
#include <queue>
using namespace std;
struct BinaryTreeNode
{
	double m_dbValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

inline bool equal(double n1, double n2)
{
    return (n1-n2 < 0.0000001 && n1-n2 > -0.0000001);
}

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    if (pRoot2 == nullptr)
    {
        return true;
    }
    if (pRoot1 == nullptr)
    {
        return false;
    }
    if (!(equal(pRoot1->m_dbValue, pRoot2->m_dbValue)))
    {
        return false;
    }
    return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft)&&
           DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

// 查找树A中与树B根节点相等的节点
bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    bool result = false;
    if (pRoot1 != nullptr && pRoot2 != nullptr)
    {
        if(equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
        {
            result = DoesTree1HaveTree2(pRoot1, pRoot2);
        }
        if(!result)
        {
            result = HasSubtree(pRoot1->m_pLeft, pRoot2);
        }
        if(!result)
        {
            result = HasSubtree(pRoot1->m_pRight, pRoot2);
        }
    }
    return result;
}

void addLeftCh(BinaryTreeNode* parent,int left) // 添加左孩子 
{
	parent->m_pLeft = new BinaryTreeNode;
	parent->m_pLeft->m_dbValue = left;
	parent->m_pLeft->m_pLeft = nullptr;
	parent->m_pLeft->m_pRight = nullptr;
}

void addRightCh(BinaryTreeNode* parent,int right) // 添加右孩子 
{
	parent->m_pRight = new BinaryTreeNode;
	parent->m_pRight->m_dbValue = right;
	parent->m_pRight->m_pLeft = nullptr;
	parent->m_pRight->m_pRight = nullptr;
}

void printTree (BinaryTreeNode* root) // 打印树 
{
	queue<BinaryTreeNode*> node;
	cout << root->m_dbValue << " ";
	node.push(root->m_pLeft);
	node.push(root->m_pRight);
	while(!node.empty())
	{
		if (node.front() != nullptr)
		{
			cout << node.front()->m_dbValue << " ";
			node.push(node.front()->m_pLeft);
			node.push(node.front()->m_pRight);
			node.pop();
		}
		else
		{
			cout << "X ";
			node.pop();
		}
	}
}

int main()
{
	BinaryTreeNode* head1 = new BinaryTreeNode;
	head1->m_dbValue = 0.0;
	head1->m_pLeft = nullptr;
	head1->m_pRight = nullptr;
	queue<BinaryTreeNode*> temp;
	temp.push(head1);
	int n1, n2;
	cin >> n1;
	int* val1 = new int[n1];
	int i = 0;
	for(i = 0; i < n1; ++i)
	{
		cin >> val1[i];	
	}
	head1->m_dbValue = val1[0];
	BinaryTreeNode* pNode;
	i = 1;
	while(i < n1 && (!temp.empty())) // 构造树 
	{
		pNode = temp.front();
		if (val1[i]!=0)
		{
			addLeftCh(pNode,val1[i]);
			temp.push(pNode->m_pLeft);
		}
		if (val1[i+1]!=0)
		{
			addRightCh(pNode,val1[i+1]);
			temp.push(pNode->m_pRight);
		}
		temp.pop();
		i+=2;
	}

    while(!temp.empty())
    {
        temp.pop();
    }
    BinaryTreeNode* head2 = new BinaryTreeNode;
	head2->m_dbValue = 0.0;
	head2->m_pLeft = nullptr;
	head2->m_pRight = nullptr;
    cin >> n2;
	int* val2 = new int[n2];
	for(i = 0; i < n2; ++i)
	{
		cin >> val2[i];	
	}
	head2->m_dbValue = val2[0];
    temp.push(head2);
	i = 1;
	while(i < n2 && (!temp.empty())) // 构造树 
	{
		pNode = temp.front();
		if (val2[i]!=0)
		{
			addLeftCh(pNode,val2[i]);
			temp.push(pNode->m_pLeft);
		}
		if (val2[i+1]!=0)
		{
			addRightCh(pNode,val2[i+1]);
			temp.push(pNode->m_pRight);
		}
		temp.pop();
		i+=2;
	}
	printTree(head1);
    cout << endl;
    printTree(head2);
    cout << endl;
    cout << HasSubtree(head1, head2);

	return 0;
}
 ```


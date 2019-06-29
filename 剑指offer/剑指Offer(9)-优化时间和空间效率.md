# 剑指Offer

## 优化时间和空间效率

### 时间效率

#### 数组中出现次数超过一半的数字

> 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。

##### 解法一：基于快速排序的时间复杂度为O(n)的算法

数组中次数超过一半，则说明这个数字为数组的中位数。随机选取一个数，调整数组的顺序，使比它小的数都位于数组的作边，比它大的数字位于数组的右边，若调整后这个数的位置为n/2，则这个数字就是数组的中位数，如果这个数的位置小于n/2，则中位数位于这个数的右半部分。可以利用递归实现。找到中位数之后，需要检查该数出现的次数是否超过了数组的一半。这种方法会更改数组的顺序。

##### 解法二：根据数组特点找出时间复杂度为O(n)的算法

在遍历数组时，可以保存两个值，数组中的一个数字和数字的次数。如果下一个数字和当前数字相同，则次数加一，否则次数减一。如果次数为0，则需要保存下一个数字。因为要找的数字出现的次数比其他所有数字出现的次数都要多，所以要找的数字肯定是最后一次把次数设为1时对应的数字。

```C++
#include <iostream>
using namespace std;

bool g_bInputInvalid = false;

bool CheckInvalidArray(int* numbers, int length) // 检查输入是否有效
{
    if(numbers == nullptr || length <= 0)
        g_bInputInvalid = true;
    return g_bInputInvalid;
}

bool CheckMoreThanHalf(int* numbers, int length, int number) // 检查该数字是否超过一半
{
    int times = 0;
    for(int i = 0; i < length; ++i)
    {
        if (numbers[i] == number)
        {
            times++;
        }
    }
    bool isMoreThanHalf = true;
    if(times * 2 <= length)
    {
        g_bInputInvalid = true;
        isMoreThanHalf = false;
    }
    return isMoreThanHalf;
}

int MoreThanHalfNum(int* numbers, int length)
{
    if(CheckInvalidArray(numbers, length))
        return 0;
    int result = numbers[0];
    int times = 1;
    for(int i = 1; i < length; ++i)
    {
        if (times == 0)
        {
            result = numbers[i];
            times = 1;
        }
        else if(numbers[i] == result)
            times ++;
        else
            times --;
    }
    if (!CheckMoreThanHalf(numbers, length, result))
        result = 0;
    return result;
}

int main()
{
    int n;
    cin >> n;
    int* nums = new int[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    cout << MoreThanHalfNum(nums, n);
    return 0;
}
```

#### 最小的k个数

> 输入n个整数，找出其中最小的k个数。

##### 解法一：时间复杂度O(n) 的算法，需要修改数组

同样基于快排，随机选取数字，将小于该数字的放到数组作边，大于该数字的放到数组右边，如果调整后该数字的位置为k，则数组作边k个数字就是最小的k个数字。

##### 解法二：时间复杂度O(nlogk)，适合处理海量数据

建立一个包含k个节点的最大堆，扫描数组，如果当前数字小于堆顶，则将当前数字作为堆顶，并调整堆。最终堆中的数字就是最小的k个数字。 可以在O(1)时间内找到堆中的最大值，但是需要O(logk)的时间来完成删除及插入的操作。

使用STL中的 set和 multiset实现（基于红黑树）

```C++
typedef multiset<int, greater<int> > intSet;
typedef multiset<int, greater<int> > ::iterator setIterator;

void GetLeastNumbers(const vector<int>& data, intSet& leastNumbers, int k)
{
    leastNumbers.clear();

    if (k < 1 || data.size() < k)
        return;
    vector<int>::const_iterator iter = data.begin();
    for (; iter != data.end(); ++iter)
    {
        if((leastNumbers.size())<k)
            leastNumbers.insert(*iter);
        else
        {
            setIterator iterGreatest = leastNumbers.begin();
            if(*iter < * leastNumbers.begin()))
            {
                leastNumbers.erase(iterGreatest);
                leastNumbers.insert(*iter);
            }
        }
    }
}
```

#### 数据流中的中位数

> 如何得到一个数据流中的中位数？

数据是从一个数据流中读出来的，因此数据的数目随着时间的变化而增加。可以使用数组，基于快排的思想，查找中位数，也可以使用其他数据结构，每次插入新元素之后进行调整。

| 数据结构       | 插入的时间复杂度     | 得到中位数的时间复杂度 |
| -------------- | -------------------- | ---------------------- |
| 没有排序的数组 | O(1)                 | O(n)                   |
| 排序的数组     | O(n)                 | O(1)                   |
| 排序的链表     | O(n)                 | O(1)                   |
| 二叉搜索树     | 平均O(logn) 最差O(n) | 平均O(logn) 最差O(n)   |
| AVL树          | O(logn)              | O(1)                   |
| 最大堆最小堆   | O(logn)              | O(1)                   |

使用最大堆和最小堆，要保证数据平均分配到两个堆中。可以将偶数个数据插入最小堆，奇数个数据插入最大堆。同时，需要保证最大堆中所有数据都要小于最小堆中的数据。如果一个要插入最小堆中的数据比最大堆中的一些数字小，则先将这个数字插入最大堆，取出原来最大堆的堆顶插入最小堆。以保证最小堆中所有数字都比最大堆中的数字大。

```C++
template<typename T> class DynamicArray
{
public:
    void Insert(T num)
    {
        if(((min.size()+max.size()) & 1) == 0)
        {
            if(max.size() > 0 && num > max[0])
            {
                max.push_back(num);
                puysh_heap(max.begin(), max.end(), less<T>());

                num = max[0];
                
                pop_heap(max.begin(), max.end(), less<T>());
                max.pop_back();
            }
            min.push_back(num);
            push_heap(min.begin(),min.end(), greater<T>());
        }
        else
        {
            if (min.size() > 0 && min[0] < num)
            {
                min.push_back(num);
                push_heap(min.begin(), min.end(), greater<T>());
                num = min[0];
                pop_heap(min.begin(),min.end(), greater<T>());
                min.pop_back();
            }
            max.push_back(num);
            push_heap(max.begin(), max.end(), les<T>());
        }
    }

    T GetMedian()
    {
        int size = min.size() + max.size();
        if(size == 0)
            throw("No numberse are available");
        T median = 0;
        if((size & 1) == 1)
            midian = min[0]
        else
            median = (min[0] + max[0] /2);
            return median;
    }
private:
    vector<T> min;
    vector<T> max;
}
```

#### 连续子数组的最大和

> 输入一个整形数组，数组离有正数也有负数，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。

##### 解法一：

从头到尾逐个累加数组中的每个数字。初始化和为0，当累加当前数字后得到的累加和小于当前数组时（累加前的累加和小于0），就丢弃之前的累加值，从当前数字开始累加。

```C++
bool g_InvalidInput = false;

int FindGreatestSumOfSubArray(int* pData, int nLength)
{
    if((pData == nullptr) || (nLength <=0))
    {
        g_InvalidInput = true;
        return 0;
    }

    g_InvalidInput = false;

    int nCurSum = 0;
    int nGreatestSum = 0x80000000;
    for (int i = 0; i < nLength; ++i)
    {
        if(nCurSum <=0)
            nCurSum = pData[i];
        else
            nCurSum += pData[i];
        if (nCurSum > nGreatestSum)
            nGreatestSum = nCurSum;
    }
    return nGreatestSum;
}
```

##### 解法二：动态规划法

令 `f(i)` 表示第 `i` 个数字结尾的子数组的最大和，则需要求出 `max[f(i)]`。可以利用递归公式求 `f(i)`

`f(i) = pData[i] i = 0 || f(i-1) <= 0`

`f(i) = f(i-1)+pData[i] i!= 0 && f(i-1)>0` 

这种方法的程序和上面相同。公式中`f(i)` 对应 `nCurSum` 而 `max[f(i)]` 对应 `nGreatestSum`

#### 1~n整数中1出现的次数

> 输入一个整数n，求1~n这n个整数的十进制表示中1出现的次数。例如，输入12， 1~12这些整数中包含1的数字有1、10、11、12，1一共出现了5次。

以21345为例，将其分为1~1345和1346~21345。1346~21345中，首先分析1在最高位中的情况。在1346~21345中，1出现在10000~19999这10000个数字的万位中，一共出现了10000次。

需要注意的是，不是所有5位数在万位中出现的次数都是10000次。比如12345，1出现的次数是2345+1=2346次。

接下来分析1出现在最高位之外的其他4位数中的情况。1346~21345这20000个数字中后4位中1出现的次数是8000次，由于最高为是2，可以将其分为1346~11345和11346~21345。每一段剩下的4位数中，选择其中一位是1，其余三位可以在0~9这10个数字中任意选择，因此出现的次数是2\*4\*10^3=8000次。

```C++
#include <iostream>
#include <cstring>
using namespace std;
int PowerBase10(unsigned int n)
{
    int result = 1;
    for(unsigned int i = 0; i < n; ++i)
        result *= 10;
    return result;
}

int NumberOf1(const char* strN)
{
    if(!strN||*strN<'0' || *strN>'9' || *strN == '\0')
        return 0;

    int first = *strN - '0';
    unsigned int length = static_cast<unsigned int>(strlen(strN));

    if (length == 1 && first == 0)
        return 0;
    if (length == 1 && first > 0)
        return 1;
    
    int numFirstDigit = 0;
    if (first > 1)
        numFirstDigit = PowerBase10(length - 1);
        else if(first == 1)
            numFirstDigit = atoi(strN + 1) + 1;
    int numOtherDigits = first* (length - 1)*PowerBase10(length - 2);
    int numRecursive = NumberOf1(strN+1);
    return numFirstDigit + numOtherDigits + numRecursive;
}

int NumberOf1BetweenAndN(int n)
{
    if (n <= 0)
        return 0;
    char strN[50];
    sprintf(strN, "%d", n);
    return NumberOf1(strN);
}

int main()
{
    int n;
    cin >> n;
    cout << NumberOf1BetweenAndN(n) << endl;
    return 0;
}
```

#### 数字序列中某一位的数字

> 数字以0123456789101112131415......的格式序列化到一个字符序列中，在这个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4等等，请写一个函数，求任意第n位对应的数字。

前10位为0-9，之后的2\*90=180个数字为10~99，再接下来的3\*900=2700个数字为100-999，依照这个规律，可以找出第n位的数字。

```C++
#include <iostream>
using namespace std;

int myPow(int x, int y) // 使用math.h中的pow函数再转换为整形时会出现误差
{
    int re = x;
    for (int i = 1; i < y; ++i)
    {
        re *= x;
    }
    return re;
}
int countOfIntegers(int digits)
{
    if (digits == 1)
        return 10;
    int count = myPow(10, digits-1);
    return 9*count;
}

int beginNumber(int digits)
{
    if (digits == 1)
        return 0;
    return myPow(10, digits-1);
}

int digitAtIndex(int index, int digits)
{
    int number = beginNumber(digits) + index / digits;
    int indexFromRight= digits- index % digits;
    for (int i = 1; i < indexFromRight; ++i)
        number /= 10;
    return number % 10;
}
int digitAtIndex(int index)
{
    if (index < 0)
        return -1;
    int digits = 1;
    while(true)
    {
        int numbers = countOfIntegers(digits);
        if(index < numbers * digits)
            return digitAtIndex(index,digits);
        index -= digits * numbers;
        digits++;
    }
    return -1;
}

int main()
{
    int n;
    cin >> n;
    cout << digitAtIndex(n);
    return 0;
}
```

#### 把数组排成最小的数

> 输入一个正整数数组，把数组里所有数字拼接起来拍成一个数。打印能拼接出的所有数字中最小的一个。例如，输入数组{3，32，321}，则打印出这3个数字能排列成的最小数字 321323

两个数字m和n能拼成数字 mn 和 nm，如果 mn < nm，则应打印出 mn，定义此时m<n，反之则定义n<m。如果 mn=nm，则 m=n。拼接时需要考虑拼接成的数字是否会溢出，可以将数字转换为字符串。

```C++
const int g_MaxNumberLength = 10;

char* g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];
char* g_strCombine2 = new char[g_MaxNumberLength * 2 + 1];

int compare(const void* strNumber1, const void* strNumber2)
{
    strcpy(g_StrCombine1, *(const char** )strNumber1);
    strcat(g_StrCombine1, *(const char**)strNumber2);
    strcpy(g_strCombine2, *(const char**)strNumber2);
    strcat(g_strCombine2, *(const char**)strNumber1);
    return strcmp(g_StrCombine1, g_strCombine2);
}

void PrintMinNumber(int* numbers, int length)
{
    if (numbers == nullptr || length <= 0)
    {
        return;
    }
    char** strNumbers = (char**)(new int[length]);
    for(int i = 0; i < length; ++i)
    {
        strNumbers[i] = new char[g_MaxNumberLength + 1];
        sprintf(strNumbers[i], "%d", numbers[i]);
    }
    qsort(strNumbers, length, sizeof(char*), compare);
    for(int i = 0; i < length; ++i)
    {
        cout << strNumbers[i];
    }
    cout << endl;
    for(int i = 0; i < length; ++i)
    {
        delete[] strNumbers[i];
    }
    delete[] strNumbers;

}
```

#### 把数字翻译成字符串

> 给定一个数字，按照如下规则把它翻译成字符串，0翻译成a，1翻译成b……25翻译成z，一个数字可能有多个翻译。实现一个函数计算一个数字有多少种不同的翻译方法。

从数字末尾开始，从右到左翻译并计算不同翻译的数目。用数组counts存储对应每一位开始的字符串有几种翻译方法

例如12258

（1）从末位开始，数字8只有一种情况，8，counts[4] = 1

（2）58也只有一种翻译方法，即在（1）的前面加上数字5，counts[3] =counts[4]= 1

（3）258有两种翻译方法，在（2）前加上数字2或在（1）前加上数字25，因此为counts[2]=counts[3]+ counts[4]= 2

（4）2258有3种翻译方法，对应counts[1]=counts[2]+counts[3]=3

（5）12258有5种翻译方法，对应counts[0]=counts[1]+counts[2]=5

```C++
#include <iostream>
#include <string>
using namespace std;

int GetTransCount(const string& number)
{
    int length = number.length();
    int* counts = new int[length];
    int count = 0;

    for (int i = length - 1; i >= 0; --i)
    {
        count = 0;
        if (i < length - 1)
        {
            count = counts[i + 1];
        }
        else
        {
            count = 1;
        }

        if (i < length - 1)
        {
            int digit1 = number[i]-'0';
            int digit2 = number[i+1]-'0';
            int converted = digit1 * 10 + digit2;
            if(converted >= 10 && converted <= 25)
            {
                if (i < length -2)
                    count += counts[i+2];
                else
                    count += 1;
            }
        }
        counts[i] = count;
    }
    count = counts[0];
    delete[] counts;

    return count;
}

int GetTransCount(int number)
{
    if(number < 0)
        return 0;
    string numberInString = to_string(number);
    return GetTransCount(numberInString);
}

int main()
{
    int n;
    cin >> n;
    cout << GetTransCount(n);
    return 0;
}
```

#### 礼物的最大价值

> 在一个m*n的棋盘的每一格都有一个礼物，每个礼物都有一定的价值，你可以从棋盘的左上角开始拿格子里的礼物并且每次向右或者向下移动一个，直到到达棋盘的右下角。给定一个棋盘及其上面的礼物，计算你最多能拿到多少价值的礼物。

使用动态规划

假如有如下的一个棋盘

| i\j  | 0    | 1    | 2    | 3    |
| ---- | ---- | ---- | ---- | ---- |
| 0    | 1    | 10   | 3    | 8    |
| 1    | 12   | 2    | 9    | 6    |
| 2    | 5    | 7    | 4    | 11   |
| 3    | 3    | 7    | 16   | 5    |

如果要求从\[0\]\[0\]开始到\[3\]\[3\]能拿到多少价值礼物，则子问题为从\[0\]\[0\]到\[3\]\[2\]和从\[0\]\[0\]到\[2\]\[3\]能拿到多少价值礼物中的最优解。定义`f(i,j)`为i*j的棋盘上能拿到礼物的最优解，`v[i][j]`为棋盘`[i][j]`位置上礼物的价值，则`f(i,j)=max(f[i-1][j],f[i][j-1])+v[i][j]`c

```C++
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
    return 0;
}
```

对上述代码进行优化，可以使用一个长度为n的一维数组来代替二维数组。因为计算第i,j个格子时只需要`f[i-1][j]`和`f[i][j-1]`的值，因此，只需要一个一维数组，当计算第i行第j个格子时，数组中的前j-1个数保存的是第i行0~j-1列的值，第j~n-1个数保存的是第i-1行j~n-1列的值。

优化后的代码为：

```C++
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
        }
    }
    return dp[cols-1];
}
```

#### 最长不含重复字符的字符串

> 请从字符串中超出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。假设字符串中只包含‘a’~'z'的字符。

使用动态规划，定义函数`f(i)`表示以第i个字符串结尾的不包含重复字符串的最长长度。从左到右扫描字符串的每个字符。如果第i个字符之前没有出现过，则`f(i)=f(i-1)+1`，否则先计算第i个字符和它上次出现在字符串中的位置和距离，记为d，若d小于或等于`f(i-1)`，此时第i个字符上次出现在`f(i-1)`对应的最长子字符串之中。因此`f(i)=d`。若d大于`f(i-1)`，此时仍然有`f(i)=f(i-1)+1`

```C++
#include <iostream>
#include <string>
using namespace std;

int longestSubstringWithoutDuplication(const string& str)
{
    int curLength = 0;
    int maxLength = 0;

    int* position = new int[26];
    for (int i = 0; i < 26; i++)
    {
        position[i]=-1;
    }

    for (int i = 0; i < str.length(); ++i)
    {
        int prevIndex = position[str[i]-'a'];
        if (prevIndex < 0 || i - prevIndex > curLength)
            ++curLength;
        else
        {
            if (curLength > maxLength)
                maxLength = curLength;
            curLength = i - prevIndex;
        }
        position[str[i]-'a']=i;
    }

    if (curLength>maxLength)
        maxLength = curLength;
    
    delete[] position;
    return maxLength;
}

int main()
{
    string s;
    cin >> s;
    cout << longestSubstringWithoutDuplication(s);
    return 0;
}
```

#### 丑数

> 我们把只包含因子2，3，5的数称为整数，求从小到大顺序的第1500个丑数。习惯上我们把1当作第一个丑数。

可以逐个判断每个整数是不是丑数，但是效率不高。可以将之前求出的丑数存到数组里。根据丑数的定义，一个丑数应该是另一个丑数乘以2、3或5。可以记下当前数组里最大的丑数M。将前面某一个丑数乘以2、3或5，如果结果小于M，则说明这个数已经存在在前面的数组中。

```C++
#include <iostream>
using namespace std;

int Min(int n1, int n2, int n3)
{
    int min = (n1 < n2)? n1 : n2;
    min = (min < n3)? min : n3;
    return min;
}

int GetUglyNumber(int index)
{
    if (index <= 0)
    {
        return 0;
    }
    int* pUglyNumbers = new int[index];
    pUglyNumbers[0]=1;
    int nextUglyIndex = 1;
    int* pMultiply2 = pUglyNumbers;
    int* pMultiply3 = pUglyNumbers;
    int* pMultiply5 = pUglyNumbers;

    while(nextUglyIndex < index)
    {
        int min = Min(*pMultiply2*2, *pMultiply3 * 3, *pMultiply5 * 5);
        pUglyNumbers[nextUglyIndex] = min;
        while (*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply2;
        while (*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply3;
        while (*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply5;
        ++nextUglyIndex;
    }
    int ugly = pUglyNumbers[nextUglyIndex-1];
    delete[] pUglyNumbers;
    return ugly;
}

int main()
{
    int n;
    cin >> n;
    cout << GetUglyNumber(n);
    return 0;
}
```


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
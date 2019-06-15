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


### 在排序数组中查找数字

#### 数字在排序数组中出现的次数

> 统计一个数字在排序数组中出现的次数，例如，输入排序数组{1，2，3，3，3，4，5} 和数字3，由于3在这个数组中出现了3次，因此输出3

```C++
#include <iostream>
using namespace std;
int BinarySearch(int* nums, int lo, int hi, int target) // 返回第一个等于target的元素或当向数组中插入target时应该插入的位置。
{
    int mid = (lo+hi)/2;
    while(lo < hi)
    {
        if (nums[mid] < target)
        {
            lo = mid+1;
        }
        else
        {
            hi = mid;
        }
        mid = (lo + hi)/2;
        
    }
    return lo;
}

int countnum(int* nums, int size, int pos, int target)
{
    if (pos >= size || pos < 0)
    {
        return 0;
    }
    else
    {
        int count = 0;
        while (nums[pos]==target)
        {
            ++count;
            ++pos;
        }
        return count;
    }
    
}

int main()
{
    int n = 0, target;
    cin >> n;
    int* nums = new int[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    cin >> target;
    cout << countnum(nums, n, BinarySearch(nums, 0, n, target), target);
    return 0;
}
```

#### 0~n-1中缺失的数字

> 一个长度为n-1的递增序列数组中的所有数字都是唯一的，并且每个数字都在范围0~n-1之内，在范围0~n-1内的n各数字中有且只有一个数字不在该数组中，找出这个数字。

用公式`n(n-1)/2`求出数字0~n-1的所有数字之和，再减去数组中所有的数字，时间复杂度O(n)

利用二分查找，如果中间元素的值和下标相等，则缺失的数字再数组的右半边。如果中间元素的值和下标不相等，而前一个元素的值和下标相等，则它的下标就是缺失的数字，否则下一轮查找数组的左半边。

```c++
#include <iostream>
using namespace std;

int findMissingNum(int* nums, int lo, int hi)
{
    int mid = (lo+hi)/2;
    while(lo < hi)
    {
        if (nums[mid] == mid)
        {
            lo = mid+1;
        }
        else
        {
            hi = mid;
        }
        mid = (lo+hi)/2;
    }
    return lo;
}

int main()
{
    int n = 0;
    cin >> n;
    int* nums = new int[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    cout << findMissingNum(nums, 0, n);
    return 0;
}

```

#### 数组中数值和下标相等的元素

假设一个单调递增的数组里每个元素都是整数并且是唯一的，编程实现一个函数，找出数组中任意一个数值等于其下标的元素。例如，在数组{-3，-1，1，3，5}中，数字3和它的下标相等。

```C++
#include <iostream>
using namespace std;
int getNumSameAsIndex(int* nums, int lo, int hi)
{
    int mid = (lo+hi)/2;
    while(lo < hi)
    {
        if (nums[mid] < mid)
        {
            lo = mid+1;
        }
        else
        {
            hi = mid;
        }
        mid = (lo+hi)/2;
    }
    return lo;
}
int main()
{
    int n = 0;
    cin >> n;
    int* nums = new int[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    cout << getNumSameAsIndex(nums, 0, n);
    return 0;
}

```


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


#include <iostream>
using namespace std;
int BinarySearch(int* nums, int lo, int hi, int target)
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

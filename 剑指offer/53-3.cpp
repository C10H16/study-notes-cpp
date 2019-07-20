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

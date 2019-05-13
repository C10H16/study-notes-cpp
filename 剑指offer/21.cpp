#include <iostream>
using namespace std;

inline bool isEven(int n)
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
#include <iostream>
using namespace std;

bool VerifySequenceOfBST(int* sequence, int length)
{
    if(sequence == nullptr || length <= 0)
    {
        return false;
    }
    int root = sequence[length - 1];
    // 在二叉搜索树中左子节点的值小于根节点的值。
    int i = 0;
    for(; i < length-1; ++i)
    {
        if (sequence[i]>root)
            break;
    }
    // 在二叉搜索树中右子树节点的值大于根节点的值
    int j = i;
    for(;j < length-1; ++j)
    {
        if (sequence[j] < root)
            return false;
    }
    bool left = true;
    if(i > 0)
        left = VerifySequenceOfBST(sequence, i);
    bool right = true;
    if (i < length - 1)
        right = VerifySequenceOfBST(sequence + i, length - i - 1);
    return left && right;
}

int main()
{
    int n = 0;
    cin >> n;
    int* nums = new int[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    cout <<  VerifySequenceOfBST(nums, n);
    return 0;
}
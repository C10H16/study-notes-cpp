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

### 二叉搜索树的第k大节点

> 给定一棵二叉搜索树，找出其第k大节点。

二叉搜索树的中序遍历是节点数之从大到小排列的，因此只需求出二叉树的中序遍历。

```C++
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

void addLeftCh(BinaryTreeNode* parent,int left) // 添加左孩子
{
	parent->m_pLeft = new BinaryTreeNode;
	parent->m_pLeft->m_nValue = left;
	parent->m_pLeft->m_pLeft = nullptr;
	parent->m_pLeft->m_pRight = nullptr;
}

void addRightCh(BinaryTreeNode* parent,int right) // 添加右孩子
{
	parent->m_pRight = new BinaryTreeNode;
	parent->m_pRight->m_nValue = right;
	parent->m_pRight->m_pLeft = nullptr;
	parent->m_pRight->m_pRight = nullptr;
}

void BuildTree(BinaryTreeNode** head, int* val, int n)
{
    BinaryTreeNode* pHead = *head;
    pHead->m_nValue = 0;
	pHead->m_pLeft = nullptr;
	pHead->m_pRight = nullptr;
	queue<BinaryTreeNode*> temp;
	temp.push(pHead);
	
	pHead->m_nValue = val[0];
	BinaryTreeNode* pNode;
	int i = 1;
	while(i < n && (!temp.empty()))
	{
		pNode = temp.front();
		if (val[i]!=0)
		{
			addLeftCh(pNode,val[i]);
			temp.push(pNode->m_pLeft);
		}
		if (i+1<n && val[i+1]!=0)
		{
			addRightCh(pNode,val[i+1]);
			temp.push(pNode->m_pRight);
		}
		temp.pop();
		i+=2;
	}
}

void getAloneLeftChild(BinaryTreeNode* pHead, stack<BinaryTreeNode*>& temp)
{
	BinaryTreeNode* p = pHead;
	while(p)
	{
		temp.push(p);
		p = p->m_pLeft;
	}
}

int kthNode(BinaryTreeNode* pHead, int k) // 中序遍历寻找第k个节点
{
	int i = 0;
	stack<BinaryTreeNode*> temp;
	BinaryTreeNode* p;
	getAloneLeftChild(pHead, temp);
	while(!temp.empty() && i < k)
	{
		p = temp.top();
		temp.pop();
		++i;
		if (p->m_pRight)
			getAloneLeftChild(p->m_pRight, temp);
	}
	return p->m_nValue;

}

int main()
{
    BinaryTreeNode* pHead = new BinaryTreeNode;
    BinaryTreeNode** head = &pHead;
    int n, k;
    cin >> n;
	int* val = new int[n];
	int i = 0;
	for(i = 0; i < n; ++i)
	{
		cin >> val[i];	
	}
	cin >> k;
    BuildTree(head, val, n);
	cout << kthNode(pHead, k);
    return 0;
}
```

### 二叉树的深度

#### 二叉树的深度

> 输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。

```C++
int TreeDepth(BinaryTreeNode* pRoot)
{
	if(pRoot == nullptr)
		return 0;
	int nLeft = TreeDepth(pRoot->m_pLeft);
	int nRight = TreeDepth(pRoot->m_pRight);
	return(nLeft > nRight)? (nLeft+1):(nRight+1);
}
```

#### 平衡二叉树

> 输入一棵二叉树的根节点，判断该树是不是平衡二叉树。如果某二叉树中任意节点的左、右子树的深度相差不超过1，那么它就是一棵平衡二叉树。

遍历树的每个节点的时候求该节点的深度，如果每个节点的左右子树深度相差不超过1，则为平衡二叉树。由于每个节点都会被遍历多次，因此时间效率不高。

```C++
bool IsBalanced(BinaryTreeNode* pRoot)
{
    if (pRoot == nullptr)
    {
        return true;
    }
    int left = TreeDepth(pRoot->m_pLeft);
    int right = TreeDepth(pRoot->m_pRight);
    int diff = left - right;
    if (diff > 1 || diff < -1)
        return false;
    return IsBalanced(pRoot->m_pLeft)&&IsBalanced(pRoot->m_pRight);
}
```

利用后序遍历的方法遍历整颗二叉树，在遍历每个节点的时候记录其深度，就可以一边遍历一遍判断每个节点是不是平衡的

```C++
bool IsBalanced(BinaryTreeNode* pRoot, int* pDepth)
{
	if(pRoot == nullptr)
	{
		*pDepth = 0;
		return true;
	}
	int left, right;
	if(IsBalanced(pRoot->m_pLeft,&left) && IsBalanced(pRoot->m_pRight, &right))
	{
		int diff = left - right;
		if (diff <=1 && diff >= -1)
		{
			*pDepth = 1+(left > right? left : right);
			return true;
		}
	}
	return false;
}

bool IsBalanced(BinaryTreeNode* pRoot)
{
	int depth = 0;
	return IsBalanced(pRoot, &depth);
}
```


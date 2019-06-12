# 剑指Offer

## 解决面试题的思路

### 二叉树的镜像

> 完成一个函数，输入一个二叉树，该函数输出它的镜像。二叉树节点的定义如下：

```C++
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
}
```

通过观察可以发现，对一棵树求镜像，只需要先序遍历这棵树的每个节点，如果遍历到的节点有子节点，则交换它的两个子节点。当交换玩所有非叶子节点的子节点之后，得到的即为树的镜像。

另一种方式是，从根节点开始，节点的右孩子、左孩子依次存入队列，再从队列中读取节点，依次向队列中存入该节点的有孩子、左孩子，直到队列为空。需要额外空间但是不会改变原来的树。

```C++
#include <iostream>
#include <queue>
using namespace std;
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

void MirrorRecursively(BinaryTreeNode* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}
	if (pNode->m_pLeft==nullptr && pNode->m_pRight==nullptr)
	{
		return;
	}
	BinaryTreeNode* pTemp = pNode->m_pLeft;
	pNode->m_pLeft = pNode->m_pRight;
	pNode->m_pRight = pTemp;

	if (pNode->m_pLeft)
	{
		MirrorRecursively(pNode->m_pLeft);
	}
	if (pNode->m_pRight)
	{
		MirrorRecursively(pNode->m_pRight);
	}
}

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

void printTree (BinaryTreeNode* root) // 打印树 
{
	queue<BinaryTreeNode*> node;
	cout << root->m_nValue << " ";
	node.push(root->m_pLeft);
	node.push(root->m_pRight);
	while(!node.empty())
	{
		if (node.front() != nullptr)
		{
			cout << node.front()->m_nValue << " ";
			node.push(node.front()->m_pLeft);
			node.push(node.front()->m_pRight);
			node.pop();
		}
		else
		{
			cout << "X ";
			node.pop();
		}
	}
}

void printMirror (BinaryTreeNode* root) // 打印树 
{
	queue<BinaryTreeNode*> node;
	cout << root->m_nValue << " ";
	node.push(root->m_pRight);
	node.push(root->m_pLeft);
	while(!node.empty())
	{
		if (node.front() != nullptr)
		{
			cout << node.front()->m_nValue << " ";
			node.push(node.front()->m_pRight);
			node.push(node.front()->m_pLeft);
			node.pop();
		}
		else
		{
			cout << "X ";
			node.pop();
		}
	}
}

int main()
{
	BinaryTreeNode* head1 = new BinaryTreeNode;
	head1->m_nValue = 0;
	head1->m_pLeft = nullptr;
	head1->m_pRight = nullptr;
	queue<BinaryTreeNode*> temp;
	temp.push(head1);
	int n1, n2;
	cin >> n1;
	int* val1 = new int[n1];
	int i = 0;
	for(i = 0; i < n1; ++i)
	{
		cin >> val1[i];	
	}
	head1->m_nValue = val1[0];
	BinaryTreeNode* pNode;
	i = 1;
	while(i < n1 && (!temp.empty())) // 构造树 
	{
		pNode = temp.front();
		if (val1[i]!=0)
		{
			addLeftCh(pNode,val1[i]);
			temp.push(pNode->m_pLeft);
		}
		if (val1[i+1]!=0)
		{
			addRightCh(pNode,val1[i+1]);
			temp.push(pNode->m_pRight);
		}
		temp.pop();
		i+=2;
	}

	printTree(head1);
    cout << endl;
	printMirror(head1);
	cout << endl;
	MirrorRecursively(head1);
	printTree(head1);
	return 0;
}
```

### 对称的二叉树

> 实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。

对二叉树按根节点->左孩子->右孩子和根节点->右孩子->左孩子的顺序遍历，如果遍历顺序相同，则为对称的。遍历时，需要考虑为空的节点。也可使用上一题输出镜像的方法对二叉树进行遍历，与正常输出的顺序进行比较。

```C++
#include <iostream>
#include <queue>
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

bool isSymmetrical(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot1 == nullptr && pRoot2 == nullptr)
	{
		return true;
	}
	if (pRoot1 == nullptr || pRoot2 == nullptr)
	{
		return false;
	}
	if (pRoot1->m_nValue != pRoot2->m_nValue)
	{
		return false;
	}
	return isSymmetrical(pRoot1->m_pLeft, pRoot2->m_pRight)
		&& isSymmetrical(pRoot1->m_pRight, pRoot2->m_pLeft);
}

bool isSymmetrical(BinaryTreeNode* pRoot)
{
	return isSymmetrical(pRoot, pRoot);
}

bool Mirror(BinaryTreeNode* root)
{
	queue<BinaryTreeNode*> node;
	queue<BinaryTreeNode*> mirror;

	node.push(root->m_pLeft);
	node.push(root->m_pRight);
	mirror.push(root->m_pRight);
	mirror.push(root->m_pLeft);
	while(!node.empty())
	{
		if (node.front()==nullptr && mirror.front()==nullptr)
		{
			node.pop();
			mirror.pop();
		}
		else if (node.front()!=nullptr&&mirror.front()!=nullptr&&node.front()->m_nValue==node.front()->m_nValue)
		{
			node.push(node.front()->m_pLeft);
			node.push(node.front()->m_pRight);
			mirror.push(mirror.front()->m_pRight);
			mirror.push(mirror.front()->m_pLeft);
			node.pop();
			mirror.pop();
		}
		else
		{
			return false;
		}
	}
	return true;
}


int main()
{
	BinaryTreeNode* head1 = new BinaryTreeNode;
	head1->m_nValue = 0;
	head1->m_pLeft = nullptr;
	head1->m_pRight = nullptr;
	queue<BinaryTreeNode*> temp;
	temp.push(head1);
	int n1, n2;
	cin >> n1;
	int* val1 = new int[n1];
	int i = 0;
	for(i = 0; i < n1; ++i)
	{
		cin >> val1[i];	
	}
	head1->m_nValue = val1[0];
	BinaryTreeNode* pNode;
	i = 1;
	while(i < n1 && (!temp.empty())) // 构造树 
	{
		pNode = temp.front();
		if (val1[i]!=0)
		{
			addLeftCh(pNode,val1[i]);
			temp.push(pNode->m_pLeft);
		}
		if (val1[i+1]!=0)
		{
			addRightCh(pNode,val1[i+1]);
			temp.push(pNode->m_pRight);
		}
		temp.pop();
		i+=2;
	}

	cout << endl;
	cout << isSymmetrical(head1) << endl;
	cout << Mirror(head1);
	return 0;
}
```

### 顺时针打印矩阵

>输入一个矩阵，按照从外向里以顺时针的次序一次打印出每一个数字。例如，输入如下矩阵
>
>1    2    3    4
>
>5    6    7    8
>
>9    10  11  12
>
>13  14  15  16
>
>则输出 1 2 3 4 8 12 16 15 1 4  13 9 5 6 7 11 10

```C++
#include <iostream>
using namespace std;

void PrintMatrixInCircle(int** matrix, int cols, int rows, int start)
{
	int endX = cols - 1 - start;
	int endY = rows - 1 - start;

	// 从左到右打印一行
	// 肯定会执行
	for (int i = start; i <= endX; ++i)
	{
		int number = matrix[start][i];
		cout << number << " ";
	}
	
	// 从上到下打印一列
	// 终止行号需大于起始行号
	if (start < endY)
	{
		for(int i = start + 1; i <= endY; ++i)
		{
			int number = matrix[i][endX];
			cout << number << " ";
		}
	}

	// 从右到左打印一行
	// 打印的前提是至少有两行
	if (start < endX && start < endY)
	{
		for(int i = endX-1; i >= start; --i)
		{
			int number = matrix[endY][i];
			cout << number << " ";
		}
	}

	// 从上到下打印一行
	// 需要至少3行2列，即终止行号比起始行号至少大2
	if (start < endX && start < endY -1)
	{
		for (int i = endY -1; i >= start + 1; --i)
		{
			int number = matrix[i][start];
			cout << number << " ";
		}
	}
}

void PrintMatrixColockWisely(int** matrix, int cols, int rows)
{
	if (matrix == nullptr || cols <=0 || rows <=0)
	{
		return;
	}
	int start = 0;
	while (cols > start * 2 && rows > start * 2) 
        // 循环条件,开始行列号相同，且小于 总行数/2 和 总列数/2
	{
		PrintMatrixInCircle(matrix, cols, rows, start);
		++start;
	}
}


int main()
{
	int rows, cols;
	cin >> rows >> cols;
	int** matrix = new int*[rows];
	for(int i = 0; i < rows; ++i)
	{
		matrix[i] = new int[cols];
	}
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			cin >> matrix[i][j];
		}
	}

	PrintMatrixColockWisely(matrix, cols, rows);
	return 0;
}
```

[相关题目：输入一个整数n，以顺时针的方式输出n*n的矩阵][https://github.com/C10H16/leetcode-note/blob/master/note/leetcode-54%2C59.md#leetcode-59-螺旋矩阵ⅱ]

### 包含min函数的栈

> 定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min函数。在该栈中，调用min、push及pop的时间复杂度都是O(1)

可以在定义数据栈之外再定义一个辅助栈，存储当前的最小值。例如：

|步骤|操作|数据栈|辅助栈|最小值|
|--|--|--|--|--|
|1|压入3|3|3|3|
|2|压入4|3，4|3，3|3|
|3|压入2|3，4，2|3，3，2|2|
|4|压入1|3，4，2，1|3，3，2，1|1|
|5|弹出|3，4，2|3，3，2|2|
|6|弹出|3，4|3，3|3|
|7|压入0|3，4，0|3，3，0|0|

```C++
#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;
template <typename T>
class StackWithMin
{
public:
    void push(const T& value);
    void pop();
    const T& min()const;
private:
    stack<T> m_data;
    stack<T> m_min;
};
template <typename T> void StackWithMin<T>::push(const T& value)
{
	m_data.push(value);
    if (m_min.empty()||value<m_min.top())
    {
        m_min.push(value);
    }    
    else
    {
        m_min.push(m_min.top());
    }
    
}

template <typename T> void StackWithMin<T>::pop()
{
    assert(m_data.size()>0&&m_min.size()>0);
    m_data.pop();
    m_min.pop();
}

template<typename T> const T& StackWithMin<T>::min() const
{
    assert(m_data.size()>0&&m_min.size()>0);
    return m_min.top();
}
int main()
{
    StackWithMin<int> test;
    int n = 0;
    cin >> n;
    int temp = 0;
    for(int i = 0; i < n; ++i)
    {
        cin >> temp;
        test.push(temp);
        cout << test.min();
    }
    for(int i = 0; i < n-1; ++i)
    {
        test.pop();
        cout << test.min();
    }
    return 0;
}
```

### 栈的压入、弹出序列

> 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如，顺序{1,2,3,4,5}是某栈的压入序列，序列{5,4,3,2,1}是该压栈序列对应的一个弹出序列，而{4,3,5,1,2}就不可能是该压栈序列的弹出序列。

借助一个辅助栈，把第一个序列中的数字一次压入该辅助栈，并和弹出序列进行比较。如果下一个弹出的数字刚好是栈顶数字，那么直接弹出。如果下一个弹出的数字不在栈顶，则把压栈序列中还没有入栈的数字压入辅助栈，直到把所有数字都压入栈后仍没有找到下一个弹出的数字，那么该序列不可能是一个弹出序列。

```C++
#include <iostream>
#include <stack>
using namespace std;

bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    bool bPossible = false;
    if (pPush != nullptr && pPop != nullptr && nLength > 0)
    {
        const int* pNextPush = pPush;
        const int* pNextPop = pPop;
        stack<int> stackData;
        while (pNextPop - pPop < nLength)
        {
            while (stackData.empty()||stackData.top()!=*pNextPop)
            {
                if (pNextPush - pPush == nLength)
                {
                    break;
                }
                stackData.push(*pNextPush);
                pNextPush++;
            }
            if (stackData.top() != *pNextPop)
            {
                break;
            }
            stackData.pop();
            pNextPop++;
        }

        if (stackData.empty()&&pNextPop-pPop==nLength)
        {
            bPossible = true;
        }
    }
    return bPossible;
}

int main()
{
    int n;
    cin >> n;
    int* pPush = new int[n];
    int* pPop = new int[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> pPush[i];
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> pPop[i];
    }
    cout << IsPopOrder(pPush, pPop, n);
    return 0;
}
```

### 从上到下打印二叉树

#### 题目一 不分行打印二叉树

> 从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。二叉树的节点定义如下：

```C++
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
}
```

#### 题目二 分行从上到下打印二叉树

> 从上到下按层打印二叉树，同一层的节点按从左到有的顺序打印，每一层打印一行。

```C++
#include <iostream>
#include <queue>
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
	while(i < n && (!temp.empty())) // 构造树 
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

void printTree (BinaryTreeNode* root) // 打印树 
{
	queue<BinaryTreeNode*> node;
	cout << root->m_nValue << endl;
	node.push(root->m_pLeft);
	node.push(root->m_pRight);
    int i = 2, j = 2;
	while(!node.empty())
	{
		if (node.front() != nullptr)
		{
			cout << node.front()->m_nValue << " ";
            --i;
            if (i==0)
            {
                cout << endl;
                i = j * 2;
                j = i;
            }
			node.push(node.front()->m_pLeft);
			node.push(node.front()->m_pRight);
			node.pop();
		}
		else
		{
			cout << "X ";
            --i;
            if (i==0)
            {
                cout << endl;
                i = j * 2;
                j = i;
            }
			node.pop();
		}
	}
}

void PrintFromTopToBottom(BinaryTreeNode* pTreeRoot)
{
    if(!pTreeRoot)
        return;
    deque<BinaryTreeNode*> dequeTreeNode;
    dequeTreeNode.push_back(pTreeRoot);
    while(dequeTreeNode.size())
    {
        BinaryTreeNode* pNode = dequeTreeNode.front();
        dequeTreeNode.pop_front();
        cout << pNode->m_nValue << " ";

        if (pNode->m_pLeft)
        {
            dequeTreeNode.push_back(pNode->m_pLeft);
        }
        if (pNode->m_pRight)
        {
            dequeTreeNode.push_back(pNode->m_pRight);
        }
    }
}

void Print(BinaryTreeNode* pRoot)
{
    if (pRoot == nullptr)
    {
        return;
    }
    queue<BinaryTreeNode*> nodes;
    nodes.push(pRoot);
    int nextLevel = 0;
    int toBePrinted = 1;
    while(!nodes.empty())
    {
        BinaryTreeNode* pNode = nodes.front();
        cout << pNode->m_nValue << " ";
        if (pNode->m_pLeft!=nullptr)
        {
            nodes.push(pNode->m_pLeft);
            ++nextLevel;
        }
        if (pNode->m_pRight!=nullptr)
        {
            nodes.push(pNode->m_pRight);
            ++nextLevel;
        }
        nodes.pop();
        --toBePrinted;
        if (toBePrinted == 0)
        {
            cout << endl;
            toBePrinted = nextLevel;
            nextLevel = 0;
        }
    }
}

int main()
{
    BinaryTreeNode* pHead = new BinaryTreeNode;
    BinaryTreeNode** head = &pHead;
    int n;
    cin >> n;
	int* val = new int[n];
	int i = 0;
	for(i = 0; i < n; ++i)
	{
		cin >> val[i];	
	}
    BuildTree(head, val, n);
    PrintFromTopToBottom(pHead);
    cout << endl;
    Print(pHead);
    cout << endl;
    printTree(pHead);
    return 0;
}
```

### 题目三 之字形打印二叉树

> 实现一个函数按照之字形顺序打印二叉树，第一行按照从左到右，第二行按照从右到左，第三行再从左到右，以此类推。

按照之字形顺序打印需要两个栈，如果当前打印的是奇数层，则先存放左子节点，再存放右子节点到一个栈里。如果是打印偶数层，则先存放右子节点，再存放左子节点到另一个栈中。

```C++
void Print(BinaryTreeNode* pRoot)
{
    if (pRoot==nullptr)
        return;
    stack<BinaryTreeNode*> levels[2];
    int current = 0;
    int next = 1;

    levels[current].push(pRoot);
    while (!levels[0].empty()||!levels[1].empty())
    {
        BinaryTreeNode* pNode = levels[current].top();
        levels[current].pop();

        cout << pNode->m_nValue << " ";

        if (current==0)
        {
            if (pNode->m_pLeft!=nullptr)
                levels[next].push(pNode->m_pLeft);
            if (pNode->m_pRight!=nullptr)
                levels[next].push(pNode->m_pRight);
        }
        else
        {
            if (pNode->m_pRight != nullptr)
                levels[next].push(pNode->m_pRight);
            if (pNode->m_pLeft != nullptr)
                levels[next].push(pNode->m_pLeft);
        }

        if (levels[current].empty())
        {
            cout << endl;
            current = 1 - current;
            next = 1 - next;
        }
        
    }
}
```

### 二叉搜索树的后序遍历序列

> 输入一个整数数组，判断该数组是不是某二叉搜索树的后续遍历结果。如果是则返回true，否则返回false。假设输入的数组的任意两个数字都互不相同。

输入数组的最后一个数字一定是该二叉树的根节点。而二叉搜索树的特点为，左子树的值一定小于根节点的值，右子树的值一定大于根节点的值。因此，可以通过根节点的值将数组分为左子树和右子树两部分。进而将子树分为左右两部分。以此类推。

```C++
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
```

### 二叉树中和为某一值的路径

> 输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下已知到叶节点所经过的节点形成一条路径。二叉树的节点定义如下：

```C++
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
}
```

```C++
#include <iostream>
#include <queue>
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
	while(i < n && (!temp.empty())) // 构造树 
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

void findPath(BinaryTreeNode* pRoot, int expectedSum, vector<int>& path, int currentSum)
{
    currentSum += pRoot->m_nValue;
    path.push_back(pRoot->m_nValue);
    // 如果是叶节点，并且路径上节点值的和等于输入的值，则打印出则条路径
    bool isLeaf = pRoot->m_pLeft == nullptr && pRoot->m_pRight == nullptr;
    if (currentSum == expectedSum && isLeaf)
    {
        cout << "A path is found: ";
        vector<int>::iterator iter = path.begin();
        for(;iter != path.end(); ++iter)
            cout << *iter << "\t";
        cout << endl;
    }

    // 如果不是叶节点，则遍历它的子节点
    if (pRoot->m_pLeft != nullptr)
        findPath(pRoot->m_pLeft, expectedSum, path, currentSum);
    if (pRoot->m_pRight != nullptr)
        findPath(pRoot->m_pRight, expectedSum, path, currentSum);
    
    // 在返回父节点之前，在路径上删除当前节点
    path.pop_back();
}

void findPath(BinaryTreeNode *pRoot, int expectedSum)
{
    if (pRoot==nullptr)
    {
        return;
    }
    vector<int> path;
    int currentSum = 0;
    findPath(pRoot, expectedSum, path, currentSum);
}

int main()
{
    BinaryTreeNode* pHead = new BinaryTreeNode;
    BinaryTreeNode** head = &pHead;
    int n, sum;
    cin >> n >> sum;
	int* val = new int[n];
	int i = 0;
	for(i = 0; i < n; ++i)
	{
		cin >> val[i];	
	}
    BuildTree(head, val, n);
    findPath(pHead, sum);
    return 0;
}
```

### 复杂链表的复制

> 请实现函数 ComplexListNode* Clone(ComplexListNode* pHead), 复制一个复杂链表。在复杂链表中，每个节点除了有一个m_pNext指针指向下一个节点，还有一个m_pSibling指针指向链表中的任意节点或者nullptr。节点的C++定义如下：

```C++
struct ComplexListNode
{
    int m_nValue;
    ComplexListNode* m_pNext;
    ComplexListNode* m_pSibling;
}
```

首先复制原始链表上的每个节点N创建N'，然后把这些创建出来的节点用m_pNext链接起来。同时把<N,N'>放到一个哈希表中。第二步，设置复制链表上每个节点的m_pSibling，如果在原始链表中节点N的 m_pSibling指向节点S，那么在复制链表中，对应的N'应该指向S'。可以通过哈希表在O(1) 时间根据S找到S'。

另一种不需要辅助空间的方法是，首先根据原始链表的每个节点创建对应的N'，将N'连接在N的后面。

即，原链表：`A-B-C`，经过第一步之后 `A-A'-B-B'-C-C'`

第二部设置复制出来的节点m_pSibling，假设原始链表上N的m_pSibling指向S，那么N‘的m_pSibling则指向S->m_pNext，即S'。

第三步，将上面的链表拆分成两个链表，奇数节点为原链表，偶数节点为复制出来的链表。

```C++
void CloneNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode != nullptr)
    {
        ComplexListNode* pCloned = new ComplexListNode();
        pCloned->m_nValue = pNode->m_nValue;
        pCloned->m_pNext = pNode->m_pNext;
        pCloned->m_pSibling = nullptr;
        pNode->m_pNext = pCloned;
        pNode=pCloned->m_pNext;
    }
}
void ConnectSiblingNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode!=nullptr)
    {
        ComplexListNode* pCloned = pNode->m_pNext;
        if (pNode->m_pSibling != nullptr)
        {
            pCloned->m_pSibling = pNode->m_pSibling->m_pNext;
        }
        pNode = pCloned->m_pNext;
    }
}
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    ComplexListNode* pClonedHead = nullptr;
    ComplexListNode* pClonedNode = nullptr;
    if (pNode != nullptr)
    {
        pClonedHead = pClonedNode = pNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode=pNode->m_pNext;
    }
    while (pNode != nullptr)
    {
        pClonedNode->m_pNext = pNode->m_pNext;
        pClonedNode = pClonedNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }
    return pClonedHead;
}

ComplexListNode* Clone(ComplexListNode* pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}
```

### 二叉搜索树与双向链表

> 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表，要求不能创建任何新的节点，只能调整树中节点的指针。二叉树节点的定义如下：

```C++
struct BianryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
}
```

转换时，根节点与左子树最大的节点和右子树最小的节点相连。

```C++
#include <iostream>
#include <queue>
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
	while(i < n && (!temp.empty())) // 构造树 
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

void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList)
{
    if(pNode == nullptr)
    {
        return;
    }
    BinaryTreeNode* pCurrent = pNode;
    if (pCurrent->m_pLeft != nullptr)
        ConvertNode(pCurrent->m_pLeft, pLastNodeInList);
    pCurrent->m_pLeft = *pLastNodeInList;
    if (*pLastNodeInList != nullptr)
    {
        (*pLastNodeInList)->m_pRight = pCurrent;
    }
    *pLastNodeInList = pCurrent;
    if (pCurrent->m_pRight != nullptr)
    {
        ConvertNode(pCurrent->m_pRight, pLastNodeInList);
    }
}

BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree)
{
    BinaryTreeNode* pLastNodeInList = nullptr;
    ConvertNode(pRootOfTree, &pLastNodeInList);
    // pLastNodtList 指向双向链表的尾节点
    // 需要返回头节点
    BinaryTreeNode* pHeadOfList = pLastNodeInList;
    while(pHeadOfList != nullptr && pHeadOfList->m_pLeft != nullptr)
    {
        pHeadOfList = pHeadOfList->m_pLeft;
    }
    return pHeadOfList;
}

int main()
{
    BinaryTreeNode* pHead = new BinaryTreeNode;
    BinaryTreeNode** head = &pHead;
    int n;
    cin >> n;
	int* val = new int[n];
	int i = 0;
	for(i = 0; i < n; ++i)
	{
		cin >> val[i];	
	}
    BuildTree(head, val, n);
    BinaryTreeNode* ListHead = Convert(pHead);
    BinaryTreeNode* temp = ListHead;
    while (temp != nullptr)
    {
        cout << temp->m_nValue << " ";
        temp = temp->m_pRight;
    }
    return 0;
}
```

### 序列化二叉树

> 请实现两个函数，分别用来序列化和反序列化二叉树

```C++
bool ReadStream(istream& stream, int* number)
{
    if(stream.eof())
        return false;
    char buffer[32];
    buffer[0] = '\0';
    char ch;
    stream >> ch;
    int i = 0;
    while(!stream.eof() && ch != ',')
    {
        buffer[i++] = ch;
        stream >> ch;
    }
    bool isNumeric = false;
    if(i > 0 && buffer[0] != '$')
    {
        *number = atoi(buffer);
        isNumeric = true;
    }
    return isNumeric;
}

void Serialize(BinaryTreeNode* pRoot, ostream& stream)
{
    if (pRoot == nullptr)
    {
        stream<<"&,";
        return;
    }
    stream<<pRoot->m_nValue<<",";
    Serialize(pRoot->m_pLeft, stream);
    Serialize(pRoot->m_pRight, stream);
}

void Deserialize(BinaryTreeNode** pRoot, istream& stream)
{
    int number;
    if(ReadStream(stream, &number))
    {
        *pRoot = new BinaryTreeNode();
        (*pRoot)->m_nValue = number;
        (*pRoot)->m_pLeft = nullptr;
        (*pRoot)->m_pRight = nullptr;

        Deserialize(&((*pRoot)->m_pLeft), stream);
        Deserialize(&((*pRoot)->m_pRight), stream);
    }

}
```

### 字符串的排列

> 输入一个字符串，打印出该字符串中字符的所有序列。

求整个字符串的排列，可以看作第一步求所有可能出现在第一个位置的字符，即把第一个字符和后面所有字符交换，第二步固定第一个字符，求后面所有字符的排列，此时仍将后面的部分看作该部分的第一个字符和后面的字符，把第一个字符逐一和后面的字符进行交换。

```C++
#include <iostream>
using namespace std;
void Permutation(char* pStr, char* pBegin)
{
    if (*pBegin=='\0')
    {
        cout << pStr << endl;
    }
    else
    {
        for (char* pCh = pBegin; *pCh != '\0'; ++pCh)
        {
            char temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
            Permutation(pStr, pBegin + 1);

            temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
        }
    }   
}

void Permutation(char* pStr)
{
    if(pStr == nullptr)
    {
        return;
    }
    Permutation(pStr, pStr);
}

int main()
{
    int n;
    cin >> n;
    char* str = new char[n+1];
    cin >> str;
    str[n] = '\0';
    Permutation(str);
    return 0;
}
```


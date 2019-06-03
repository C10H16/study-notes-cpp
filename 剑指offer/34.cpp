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
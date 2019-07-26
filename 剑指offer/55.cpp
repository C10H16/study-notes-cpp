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

int TreeDepth(BinaryTreeNode* pRoot)
{
	if(pRoot == nullptr)
		return 0;
	int nLeft = TreeDepth(pRoot->m_pLeft);
	int nRight = TreeDepth(pRoot->m_pRight);
	return(nLeft > nRight)? (nLeft+1):(nRight+1);
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

void Middle(BinaryTreeNode* pHead) // 中序遍历
{
	stack<BinaryTreeNode*> temp;
	BinaryTreeNode* p;
	getAloneLeftChild(pHead, temp);
	while(!temp.empty())
	{
		p = temp.top();
		cout << p->m_nValue << " ";
		temp.pop();
		if (p->m_pRight)
			getAloneLeftChild(p->m_pRight, temp);
	}

}


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
	Middle(pHead);
	// cout << TreeDepth(pHead);
	cout << IsBalanced(pHead);
    return 0;
}
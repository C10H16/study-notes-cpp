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

int kthNode(BinaryTreeNode* pHead, int k)
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
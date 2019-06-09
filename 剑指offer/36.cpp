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
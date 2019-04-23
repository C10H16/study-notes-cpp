#include <iostream>
#include <stack>
using namespace std;

struct ListNode
{
	int m_nKey;
	ListNode* m_pNext;
};
void AddToTail(ListNode** pHead, int value)
{
    ListNode* pNew = new ListNode();
    pNew->m_nKey = value;
    pNew->m_pNext = nullptr;
    
    if (*pHead == nullptr)
    {
        *pHead = pNew;
    }
    else
    {
        ListNode* pNode = *pHead;
        while(pNode->m_pNext != nullptr)
        {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = pNew;
    }
}

void RemoveNode(ListNode** pHead, int value)
{
    if(pHead == nullptr||*pHead ==nullptr)
        return;
    ListNode* pToBeDeleted = nullptr;
    if((*pHead)->m_nKey == value)
    {
        pToBeDeleted = *pHead;
        *pHead = (*pHead)->m_pNext;
    }
    else
    {
        ListNode* pNode = *pHead;
        while(pNode->m_pNext != nullptr && pNode->m_pNext->m_nKey!=value)
        {
            pNode = pNode->m_pNext;
        }
        if(pNode->m_pNext!=nullptr&&pNode->m_pNext->m_nKey==value)
        {
            pToBeDeleted = pNode->m_pNext;
            pNode->m_pNext = pNode->m_pNext->m_pNext;
        }
    }
    if(pToBeDeleted!=nullptr)
    {
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
    }
}

void PrintListReversingly_Iteratively(ListNode* pHead)
{
	stack<ListNode*> nodes;
	ListNode* pNode = pHead;
	while(pNode != nullptr)
	{
		nodes.push(pNode);
		pNode = pNode->m_pNext;
	}
	while (!nodes.empty())
	{
		pNode = nodes.top();
		cout << pNode->m_nKey << " ";
		nodes.pop();
	}
}
void PrintListReversingly_Recursively(ListNode* pHead)
{
	if(pHead != nullptr)
	{
		if(pHead->m_pNext != nullptr)
		{
			PrintListReversingly_Recursively(pHead->m_pNext);
		}
		cout << pHead->m_nKey << " ";
	}
}


int main()
{
	int n, temp;
	cin >> n;
	ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
	for(int i = 0; i < n; ++i)
	{
		cin >> temp;
		AddToTail(p,temp);
	}
	PrintListReversingly_Iteratively(pHead);
	cout << endl;
	PrintListReversingly_Recursively(pHead);
	return 0;	
}

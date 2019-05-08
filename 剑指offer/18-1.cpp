#include <iostream>
using namespace std;
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

void AddToTail(ListNode** pHead, int value)
{
    ListNode* pNew = new ListNode();
    pNew->m_nValue = value;
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

void PrintList(ListNode* pHead)
{
    ListNode* p = pHead;
    while (p)
    {
        cout << p->m_nValue << " ";
        p = p->m_pNext;
    }
    cout << endl;
}

void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
    if (!pToBeDeleted||!pListHead)
    {
        return;
    }
    if (pToBeDeleted->m_pNext != nullptr) // 如果不是尾节点
    {
        ListNode* pToBeDeletedNext = pToBeDeleted->m_pNext;
        pToBeDeleted->m_nValue = pToBeDeleted->m_pNext->m_nValue;
        pToBeDeleted->m_pNext = pToBeDeleted->m_pNext->m_pNext;

        delete pToBeDeletedNext;
        return;
    }
    else if (pToBeDeleted == *pListHead) // 要删除的节点是尾节点又是头节点（即链表只有一个节点）
    {
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        *pListHead = nullptr;
        return;
    }
    else
    {
        ListNode* pNode = *pListHead;
        while (pNode->m_pNext != pToBeDeleted)
        {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = nullptr;
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        return;
    }
    
}

int main()
{
	int n, temp;
    cin >> n;
    while (n<3)
    {
        cout << "n must bigger than 3";
        cin >> n;
    }
	ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
    ListNode* d1, *d2, *d3,*ptemp;
    
	for(int i = 0; i < n; ++i)
	{
		cin >> temp;
		AddToTail(p,temp);
	}
    ptemp = pHead;
    for (int i = 0; i < n; ++i)
    {
        if (i == 0)
            d3 = ptemp;
        if (i == n/2)
            d1 = ptemp;
        if (i == n-1)
            d2 = ptemp;
        ptemp = ptemp->m_pNext;
    }
    
    PrintList(pHead);
    DeleteNode(p,d1);
	PrintList(pHead);
    DeleteNode(p,d2);
    PrintList(pHead);
    DeleteNode(p,d3);
    PrintList(pHead);
    d1 = nullptr;
    d2 = nullptr;
    d3 = nullptr;
    ptemp = pHead;
    p = nullptr;
    while (ptemp)
    {
        ptemp = ptemp->m_pNext;
        delete pHead;
        pHead = ptemp;
    }
    // ptemp = nullptr;
    pHead = nullptr;
	return 0;	
}
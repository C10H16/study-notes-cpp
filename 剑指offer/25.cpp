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

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr)
        return pHead2;
    else if (pHead2 == nullptr)
        return pHead1;
    
    ListNode* pMergeHead = nullptr;
    if (pHead1->m_nValue < pHead2->m_nValue)
    {
        pMergeHead = pHead1;
        pMergeHead->m_pNext = Merge(pHead1->m_pNext, pHead2);
    }
    else
    {
        pMergeHead = pHead2;
        pMergeHead->m_pNext = Merge(pHead1, pHead2->m_pNext);
    }
    return pMergeHead;
    
}

int main()
{
    int n1,n2;
    cin >> n1;
    ListNode* pHead1 = nullptr;
	ListNode** p1;
	p1 = &pHead1;
    int temp;
    for (int i = 0; i < n1; ++i)
    {
        cin >> temp;
        AddToTail(p1, temp);
    }
    cin >> n2;
    ListNode* pHead2 = nullptr;
    ListNode** p2;
    p2 = &pHead2;
    for (int i = 0; i < n2; ++i)
    {
        cin >> temp;
        AddToTail(p2, temp);
    }
    ListNode* pMerge = Merge(pHead1, pHead2);
    ListNode* p=pMerge;
    while (p)
    {
        cout << p->m_nValue << " ";
        p = p->m_pNext;
    }

    
    return 0;
}
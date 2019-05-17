#include <iostream>
using namespace std;
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* ReverseList(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;
    ListNode* pReversedHead = nullptr;
    ListNode* pNode = pHead;
    ListNode* pPrev = nullptr;
    ListNode* pNext = nullptr;
    while (pNode != nullptr)
    {
        pNext = pNode->m_pNext;
        
        if (pNext == nullptr)
        {
            pReversedHead = pNode;
        }
        pNode->m_pNext = pPrev;

        pPrev = pNode;
        pNode = pNext;
    }
    return pReversedHead;

}

void AddToHead(ListNode** pHead, int value)
{
    ListNode* pNew = new ListNode();
    pNew->m_nValue = value;
    pNew->m_pNext = nullptr;
    ListNode* pNode = *pHead;
    if (pNode != nullptr)
        pNew->m_pNext = pNode;
    *pHead = pNew;

}

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

int main()
{
    int n;
    cin >> n;
    ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
    int temp;
    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        AddToTail(p, temp);
    }
    
    ListNode* re = ReverseList(pHead);
    pHead = re;
    while (re)
    {
        cout << re->m_nValue << " ";
        re = re->m_pNext;
    }
    
    return 0;
}
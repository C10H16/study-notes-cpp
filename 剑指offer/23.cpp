#include <iostream>
using namespace std;
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* MeetingNode(ListNode* pHead)
{
    if (pHead == nullptr)
    {
        return nullptr;
    }
    ListNode* pSlow = pHead->m_pNext;
    if (pSlow == nullptr)
        return nullptr;
    ListNode* pFast = pSlow->m_pNext;
    while (pFast != nullptr && pSlow != nullptr)
    {
        if (pFast == pSlow)
        {
            return pFast;
        }
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;
        if (pFast != nullptr)
        {
            pFast = pFast->m_pNext;
        }
    }
    return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    ListNode* meetingNode = MeetingNode(pHead);
    if (meetingNode == nullptr)
    {
        return nullptr;
    }

    int nodesInLoop = 1;
    ListNode* pNode1 = meetingNode;
    while(pNode1->m_pNext != meetingNode)
    {
        pNode1 = pNode1->m_pNext;
        ++nodesInLoop;
    }
    pNode1 = pHead;
    for(int i = 0; i < nodesInLoop; ++i)
    {
        pNode1 = pNode1->m_pNext;
    }
    ListNode* pNode2 = pHead;
    while(pNode1 != pNode2)
    {
        pNode1 = pNode1->m_pNext;
        pNode2 = pNode2->m_pNext;
    }
    return pNode1;
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
    int n, k;
    cin >> n >> k;
    ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
    int temp;
    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        AddToTail(p, temp);
    }
    ListNode* start = nullptr;
    ListNode* tail = pHead;
    for (int i = 1; i < n; ++i)
    {
        if (i==k)
            start = tail;
        tail = tail->m_pNext;
    }
    if (k==n)
        tail->m_pNext = tail;
    else
        tail->m_pNext = start;
    
    ListNode* re = EntryNodeOfLoop(pHead);
    if (re)
    {
        cout << re->m_nValue << endl;
    }
    else
    {
        cout << "Not found" << endl;
    }
    
    return 0;
}
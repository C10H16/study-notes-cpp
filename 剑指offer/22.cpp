#include <iostream>
using namespace std;
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
    if (pListHead == nullptr || k == 0)
    {
        return nullptr;
    }
    ListNode* pAhead = pListHead;
    ListNode* pBehind = nullptr;
    for (int i = 0; i < k-1; ++i)
    {
        if (pAhead->m_pNext != nullptr)
        {
            pAhead = pAhead->m_pNext;
        }
        else
        {
            return nullptr;
        }
    }
    pBehind = pListHead;
    while (pAhead->m_pNext != nullptr)
    {
        pAhead = pAhead->m_pNext;
        pBehind = pBehind->m_pNext;
    }
    return pBehind;
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
    ListNode* re = FindKthToTail(pHead, k);
    if (re)
        cout << re->m_nValue << endl;
    else
    {
        cout << "Error";
    }
    return 0;
}
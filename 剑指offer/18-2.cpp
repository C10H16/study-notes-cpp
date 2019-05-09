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

void deleteDuplication(ListNode** pHead)
{
    if(pHead == nullptr || *pHead == nullptr)
        return;
    ListNode* pPreNode = nullptr;
    ListNode* pNode = *pHead;
    while (pNode != nullptr)
    {
        ListNode *pNext = pNode->m_pNext;
        bool needDelete = false;
        if(pNext != nullptr && pNext->m_nValue == pNode->m_nValue)
            needDelete = true;
        if(!needDelete)
        {
            pPreNode = pNode;
            pNode = pNode->m_pNext;
        }
        else
        {
            int value = pNode->m_nValue;
            ListNode* pToBeDel = pNode;
            while(pToBeDel != nullptr && pToBeDel->m_nValue == value)
            {
                pNext = pToBeDel->m_pNext;

                delete pToBeDel;
                pToBeDel = nullptr;
                pToBeDel = pNext;
            }
            if (pPreNode == nullptr)
            {
                *pHead = pNext;
            }
            else
            {
                pPreNode->m_pNext = pNext;
            }
            pNode = pNext;
        }
        
    }
}

int main()
{
	int n, temp;
    cin >> n;
	ListNode* pHead = nullptr;
	ListNode** p;
	p = &pHead;
    ListNode* ptemp;
	for(int i = 0; i < n; ++i)
	{
		cin >> temp;
		AddToTail(p,temp);
	}
    PrintList(pHead);
    deleteDuplication(p);
    PrintList(pHead);
    ptemp = pHead;
    p = nullptr;
    while (ptemp)
    {
        ptemp = ptemp->m_pNext;
        delete pHead;
        pHead = ptemp;
    }
	return 0;	
}
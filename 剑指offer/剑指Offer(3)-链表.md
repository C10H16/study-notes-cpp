## 链表

由于没有闲置内存，链表的空间效率比数组要高。但是由于其空间不连续，因此链表的查找效率为O(n)

对于单项链表：

```C++
// 结点定义
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};
// 在链表末尾插入新节点
void AddToTail(ListNode** pHead, int value) // 向空表中插入新节点时，会更改pHead，因此pHead要为指针的指针。否则出了这个函数pHead还是一个空指针。
{
    ListNode* pNew = newListNode();
    pNew->m_nValue = value;
    pNew->m_pNext = nullptr;
    
    if (pHead == nullptr)
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

// 找到含有某个值的节点并删除
void RemoveNode(ListNode** pHead, int value)
{
    if(pHead == nullptr||*pHead ==nullptr)
        return;
    ListNode* pToBeDeleted = nullptr;
    if((*pHead)->m_nValue == value)
    {
        pToBeDeleted = *pHead;
        *pHead = (*pHead)->m_pNext;
    }
    else
    {
        ListNode* pNode = *pHead;
        while(pHead->m_pNext!=nullptr&&pNode->m_pNext->m_nValue!=value)
        {
            pNode = pNode->m_pNext;
        }
        if(pNode->m_pNext!=nullptr&&pNode->m_pNext->m_pValue==value)
        {
            pToBeDeleted = pNode->m_pNext;
            pNode->m_pNext = pNode->m_pNext->m_pNext;
        }
    }
    if(pToBeDeleted!=nullptr)
    {
        delete pToBedeleted;
        pToBeDeleted = nullptr;
    }
}
```

### 从尾到头打印链表

> 输入一个链表的头节点，从尾到头反过来打印每个节点的值。链表的定义如下：

```C++
struct ListNode
{
    int m_nKey;
    ListNode* m_pNext;
};
```

访问链表的节点顺序是从前往后的，而打印节点的值的顺序是从后往前的，这时典型的先进后出。因此，可以使用栈来实现。而递归在本质上就是一个栈结构，因此也可以使用递归来实现。但是，当链表的长度很长时，使用递归可能会导致函数调用栈溢出。
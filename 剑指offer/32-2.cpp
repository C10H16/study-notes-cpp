#include <iostream>
#include <queue>
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

void Print(BinaryTreeNode* pRoot)
{
    if (pRoot==nullptr)
        return;
    stack<BinaryTreeNode*> levels[2];
    int current = 0;
    int next = 1;

    levels[current].push(pRoot);
    while (!levels[0].empty()||!levels[1].empty())
    {
        BinaryTreeNode* pNode = levels[current].top();
        levels[current].pop();

        cout << pNode->m_nValue << " ";

        if (current==0)
        {
            if (pNode->m_pLeft!=nullptr)
                levels[next].push(pNode->m_pLeft);
            if (pNode->m_pRight!=nullptr)
                levels[next].push(pNode->m_pRight);
        }
        else
        {
            if (pNode->m_pRight != nullptr)
                levels[next].push(pNode->m_pRight);
            if (pNode->m_pLeft != nullptr)
                levels[next].push(pNode->m_pLeft);
        }

        if (levels[current].empty())
        {
            cout << endl;
            current = 1 - current;
            next = 1 - next;
        }
        
    }
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
    cout << endl;
    Print(pHead);
    return 0;
}
#include <iostream>
#include <queue>
using namespace std;
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pParent;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

BinaryTreeNode* InorderNext(BinaryTreeNode* node) // 寻找给定节点中序遍历的下一个节点 
{
	if (node == nullptr)
		return nullptr;
	if (node->m_pRight != nullptr)
	{
		BinaryTreeNode* p = node->m_pRight;
		while(p != nullptr)
		{
			p = p->m_pLeft;
		}
		return p->m_pParent;
	}
	else if(node->m_pParent != nullptr)
	{
		BinaryTreeNode* p2 = node;
		while (p2->m_pParent!=nullptr&&p2->m_pParent->m_pRight == p2)
		{
			p2 = p2->m_pParent;
		}
		return p2->m_pParent;
	}
}

void addLeftCh(BinaryTreeNode* parent,int left) // 添加左孩子 
{
	parent->m_pLeft = new BinaryTreeNode;
	parent->m_pLeft->m_nValue = left;
	parent->m_pLeft->m_pParent = parent;
	parent->m_pLeft->m_pLeft = nullptr;
	parent->m_pLeft->m_pRight = nullptr;
}

void addRightCh(BinaryTreeNode* parent,int right) // 添加右孩子 
{
	parent->m_pRight = new BinaryTreeNode;
	parent->m_pRight->m_nValue = right;
	parent->m_pRight->m_pParent = parent;
	parent->m_pRight->m_pLeft = nullptr;
	parent->m_pRight->m_pRight = nullptr;
}

void printTree (BinaryTreeNode* root) // 打印树 
{
	queue<BinaryTreeNode*> node;
	cout << root->m_nValue << " ";
	node.push(root->m_pLeft);
	node.push(root->m_pRight);
	while(!node.empty())
	{
		if (node.front() != nullptr)
		{
			cout << node.front()->m_nValue << " ";
			node.push(node.front()->m_pLeft);
			node.push(node.front()->m_pRight);
			node.pop();
		}
		else
		{
			cout << "X ";
			node.pop();
		}
	}
}
int main()
{
	BinaryTreeNode* head = new BinaryTreeNode;
	head->m_nValue = 1;
	head->m_pParent = nullptr;
	head->m_pLeft = nullptr;
	head->m_pRight = nullptr;
	queue<BinaryTreeNode*> temp;
	temp.push(head);
	int n,x;
	cin >> n;
	int* val = new int[n];
	int i = 0;
	for(i = 0; i < n; ++i)
	{
		cin >> val[i];	
	}
	cin >> x;
	head->m_nValue = val[0];
	BinaryTreeNode* pNode;
	BinaryTreeNode* find = nullptr;
	i = 1;
	while(i < n && (!temp.empty())) // 构造树 
	{
		pNode = temp.front();
		if (val[i]!=0)
		{
			addLeftCh(pNode,val[i]);
			temp.push(pNode->m_pLeft);
			if (val[i]==x)
				find = pNode->m_pLeft;
		}
		if (val[i+1]!=0)
		{
			addRightCh(pNode,val[i+1]);
			temp.push(pNode->m_pRight);
			if (val[i+1]==x)
				find = pNode->m_pRight;
		}
		temp.pop();
		i+=2;
	}
	printTree(head);
	cout << endl;
	if (find == nullptr)
		cout << "There is no node has a value " << x << endl;
	else
	{
		cout << "The next of " << find->m_nValue << " is: ";
		cout << InorderNext(find)->m_nValue << endl;
	}
	return 0;
 
}
 

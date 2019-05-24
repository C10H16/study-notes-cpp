#include <iostream>
#include <queue>
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

bool isSymmetrical(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot1 == nullptr && pRoot2 == nullptr)
	{
		return true;
	}
	if (pRoot1 == nullptr || pRoot2 == nullptr)
	{
		return false;
	}
	if (pRoot1->m_nValue != pRoot2->m_nValue)
	{
		return false;
	}
	return isSymmetrical(pRoot1->m_pLeft, pRoot2->m_pRight)
		&& isSymmetrical(pRoot1->m_pRight, pRoot2->m_pLeft);
}

bool isSymmetrical(BinaryTreeNode* pRoot)
{
	return isSymmetrical(pRoot, pRoot);
}

bool Mirror(BinaryTreeNode* root)
{
	queue<BinaryTreeNode*> node;
	queue<BinaryTreeNode*> mirror;

	node.push(root->m_pLeft);
	node.push(root->m_pRight);
	mirror.push(root->m_pRight);
	mirror.push(root->m_pLeft);
	while(!node.empty())
	{
		if (node.front()==nullptr && mirror.front()==nullptr)
		{
			node.pop();
			mirror.pop();
		}
		else if (node.front()!=nullptr&&mirror.front()!=nullptr&&node.front()->m_nValue==node.front()->m_nValue)
		{
			node.push(node.front()->m_pLeft);
			node.push(node.front()->m_pRight);
			mirror.push(mirror.front()->m_pRight);
			mirror.push(mirror.front()->m_pLeft);
			node.pop();
			mirror.pop();
		}
		else
		{
			return false;
		}
	}
	return true;
}


int main()
{
	BinaryTreeNode* head1 = new BinaryTreeNode;
	head1->m_nValue = 0;
	head1->m_pLeft = nullptr;
	head1->m_pRight = nullptr;
	queue<BinaryTreeNode*> temp;
	temp.push(head1);
	int n1, n2;
	cin >> n1;
	int* val1 = new int[n1];
	int i = 0;
	for(i = 0; i < n1; ++i)
	{
		cin >> val1[i];	
	}
	head1->m_nValue = val1[0];
	BinaryTreeNode* pNode;
	i = 1;
	while(i < n1 && (!temp.empty())) // 构造树 
	{
		pNode = temp.front();
		if (val1[i]!=0)
		{
			addLeftCh(pNode,val1[i]);
			temp.push(pNode->m_pLeft);
		}
		if (val1[i+1]!=0)
		{
			addRightCh(pNode,val1[i+1]);
			temp.push(pNode->m_pRight);
		}
		temp.pop();
		i+=2;
	}

	cout << endl;
	cout << isSymmetrical(head1) << endl;
	cout << Mirror(head1);
	return 0;
}
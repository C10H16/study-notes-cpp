#include <iostream>
#include <queue>
using namespace std;
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

void MirrorRecursively(BinaryTreeNode* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}
	if (pNode->m_pLeft==nullptr && pNode->m_pRight==nullptr)
	{
		return;
	}
	BinaryTreeNode* pTemp = pNode->m_pLeft;
	pNode->m_pLeft = pNode->m_pRight;
	pNode->m_pRight = pTemp;

	if (pNode->m_pLeft)
	{
		MirrorRecursively(pNode->m_pLeft);
	}
	if (pNode->m_pRight)
	{
		MirrorRecursively(pNode->m_pRight);
	}
}

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

void printMirror (BinaryTreeNode* root) // 打印树 
{
	queue<BinaryTreeNode*> node;
	cout << root->m_nValue << " ";
	node.push(root->m_pRight);
	node.push(root->m_pLeft);
	while(!node.empty())
	{
		if (node.front() != nullptr)
		{
			cout << node.front()->m_nValue << " ";
			node.push(node.front()->m_pRight);
			node.push(node.front()->m_pLeft);
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

	printTree(head1);
    cout << endl;
	printMirror(head1);
	cout << endl;
	MirrorRecursively(head1);
	printTree(head1);
	return 0;
}
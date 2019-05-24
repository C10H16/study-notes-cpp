# 剑指Offer

## 解决面试题的思路

### 二叉树的镜像

> 完成一个函数，输入一个二叉树，该函数输出它的镜像。二叉树节点的定义如下：

```C++
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
}
```

通过观察可以发现，对一棵树求镜像，只需要先序遍历这棵树的每个节点，如果遍历到的节点有子节点，则交换它的两个子节点。当交换玩所有非叶子节点的子节点之后，得到的即为树的镜像。

另一种方式是，从根节点开始，节点的右孩子、左孩子依次存入队列，再从队列中读取节点，依次向队列中存入该节点的有孩子、左孩子，直到队列为空。需要额外空间但是不会改变原来的树。

```C++
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
```

### 对称的二叉树

> 实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。

对二叉树按根节点->左孩子->右孩子和根节点->右孩子->左孩子的顺序遍历，如果遍历顺序相同，则为对称的。遍历时，需要考虑为空的节点。也可使用上一题输出镜像的方法对二叉树进行遍历，与正常输出的顺序进行比较。

```C++
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
```


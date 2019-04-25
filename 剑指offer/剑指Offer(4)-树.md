# 树

## 二叉树

二叉树是一种特殊的树结构。二叉树中，每个节点最多只能有两个子节点。

二叉树通常有三种遍历方式。设树的左、右、根节点分别表示为 L、R、X

- 先序遍历：X->L->R
- 中序遍历：L->X->R
- 后序遍历：L->R->X

假设有这样一棵二叉树

```
    1
   / \
  2   3
 /\   /\
4  5 6  7
```

其先序遍历为：1->2->4->5->3->6->7

其中序遍历为：4->2->5->1->6->3->7

其后序遍历为：4->5->2->6->7->3->1

## 堆和红黑树

### 堆

堆分为最大堆和最小堆，最大堆中根节点的值最大，最小堆中根节点最小。

### 红黑树

红黑树是把树中的节点定义成红黑两种颜色，并通过规则确保根节点到叶节点的最常路径的长度不超过最短路径的两倍。

## 相关题目

### 重建二叉树

> 输入某二叉树的先序遍历和中序遍历，重建该二叉树。假设输入的先序遍历和中序遍历中都不含重复的数字。返回二叉树的头节点。

```C++
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
}
```

观察上面的先序遍历和中序遍历可以发现，先序遍历的第一个为根节点，而中序遍历的根节点在其左子树和右子树中间。因此，可以根据先序遍历找出这棵树的根节点，再从中序遍历中找出其左子树和右子树。对其左右子树做同样的操作，即可找出其左右子树的左右子树。

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
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
	// 先序遍历的第一个值为根节点 
	int rootValue = startPreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = nullptr;
	
	if(startPreorder == endPreorder)
	{
		if(startInorder == endInorder && *startPreorder == * startInorder)
			return root;
		else
			throw ("Invalid input.");
	}
	// 在中序遍历中寻找根节点
	int* rootInorder = startInorder;
	while(rootInorder <= endInorder && *rootInorder != rootValue)
		++ rootInorder;
	if (rootInorder == endInorder && *rootInorder != rootValue)
		throw ("Invalid input.");
	int leftLength = rootInorder - startInorder;
	int* leftPreorderEnd = startPreorder + leftLength;
	if (leftLength > 0)
	{
		// 构建左子树
		root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1); 
	}
	if (leftLength < endPreorder - startPreorder)
	{
		// 构建右子树
		root->m_pRight = ConstructCore(leftPreorderEnd + 1,endPreorder, rootInorder + 1, endInorder); 
	}
	return root; 
}


BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
	if(preorder == nullptr || inorder == nullptr || length <=0)
	{
		return nullptr;
	}
	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

void printTree (BinaryTreeNode* root)
{
	queue<BinaryTreeNode*> node;
	cout << root->m_nValue << endl;
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
	int n;
	cin >> n;
	int* preorder = new int[n];
	int* inorder = new int[n];
	for(int i = 0; i < n; ++i)
	{
		cin >> preorder[i];
	}
	for(int i = 0; i < n; ++i)
	{
		cin >> inorder[i];
	}
	BinaryTreeNode* root = Construct(preorder, inorder, n);
	printTree(root);
	return 0;
}
```

### 二叉树的下一节点

> 给定一棵二叉树和其中的一个节点，如何找出中序遍历序列的下一个节点？树中的节点除了有两个分别指向左右子树的指针，还有一个指向父节点的指针。

如果一个节点有右子树，那么其中序遍历的下一个节点就是其右子树的最左子节点。

如果一个节点是某一结点的左子节点，那么其中序遍历的下一个节点就是其根节点。否则，就沿着其父节点遍历，直至找到一个为某一结点左孩子的节点，返回其根节点。

```C++
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
```




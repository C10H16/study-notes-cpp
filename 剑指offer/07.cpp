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

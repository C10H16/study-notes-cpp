#include <iostream>
#include <queue>
using namespace std;
struct BinaryTreeNode
{
	double m_dbValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

inline bool equal(double n1, double n2)
{
    return (n1-n2 < 0.0000001 && n1-n2 > -0.0000001);
}

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    if (pRoot2 == nullptr)
    {
        return true;
    }
    if (pRoot1 == nullptr)
    {
        return false;
    }
    if (!(equal(pRoot1->m_dbValue, pRoot2->m_dbValue)))
    {
        return false;
    }
    return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft)&&
           DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

// 查找树A中与树B根节点相等的节点
bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    bool result = false;
    if (pRoot1 != nullptr && pRoot2 != nullptr)
    {
        if(equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
        {
            result = DoesTree1HaveTree2(pRoot1, pRoot2);
        }
        if(!result)
        {
            result = HasSubtree(pRoot1->m_pLeft, pRoot2);
        }
        if(!result)
        {
            result = HasSubtree(pRoot1->m_pRight, pRoot2);
        }
    }
    return result;
}

void addLeftCh(BinaryTreeNode* parent,int left) // 添加左孩子 
{
	parent->m_pLeft = new BinaryTreeNode;
	parent->m_pLeft->m_dbValue = left;
	parent->m_pLeft->m_pLeft = nullptr;
	parent->m_pLeft->m_pRight = nullptr;
}

void addRightCh(BinaryTreeNode* parent,int right) // 添加右孩子 
{
	parent->m_pRight = new BinaryTreeNode;
	parent->m_pRight->m_dbValue = right;
	parent->m_pRight->m_pLeft = nullptr;
	parent->m_pRight->m_pRight = nullptr;
}

void printTree (BinaryTreeNode* root) // 打印树 
{
	queue<BinaryTreeNode*> node;
	cout << root->m_dbValue << " ";
	node.push(root->m_pLeft);
	node.push(root->m_pRight);
	while(!node.empty())
	{
		if (node.front() != nullptr)
		{
			cout << node.front()->m_dbValue << " ";
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
	BinaryTreeNode* head1 = new BinaryTreeNode;
	head1->m_dbValue = 0.0;
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
	head1->m_dbValue = val1[0];
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

    while(!temp.empty())
    {
        temp.pop();
    }
    BinaryTreeNode* head2 = new BinaryTreeNode;
	head2->m_dbValue = 0.0;
	head2->m_pLeft = nullptr;
	head2->m_pRight = nullptr;
    cin >> n2;
	int* val2 = new int[n2];
	for(i = 0; i < n2; ++i)
	{
		cin >> val2[i];	
	}
	head2->m_dbValue = val2[0];
    temp.push(head2);
	i = 1;
	while(i < n2 && (!temp.empty())) // 构造树 
	{
		pNode = temp.front();
		if (val2[i]!=0)
		{
			addLeftCh(pNode,val2[i]);
			temp.push(pNode->m_pLeft);
		}
		if (val2[i+1]!=0)
		{
			addRightCh(pNode,val2[i+1]);
			temp.push(pNode->m_pRight);
		}
		temp.pop();
		i+=2;
	}
	printTree(head1);
    cout << endl;
    printTree(head2);
    cout << endl;
    cout << HasSubtree(head1, head2);

	return 0;
}
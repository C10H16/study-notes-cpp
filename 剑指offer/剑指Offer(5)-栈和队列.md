# 栈和队列

栈：先进后出，通常不考虑排序。需要 O(n) 的时间才能找到其中最大或最小的元素。如果想在 O(1) 时间内找到栈的最小或最大值则需要对栈进行特殊的设计。

队列：先进先出

### 用两个栈实现队列

> 用两个栈实现一个队列，队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead，分别在队列尾部插入节点和在队列头部删除节点的功能。

```C++
template <typename T> class CQueue
{
public:
    CQueue(void);
    ~CQueue(void);
    void appendTail(const T& node);
    T deleteHead();
private:
    stack<T> stack1;
    stack<T> stack2;
}
```

将元素插入队列中时，可以直接插入stack1。假设向stack1中插入了1，2，3，那么此时stack1的栈顶为3。当需要删除队列头部元素时，可以将stack1中的元素依次弹出并压入stack2，此时，1位于stack2的栈顶，将其弹出即删除了该元素。继续删队列头部元素，继续弹出stack2的栈顶即可。当stack2为空时，可以将stack1中的元素全部弹出并压入stack2，此时stack2顶部的元素即为队列头部元素。

```C++
template <typename T> class CQueue
{
public:
    CQueue(void);
    ~CQueue(void);
    void appendTail(consst T& node);
    T deleteHead();
private:
    stack<T> stack1;
    stack<T> stack2;
}
```

### 两个队列实现一个栈

初始时，可以将元素放入任意一个队列。之后添加元素时，将元素放进非空的队列。需要出栈时，则需要弹出该队列队尾的元素。可以将该队列队尾前的所有元素按顺序放入另一队列，再将队尾元素删除即可。

```C++
#include <iostream>
#include <queue>
using namespace std;
template <typename T> class CStack
{
public:
    CStack(void){} 
    ~CStack(void){}
    void pushStack(const T& node);
    T popStack();
private:
    queue<T> queue1;
    queue<T> queue2;
};

template <typename T> void CStack<T>::pushStack(const T& node)
{
	if (queue1.empty()) 
		queue2.push(node);
	else
		queue1.push(node);
}
template <typename T> T CStack<T>::popStack()
{
	T re;
	if (queue1.empty() && queue2.empty())
		throw ("Stack is empty!");
	else if (queue1.empty())
	{
		while (queue2.size()>1)
		{
			queue1.push(queue2.front());
			queue2.pop();
		}
		re = queue2.front();
		queue2.pop();
		return re;
	}
	else
	{
		while (queue1.size()>1)
		{
			queue2.push(queue1.front());
			queue1.pop(); 
		}
		re = queue1.front();
		queue1.pop();
		return re;
	}
}
int main()
{
	CStack<int> a;
	a.pushStack(1);
	a.pushStack(2);
	cout << a.popStack() << endl;
	a.pushStack(3);
	cout << a.popStack() << endl;
	a.pushStack(4);
	a.pushStack(5);
	cout << a.popStack() << endl;
	cout << a.popStack() << endl;
	cout << a.popStack() << endl;
	return 0;
}
```


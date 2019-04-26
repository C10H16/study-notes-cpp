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

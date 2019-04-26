#include <iostream>
#include <stack> 
using namespace std;
template <typename T> class CQueue
{
public:
    CQueue(void){	}
    ~CQueue(void){ }
    void appendTail(const T& node);
    T deleteHead();
private:
    stack<T> stack1;
    stack<T> stack2;
};
template <typename T>
void CQueue<T>::appendTail(const T& node)
{
	stack1.push(node);
}
template <typename T>
T CQueue<T>::deleteHead()
{
	if(stack2.empty())
	{
		while(!stack1.empty())
		{
			stack2.push(stack1.top());
			stack1.pop();
		}
	}
	if (stack2.empty())
		throw ("Queue is empty!");
	T re = stack2.top();
	stack2.pop();
	return re;
}


int main()
{
	CQueue<int> a;
	a.appendTail(1);
	a.appendTail(2);
	a.appendTail(3);
	cout << a.deleteHead() << endl;
	cout << a.deleteHead() << endl;
	a.appendTail(4);
	a.appendTail(5);
	cout << a.deleteHead() << endl;
	cout << a.deleteHead() << endl;
	cout << a.deleteHead() << endl;
	return 0;
}

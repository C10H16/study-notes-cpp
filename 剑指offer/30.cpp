#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;
template <typename T>
class StackWithMin
{
public:
    void push(const T& value);
    void pop();
    const T& min()const;
private:
    stack<T> m_data;
    stack<T> m_min;
};
template <typename T> void StackWithMin<T>::push(const T& value)
{
	m_data.push(value);
    if (m_min.empty()||value<m_min.top())
    {
        m_min.push(value);
    }    
    else
    {
        m_min.push(m_min.top());
    }
    
}

template <typename T> void StackWithMin<T>::pop()
{
    assert(m_data.size()>0&&m_min.size()>0);
    m_data.pop();
    m_min.pop();
}

template<typename T> const T& StackWithMin<T>::min() const
{
    assert(m_data.size()>0&&m_min.size()>0);
    return m_min.top();
}
int main()
{
    StackWithMin<int> test;
    int n = 0;
    cin >> n;
    int temp = 0;
    for(int i = 0; i < n; ++i)
    {
        cin >> temp;
        test.push(temp);
        cout << test.min();
    }
    for(int i = 0; i < n-1; ++i)
    {
        test.pop();
        cout << test.min();
    }
    return 0;
}
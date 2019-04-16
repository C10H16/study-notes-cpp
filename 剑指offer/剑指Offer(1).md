## 剑指Offer

### 1 赋值运算符函数

为下面的类添加赋值运算符函数

```C++
class CMystring
{
public:
    CMystring(char* pData = nullptr);
    CMystring(const CMystring& str);
    ~CMystring(void);
private:
    char* m_pData;
}

// answer
CMystring& CMystring:: operator = (const CMystring& str)
// 返回实例自身的的引用，使得 str1 = str2 = str3 的连续赋值得以实现。
// 参数为常量引用，提高代码效率。因为并不会改变传入参数的值，因此为 const
{
    if (this != &str) // 判断如果参数和实例相同则不执行操作
    {
        CMystring temp(str);
        char *pTemp = temp.m_pData;
        temp.m_pData = m_pData;
        m_pData = pTemp;
    }
    // temp 为局部变量，函数运行结束后会自动释放内存。
    return *this;
}

// another answer
CMystring & CMystring::operator = (const CMystring& str)
{
    if (this == &str) // 判断如果传入参数和当前实例是否为同一个实例。如果是则不执行操作。
        // 否则，当释放当前实例的内存时，传入参数的内存也被释放，会导致严重的问题。
        return *this;
    delete []m_pData;
    m_pData = nullptr;
    //释放实例自身已有的空间防止造成内存泄露
    m_pData = new char[strlen(str.m_pData)+1]; // 如果空间不足导致 new char 抛出异常，则会导致 m_pData 成为空指针，会导致程序崩溃，违背了异常安全性（Exception Safety）原则。
    strcpy(m_pData, str.m_pData);
    return *this;
}
```

### 实现 Singleton 模式

单例模式应该提供一个全局的方法以便获取该实例。

构造函数应为私有。

```C++
// ver1
class singleton
{
public:
    static singleton& instance()
    {
        if (instance_ == NULL)
            instance_ = new singleton();
        return *instance_;
    }
private:
    singleton(){};
    static singleton* instance_;
};
// ver2
class singleton
{
public:
    static singleton& instance()
    {
        static singleton *instance_ = new singleton();
        return *instance_;
    }
private:
    singleton(){}
};
```

C++ 保证一个占静态变量的初始化只进行一次，哪怕在多线程下也是如此。因此 ver2 是安全的，之前的版本不是。


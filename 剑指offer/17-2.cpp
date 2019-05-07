#include <iostream>
using namespace std;

void printNum(int *num,int n)
{
    int i = n-1;
    while (num[i]==0)
    {
        --i;
    }
    for(i; i >= 0; --i)
    {
        cout << num[i];
    }
    cout << '\t';
}

void Print1ToMaxOfNDigitsCore(int index, int* num, int n)
{
    if(index<0)
    {
        printNum(num,n);
        return;
    }
    for(int i = 0; i < 10; ++i)
    {
        num[index] = i;
        Print1ToMaxOfNDigitsCore(index-1, num, n);
    }
}

void print1ToMaxOfNDigits(int n)
{
    int *num = new int[n];
    for(int i = 0; i < n; ++i)
    {
        num[i] = 0;
    }
    Print1ToMaxOfNDigitsCore(n-1,num,n);
    delete[] num;
}


int main()
{
    int n;
    cin >> n;
    print1ToMaxOfNDigits(n);
    return 0;
}
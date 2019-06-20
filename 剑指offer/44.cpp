#include <iostream>
using namespace std;


int myPow(int x, int y)
{
    int re = x;
    for (int i = 1; i < y; ++i)
    {
        re *= x;
    }
    return re;
}
int countOfIntegers(int digits)
{
    if (digits == 1)
        return 10;
    int count = myPow(10, digits-1);
    return 9*count;
}

int beginNumber(int digits)
{
    if (digits == 1)
        return 0;
    return myPow(10, digits-1);
}

int digitAtIndex(int index, int digits)
{
    int number = beginNumber(digits) + index / digits;
    int indexFromRight= digits- index % digits;
    for (int i = 1; i < indexFromRight; ++i)
        number /= 10;
    return number % 10;
}
int digitAtIndex(int index)
{
    if (index < 0)
        return -1;
    int digits = 1;
    while(true)
    {
        int numbers = countOfIntegers(digits);
        if(index < numbers * digits)
            return digitAtIndex(index,digits);
        index -= digits * numbers;
        digits++;
    }
    return -1;
}

int main()
{
    int n;
    cin >> n;
    cout << beginNumber(2) << endl << beginNumber(3) << endl << beginNumber(4) << endl; 
    cout << countOfIntegers(2) << endl << countOfIntegers(3) << endl << countOfIntegers(4) << endl;
    cout << digitAtIndex(n);
    return 0;
}
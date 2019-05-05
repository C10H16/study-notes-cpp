#include <iostream>
#include <math.h>
using namespace std;
int maxProduct_1(int length) //动态规划
{
    if (length < 2)
    return 0;
    else if(length == 2)
    return 1;
    else if(length ==3)
    return 2;

    int *products = new int[length+1]; // 存储最优解
    products[0] = 0;
    products[1] = 1;
    products[2] = 2;
    products[3] = 3;

    int max = 0;
    for(int i = 4; i <= length; ++i)
    {
        max = 0;
        for(int j = 1; j <= i/2; ++j)
        {
            int product = products[j]*products[i-j];
            if (product > max)
            {
                max = product;
            }
        }
        products[i] = max;
    }
    max = products[length];
    delete[] products;
    return max;
}

int maxProduct_2(int length) // 贪婪算法
{
    if (length < 2)
        return 0;
    else if(length == 2)
        return 1;
    else if(length ==3)
        return 2;

    int timesOf3 = length/3;
    if (length - 3*timesOf3 == 1)
    {
        timesOf3 -= 1;
    }
    int timesOf2 = (length - 3*timesOf3)/2;
    return (int) (pow(3,timesOf3))*(int)(pow(2,timesOf2));
}
int main()
{
    int length;
    cin >> length;
    cout << "method_1: " << maxProduct_1(length) << endl;
    cout << "method_2: " << maxProduct_2(length) << endl;
    return 0; 
}
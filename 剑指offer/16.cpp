#include <iostream>
using namespace std;
bool InvalidInput = false;
double Power(double base, int exponent)
{
    double result = 1.0;
    if (base > 0 || base < 0)
    {
        bool negative = false;
        int absExponent = exponent;
        if (exponent==0)
        {
            return 1.0;
        }
        else if(exponent < 0)
        {
            negative = true;
            absExponent = -exponent;
        }
        for (int i = 0; i < absExponent; ++i)
        {
            result *= base;
        }
        if (negative)
        {
            result = 1.0/result;
        }
        return result;

    }
    else
    {
        if (exponent < 0)
        {
            InvalidInput = true;
        }
        return 0.0;
    }
}
int main()
{
    double base;
    int exponent;
    cin >> base >> exponent;
    double result = 0.0;
    result = Power(base, exponent);
    if (!InvalidInput)
    {
        cout << result << endl;
    }
    else
        cout << "Invalid input!" << endl;
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

bool scanUnsignedInteger(const char** str)
{
    const char* before = *str;
    while (**str != '\0' && **str >= '0' && **str <= '9')
    {
        ++(*str);
    }
    return *str>before;
}

bool scanInteger(const char** str)
{
    if (**str=='+'||**str=='-')
        ++(*str);
    return scanUnsignedInteger(str);
}

bool isNumeric(const char* str)
{
    if (str==nullptr)
    {
        return false;
    }
    bool numeric = scanInteger(&str);
    // 如果出现'.'，接下来是数字的小数部分
    if (*str == '.')
    {
        ++str;
        // 下面代码用||的原因：
        // 1.小数可以没有整数部分，如 .123 等于 0.123
        // 2.小数点后面可能没有数字，如 233. 等于 233.0
        // 3.小数点后面可能有数字，233.666
        numeric = scanUnsignedInteger(&str) || numeric;
    }

    // 如果出现 'e' 或 'E'，则接下来是数字的整数部分
    if (*str == 'e' || *str == 'E')
    {
        ++str;
        // 下面代码使用&&的原因：
        // 1.当 e 或 E 前面没有数字时，整个字符串不能表示数字，如.e1，e1
        // 2.当 e 或 E 后面没有整数时，整个字符串不能表示数字，如12e，12e+5.4
        numeric = numeric && scanInteger(&str);
    }
    return numeric && *str == '\0';
}

int main()
{
    string test;
    cin >> test;
    cout << isNumeric(&test[0]) << endl;
    return 0;
}
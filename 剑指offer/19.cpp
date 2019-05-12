#include <iostream>
using namespace std;

bool matchCore(char* str, char* pattern)
{
    if (*str == '\0' && *pattern == '\0')
        return true;
    if (*str != '\0' && *pattern == '\0')
        return false;
    if (*(pattern + 1) == '*')
    {
        if (*pattern == *str || (*pattern == '.' && *str != '\0'))
        {
            return matchCore(str+1, pattern+2) // move to the next state
                || matchCore(str+1, pattern) // stay on current state
                || matchCore(str, pattern+2); // ignore a'*'
        }
        else
        {
            return matchCore(str, pattern + 2); // ignore a '*'
        }
    }
    if (*str == *pattern || (*pattern == '.' && *str != '\0'))
        return matchCore(str + 1, pattern+1);
    return false;
}

bool match(char* str, char* pattern)
{
    if (str == nullptr || pattern == nullptr)
        return false;
    matchCore(str, pattern);
}

int main()
{
    int n;
    cin >> n;
    char* str = new char[n+1];
    for(int i = 0; i < n; ++i)
    {
        cin >> str[i];
    }
    str[n] = '\0';
    cin >> n;
    char* pattern = new char[n+1];
    for(int i = 0; i < n; ++i)
    {
        cin >> pattern[i];
    }
    pattern[n] = '\0';

    cout << match(str, pattern);
    return 0; 
}

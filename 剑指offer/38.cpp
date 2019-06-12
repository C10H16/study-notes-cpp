#include <iostream>
using namespace std;
void Permutation(char* pStr, char* pBegin)
{
    if (*pBegin=='\0')
    {
        cout << pStr << endl;
    }
    else
    {
        for (char* pCh = pBegin; *pCh != '\0'; ++pCh)
        {
            char temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
            Permutation(pStr, pBegin + 1);

            temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
        }
    }   
}

void Permutation(char* pStr)
{
    if(pStr == nullptr)
    {
        return;
    }
    Permutation(pStr, pStr);
}

int main()
{
    int n;
    cin >> n;
    char* str = new char[n+1];
    cin >> str;
    str[n] = '\0';
    Permutation(str);
    return 0;
}
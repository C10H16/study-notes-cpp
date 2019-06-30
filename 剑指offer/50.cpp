#include <iostream>
#include <string>
#include <map>
using namespace std;
// 问题一
char FirstNotRepeatingChar(string s)
{
    map<char, int> table;
    for(int i = 0; i < s.size(); ++i)
    {
        table[s[i]]++;
    }
    int i = 0;
    while(i < s.size()&&table[s[i]]>1)
    {
        ++i;
    }
    if (i < s.size())
        return s[i];
    else
    {
        return '\0';
    }
    
}
// 问题二
class CharStatistics
{
public:
    CharStatistics() : index(0)
    {
        for(int i = 0; i < 256; ++i)
            occurrence[i]=-1;
    }
    void Insert(char ch)
    {
        if (occurrence[ch] == -1)
            occurrence[ch] = index;
        else if (occurrence[ch] >= 0)
            occurrence[ch] = -2;
        index ++;
    }

    char FirstAppearingOnce()
    {
        char ch = '\0';
        int minIndex = numeric_limits<int>::max();
        for (int i = 0; i < 256; ++i)
        {
            if (occurrence[i] >= 0 && occurrence[i] < minIndex)
            {
                ch = (char)i;
                minIndex = occurrence[i];
            }
        }
        return ch;
    }
private:
    int occurrence[256];
    int index;
};

int main()
{
    string s;
    cin >> s;
    cout << FirstNotRepeatingChar(s);
    return 0;
}
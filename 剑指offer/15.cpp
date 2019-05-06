#include <iostream>
using namespace std;
int numberOf1(int n)
{
    int m = 0;
    int count = 0;
    while(n)
    {
        ++count;
        m = n-1;
        n = m&n;
    }
    return count;
}
int main()
{
    int n;
    cin >> n;
    cout << numberOf1(n) << endl;
    return 0;


}
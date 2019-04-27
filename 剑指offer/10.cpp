#include <iostream>
using namespace std;
unsigned long long Fibonacci(unsigned int n)
{
	if (n == 0)
		return 0;
	else if(n==1)
		return 1;
	else 
	{
		unsigned long long num1 = 0;
		unsigned long long num2 = 1;
		unsigned long long re = num1 + num2;
		unsigned int i = 2;
		while(i<=n)
		{
			re = num1 + num2;
			num1 = num2;
			num2 = re;
			++i;
		}
		return re;
	}
		
} 

int main()
{
	//unsigned int n;
	//cin >> n;
	for(unsigned int n = 0; n < 10; ++n)
		cout << Fibonacci(n)<<endl;
	return 0;
}

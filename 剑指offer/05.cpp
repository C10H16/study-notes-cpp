#include <iostream>
#define LEN 200
using namespace std;
void ReplaceBlank(char str[], int length)
{
	if (str==nullptr||length<=0)
	{
		return;
	}
	
	int originalLength = 0;
	int numberOfBlank = 0;
	int i = 0;
	while(str[i] != '\0')
	{
		++originalLength;
		if (str[i] == ' ')
		{
			++numberOfBlank;
		}
		++i;
	}
	int newLength = originalLength + 2 * numberOfBlank;
	if (newLength > length)
	{
		return;
	}
	int indexOfOriginal = originalLength;
	int indexOfNew = newLength;
	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)
	{
		if(str[indexOfOriginal] == ' ')
		{			
			str[indexOfNew--] = '0';
			str[indexOfNew--] = '2';
			str[indexOfNew--] = '%';
		}
		else
		{
			str[indexOfNew--] = str[indexOfOriginal];			
		}
		--indexOfOriginal;
	}
}
int main()
{
	char str[LEN];
	char a;
	int i = 0;
	gets(str);
	ReplaceBlank(str, LEN);
	i = 0;
	while(str[i] != '\0')
	{
		cout << str[i];
		++i;
	}
	return 0;
}

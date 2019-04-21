#include <iostream>
using namespace std;
void insertToList (int *a1, int *a2, int l1, int l2)
{
	if (a1 == nullptr || a2 == nullptr )
		return;
	int newLength = l1 + l2;
	int indexOfNew = newLength-1;
	int indexOfOriginal = l1-1;
	int i = l2-1;
	while(i >= 0 && indexOfNew >= 0)
	{
		
		if (indexOfOriginal >= 0 && a1[indexOfOriginal] < a2[i])
		{
			a1[indexOfNew--] = a2[i--];
		}
		else if(indexOfOriginal >= 0)
		{
			a1[indexOfNew--] = a1[indexOfOriginal--];
		}
		else
		{
			a1[indexOfNew--] = a2[i--];
		}
	}
}

int main()
{
	int l1, l2;
	cin >> l1 >> l2;
	int *a1 = new int[l1+l2];
	int *a2 = new int[l2];
	for(int i = 0; i < l1; ++i)
	{
		cin >> a1[i];
	}
	for(int i = 0; i < l2; ++i)
	{
		cin >> a2[i];
	}
	insertToList(a1, a2, l1, l2);
	for(int i = 0; i < l1 + l2; ++i)
	{
		cout << a1[i] << " ";
	}
	return 0;
}

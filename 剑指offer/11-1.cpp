#include <iostream>
using namespace std;
int findMin(int* num,int start, int end)
{
	int mid = (start + end)/2;
	if (mid == 0 || (mid > 0 && num[mid] < num[mid-1]))
		return num[mid];
	if (num[mid] > num[start])
		findMin(num, mid, end);
	else 
		findMin(num, start, mid);
}

int main()
{
	int n;
	cin >> n;
	int *num = new int[n];
	for(int i = 0; i < n; ++i)
	{
		cin >> num[i];
	}	
	cout << findMin(num, 0, n);
	delete[] num;
	return 0;
}

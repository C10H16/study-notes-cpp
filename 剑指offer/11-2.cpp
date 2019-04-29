#include <iostream>
using namespace std;

int MinInOrder(int* num, int index1, int index2)
{
	int min = num[index1];
	for (int i = index1+1; i <= index2; ++i)
	{
		if (num[i] < min)
			min = num[i];
	}
	return min;
} 
int findMin(int *num, int length)
{
	if (num == nullptr || length <=0)
	{
		throw ("Invalid parameters");
	}
	int index1 = 0;
	int index2 = length -1;
	int indexMid = index1;
	while (num[index1]>=num[index2])
	{
		if (index2 - index1 == 1)
		{
			indexMid = index2;
			break;
		}
		indexMid = (index1 + index2)/2;
		if (num[index1]==num[index2]&&num[indexMid]==num[index1]) // 三个数字相等时，只能顺序查找 
		{
			return MinInOrder(num,index1,index2);
		}
		if (num[indexMid]>=num[index1])
		{
			index1 = indexMid;
		}
		else if(num[indexMid]<=num[index2])
		{
			index2 = indexMid;
		}
	}
	return num[indexMid];
}



int main()
{
	int n;
	cin >> n;
	int* num = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> num[i];
	}
	cout << findMin(num, n);
	delete[] num;
	return 0;
}

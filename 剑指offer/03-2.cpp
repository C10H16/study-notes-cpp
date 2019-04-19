#include <iostream>
#include <vector>
using namespace std;

int findDuplicate(vector<int> &num, int start, int end)
{
	int count = 0;
	int middle = (end-start)/2+start;
	for(int i = 0; i < num.size(); ++i)
	{
		if (num[i]<=middle && num[i]>=start)
		{
			++count;
		}
	}
	if (start == middle && count > 1)
	{
		return start;
	}
	else
	{
		
		if (count > middle-start+1)
		{
			findDuplicate(num, start, middle);
		}
		else
		{
			findDuplicate(num, middle+1,end);
		}
		
	}
}

int main() 
{
	int n;
	cin >> n;
	vector<int> nums(n,0);
	int temp,i = 0;
	while (i < n)
	{
		cin >> temp;
		if (temp > n-1)
		{
			cout << temp << " is bigger than " << n-1 << endl; 
			cout << "please enter a correct number again." << endl;
		}
		else
		{
			nums[i] = temp;
			++i;
		}
	}
	cout << findDuplicate(nums,1,n);
	return 0;
	
}

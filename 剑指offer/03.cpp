#include <iostream>
#include <vector>
using namespace std;
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
	i = 0;
	bool flag = true;
	while (i < n)
	{
		if(nums[i]==i)
		{
			++i;
		}
		else
		{
			if (nums[i]==nums[nums[i]])
			{
				flag = false;
				break;
			}
			else
			{
				temp = nums[i];
				nums[i] = nums[temp];
				nums[temp] = temp;
			} 
		}
	}
	if (flag)
	{
		cout << "no dublicate number" << endl;
	}
	else
	{
		cout << "number " << nums[i] << " is duplicate." << endl;
	}
	return 0; 
}

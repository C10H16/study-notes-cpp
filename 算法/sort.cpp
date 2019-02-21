#include <iostream>
#include <vector>

using namespace std;

//普通的冒泡排序算法 
void bubbleSort1(vector<int> &num)
{
	int n = num.size();
	int i = 0;
	for (n; n > 0; --n)
	{
		for (i = 1; i < n; ++i)
		{
			if (num[i-1]>num[i])
			{
				swap(num[i-1],num[i]);
			}
		}
	}
}

//改进的冒泡排序算法，不需要完成全部n-1次循环，当排序完成时自动退出 
void bubbleSort2(vector<int> &num)
{
	bool sorted = false;
	int n = num.size();
	while(!sorted)
	{
		sorted = true;
		for(int i=1; i < n; ++i)
		{
			if (num[i-1]>num[i])
			{
				swap(num[i-1], num[i]);
				sorted = false;
			}
		}
		--n;
	}
}

//快速排序算法 
void quickSort(vector<int> &num, int low, int high)
{
	if(low>=high)
	{
		return;
	}
	int first = low;
	int last = high;
	int key = num[first];
	
	while(first < last)
	{
		while(first < last && num[last] >= key) //将小于key的放在前面 
		{
			--last;
		}
		num[first] = num[last];
		while(first < last && num[first] <= key)//将大于key的放在后面 
		{
			++first;
		}
		num[last] = num[first];
	}
	num[first] = key; //将key放在first和last重合的位置 
	quickSort(num, low, first-1); //递归对前半部分排序 
	quickSort(num, first+1, high); //递归对后半部分排序 
}

int main()
{
	//test 
	vector<int> num = {5,2,4,7,6,1,3};  
	quickSort(num,0,num.size()-1);
	for (int i = 0; i < num.size(); ++i)
	{
		cout << num[i] << " ";
	}
	cout << endl;
	return 0;
} 

#include <iostream>
#include <vector>

//普通的冒泡排序算法 
void bubbleSort1(std::vector<int> &num)
{
	int n = num.size();
	int i = 0;
	for (n; n > 0; --n)
	{
		for (i = 1; i < n; ++i)
		{
			if (num[i-1]>num[i])
			{
				std::swap(num[i-1],num[i]);
			}
		}
	}
}

//改进的冒泡排序算法，不需要完成全部n-1次循环，当排序完成时自动退出 
void bubbleSort2(std::vector<int> &num)
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
				std::swap(num[i-1], num[i]);
				sorted = false;
			}
		}
		--n;
	}
}

//快速排序算法 
void quickSort(std::vector<int> &num, int low, int high)
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

// 选择排序
void selectionSort(std::vector<int> &num)
{
	int n = num.size();
	int min = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		min = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (num[j]<num[min])
				min = j;
			
		}
		std::swap(num[i], num[min]);
	}
}

// 插入排序
void insertionSort(std::vector<int> &num)
{
	int n = num.size();
	int j = 0,key = 0;
	for(int i = 1; i < n; ++i)
	{
		j = i-1;
		key = num[i];
		while (j>=0 && num[j]>key)
		{
			num[j+1] = num[j];
			--j;
		}
		num[j+1] = key;
	}
}
 
// 二分查找插入排序
int searchInsert(std::vector<int>& nums, int target, int low, int high) 
{ 
        int mid = (high - low)/2;
        while (low != high)
        {
            if (target>nums[mid])
            {
                low = mid + 1;
            }
            else
            {
                high = mid;
            }
            mid = low + (high - low)/2;
        }
        return low;
}

void insertionSort2(std::vector<int> &num)
{
	int n = num.size();
	int j = 0, k = 0, key = 0;
	for(int i = 1; i < n; ++i)
	{
		key = num[i];
		j = searchInsert(num, key, 0, i);
		for (k = i;k > j; --k)
		{
			num[k] = num[k-1];
		}
		num[j] = key;
	}
}

// 归并排序 递归
void merge(std::vector<int> &num, int low, int mid, int high)
{
	std::vector<int> leftSorted(num.begin()+low, num.begin()+mid+1);
	std::vector<int> rightSorted(num.begin()+mid+1, num.begin()+high+1);
	int l = 0, r = 0,i = low;
	while (l<leftSorted.size()&&r<rightSorted.size())
	{
		if (leftSorted[l] < rightSorted[r])
		{
			num[i] = leftSorted[l];
			++l;
		}
		else
		{
			num[i] = rightSorted[r];
			++r;
		}
		++i;
	}
	if (l < leftSorted.size())
	{
		for(l; l < leftSorted.size(); ++l)
		{
			num[i] = leftSorted[l];
			++i;
		}
	}
	else
	{
		for(r; r< rightSorted.size(); ++r)
		{
			num[i] = rightSorted[r];
			++i;
		}
	}
}

void mergeSort(std::vector<int> &num, int low, int high)
{
	if (low>=high)
		return;
	int mid = (low + high) / 2;
	mergeSort(num, low, mid);
	mergeSort(num, mid+1, high);
	merge(num, low, mid, high);
}
 

int main()
{
	//test 
	std::vector<int> num = {5,2,4,7,6,1,3};  
	mergeSort(num, 0, num.size()-1);
	for (int i = 0; i < num.size(); ++i)
	{
		std::cout << num[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}

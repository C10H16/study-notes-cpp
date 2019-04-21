# 数组、字符串

##　数组

数组的内存是连续的，可以根据下标以 O(1) 的时间读/写任何元素。

如果使用哈希表，通过键-值对的方式就可以在 O(1) 的时间内完成查找。

```C++
int GetSize(int data[])
{
    return sizeof(data);
}
int _tmain(int argc, _TCHAR* argv[])
{
    int data1[] = {1,2,3,4,5};
    int size1 = sizeof(data1);// 求数组的大小，4*5=20 byte
    
    int *data2 = data1;
    int size2 = sizeof(data2);// 指针的大小，32 位系统上为 4 byte, 64位系统上为 8 byte
        
    int size3 = GetSize(data1);// 作为函数参数传递，数组退化为同类型指针。
    printf("%d,%d,%d",size1,size2,size3); // 20,4,4
}
```

### 数组中重复的数字

> 在一个长度为 n 的数组里所有数字都在 0~n-1 的范围内，数组中某些数字是重复的。找出数组中任意一个重复的数字。

- 先将数组排序，再从头开始扫描。排序时间复杂度：O(nlogn) ；扫描时间复杂度：O(n)

- 使用哈希表，没扫描一个数字，添加到哈希表中，如果哈希表中已经存在这个数字，则返回。时间复杂度：O(n)；空间复杂度：O(n)

- 因为长度为 n 的数组的数字范围为 0~n-1，因此可以依次访问数组中的每个数字，查找第 i 位的数字是否为 i，是的话则继续扫描，否则，如果该数为 m，则与第 m 位的数字交换，然后继续比较，直到发现一个重复的数字。

```C++
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
```
总时间复杂度为 O(n)，空间复杂度为 O(1)

> 在不修改数组的前提下找出重复的数字

- 建立哈希表或建立长度为 n+1 的辅助数组，空间复杂度为O(n)
- 利用类似二分查找的思想。长度为 n+1 的数组，数字的范围为1~n，则取m=(n+1/2)，统计小于等于 m 的数字的个数，若其总数大于 m，则说明重复数字的大小在区间 [1,m] 之间，否则就在 [m+1,n] 之间。

```C++
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
	cin >> n; // 输入数组中数字个数
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
```

**注意**：这种算法不能够找出所有重复的数字

> 如果有不同的功能要求或者性能要求（时间效率优先、空间效率优先），那么最终选择的算法也不同。在写程序之前需要弄清楚需求。



### 二维数组中的查找

> 在一个二维数组中，每一行按照从上到下的顺序递增，每一列按照从左到右的顺序递增，请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否有该整数。

从数组的最后一行第一个数字开始找起，设要找的数字为 x，如果当前数字大于 x，则将上一行同一列的数字与 x 比较，否则与同一行下一列的数字进行比较。当当前数字在第一行且大于 x或当前数字在最后一列且小于 x 时，查找失败。（书中方法为从矩阵的右上角开始找，基本思路相同）

```C++
#include <iostream>
using namespace std;
bool findX(int **arr, int x,int row, int col)
{
	bool find = false;
	int i = row-1,j = 0;
	if (arr != NULL && row > 0 && col > 0)
	{
		while (i >= 0 && j < col)
		{
			if (x > arr[i][j])
			{
				++j;
			}
			else if(x < arr[i][j])
			{
				--i;
			}
			else
			{
				cout << i+1 << "," << j+1 << endl;
				return true;
			}
		}
	}
	return false;
}
int main()
{
	int row, col, x;
	cin >> row >> col;
	int **arr = new int *[row];
	for(int i = 0; i < row; ++i)
	{
		arr[i] = new int[col];
	}
	for(int i = 0; i < row; ++i)
	{
		for(int j = 0; j < col; ++j)
		{
			cin >> arr[i][j];
		}
	}
	cin >> x;
	cout << findX(arr, x,row,col);
	for(int i = 0; i < row; ++i)
	{
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}
```

## 字符串

注意，字符串末尾有一个'\0'字符，比看上去多一个字节。

### 替换字符串中的空格

> 实现一个函数，把字符串中的每个空格替换成‘%20’

考虑不借助辅助空间的情况，如果从左至右扫描，每当遇到空格就将空格改为‘%20’，则每次都需要将空格后的字符串后移2位，时间复杂度为O(n^2)。可以先扫描以便字符串，计算出空格的数量 n，则更改后字符串的长度增加 2*n。然后从后向前将字符串中的每个字符放入相应的位置。这样的时间复杂度为 O(n)。此时要考虑原字符串后有没有足够的空余内存。

```C++
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
```

### 合并两个数组（字符串）

> 两个排序数组A1和A2，在A1尾部有足够空间容纳A2，把A2所有数字插入A1中，且所有数字是排序的

可以使用和上一题同样的方法，从后向前将A2插入A1。

在合并两个数组或字符串时，都可以使用这个方法，减少移动次数，提高效率。

```C++
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
```


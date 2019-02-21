#include <iostream>
#include <vector>

using namespace std;

//��ͨ��ð�������㷨 
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

//�Ľ���ð�������㷨������Ҫ���ȫ��n-1��ѭ�������������ʱ�Զ��˳� 
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

//���������㷨 
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
		while(first < last && num[last] >= key) //��С��key�ķ���ǰ�� 
		{
			--last;
		}
		num[first] = num[last];
		while(first < last && num[first] <= key)//������key�ķ��ں��� 
		{
			++first;
		}
		num[last] = num[first];
	}
	num[first] = key; //��key����first��last�غϵ�λ�� 
	quickSort(num, low, first-1); //�ݹ��ǰ�벿������ 
	quickSort(num, first+1, high); //�ݹ�Ժ�벿������ 
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

#include <iostream>
#include <string>
#include "strhash.h"
using namespace std;
int main()
{
	string a = "abcd0301";
	string b = "20190301test";// �ַ�������������� 
	str_hash ha = str_to_hash(a);
	str_hash hb = str_to_hash(b);
	cout << a << " " << ha << ": " << hash_to_str(ha) << endl;
	cout << b << " " << hb << ": " << hash_to_str(hb) << endl;
	return 0;
} 

#include <iostream>
#include <string>
#include "strhash.h"
using namespace std;
int main()
{
	string a = "a ~0301";
	string b = "aaaa  test";// 字符串过长导致溢出 
	str_hash ha = str_to_hash(a);
	str_hash hb = str_to_hash(b);
	cout << a << " " << ha << ": " << hash_to_str(ha) << endl;
	cout << b << " " << hb << ": " << hash_to_str(hb) << endl;
	return 0;
} 

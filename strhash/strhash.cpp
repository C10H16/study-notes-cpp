#include <string> 
#include <math.h>
typedef unsigned long long str_hash;
str_hash str_to_hash(const std::string& s)
{
	str_hash sum = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		sum += ((int)s[i] - 32)*(str_hash)pow(95,i);
	}
	return sum;
}
std::string hash_to_str(str_hash h)
{
	std::string re = "";
	while(h > 0)
	{
		re += (char) (h % 95 + 32);
		h /= 95;
	}
	return re;
}

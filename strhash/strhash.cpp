#include <string> 
#include <math.h>
typedef unsigned long long str_hash;
str_hash str_to_hash(const std::string& s)
{
	str_hash sum = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		sum += ((int)s[i] - 32)*(str_hash)pow(94,i);
	}
	return sum;
}
std::string hash_to_str(str_hash h)
{
	std::string re = "";
	while(h > 0)
	{
		re += (char) (h % 94 + 32);
		h /= 94;
	}
	return re;
}

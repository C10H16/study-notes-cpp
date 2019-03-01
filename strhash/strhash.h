/*---------------
字符串与hash相互转换
字符串可以使用ASCII码表中除空格之外所有可打印字符
字符串长度不超过8，否则可能溢出，导致无法从hash转换回正确的字符串。 
---------------*/

#ifndef _STRHASH_H
#define _STRHASH_H
#include <string>
typedef unsigned long long str_hash; 
str_hash str_to_hash(const std::string& s);

std::string hash_to_str(str_hash h);

#endif

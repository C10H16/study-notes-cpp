/*---------------
�ַ�����hash�໥ת��
�ַ�������ʹ��ASCII����г��ո�֮�����пɴ�ӡ�ַ�
�ַ������Ȳ�����8�������������������޷���hashת������ȷ���ַ����� 
---------------*/

#ifndef _STRHASH_H
#define _STRHASH_H
#include <string>
typedef unsigned long long str_hash; 
str_hash str_to_hash(const std::string& s);

std::string hash_to_str(str_hash h);

#endif

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Cstring"
#include "vector"
#include "iterator"
#include <cstdlib>
using namespace std;

int main()
{
	vector<int> s{0,1,2};

	vector<int>::size_type cnt = s.size();
	
	for (vector<int>::size_type i = 0; i != s.size(); i++, cnt--)
		s[i] = cnt;


	char str[] = "asf asdf";
	char str2[] = "das f h";
	char str3[sizeof str / sizeof *str + sizeof str2 / sizeof *str2] = {"\0"};//1、使用sizeof2、初始化必须加入0字符
	strcat_s(str3, str);
	strcat_s(str3, str2);

	for(auto i:str3)
	cout << i << endl;

	system("PAUSE");
	return 0;
}


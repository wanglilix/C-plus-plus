// test.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <iostream>
#include <list> 
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <forward_list>
using namespace std;
using namespace std::placeholders;

void replace(string & str, string oldVal, string newVal);
int main()
{
	string str("what i love is you");
	string strA("what");
	string strB("What");
	replace(str, strA, strB);

	cout << str << endl;

	system("PAUSE");
	return 0;
}

void replace(string & str, string oldVal, string newVal)
{
	istringstream str2(str);
	string str3;
	vector<string> vec;
	while (str2 >> str3)
	{
		vec.push_back(str3);
	}
	auto beg = vec.begin();
	while (beg != vec.end())
	{
		if (oldVal == *beg)
		{
			*beg = newVal;
		}
		++beg;
	}

	str.clear();
	for (auto i : vec)
	{
		for (auto j : i)
		{
			str.push_back(j);
		}
		str.push_back(' ');
	}
}
// test.cpp : 定义控制台应用程序的入口点。

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
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <time.h>
//#include <initalizer_list.h>
#include <stdexcept>
#include <new>

using namespace std;
using namespace std::placeholders;

void main()
{
	vector<string> vec{ "s", "ss", "sss", "ssss", "gjhhgjgjgjgjhgj" };
	map<int, int> count;


	for_each(vec.begin(), vec.end(), [&count](const string& str){ ++count[str.size() - 1];  });

	for (auto i : count)
	{
		cout << "长度：" << i.first << "    个数：" << i.second << endl;
	}


	system("PAUSE");
	return;
}
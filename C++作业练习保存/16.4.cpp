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

template<typename T, typename M>
T find(T & begin, const T & end, const M & traget)
{
	while (begin != end)
	{
		if (*begin == target)
		{
			return begin;
		}
		++begin;
	}
	return end;
}

void main()
{
	vector<int> a{ 1, 2, 3, 4, 5, 6 };
	list<string> b{ "1", "2", "3", "4", "5", "6" };

	auto i = find(a.begin(), a.end(), 4);
	cout << *i << endl;

	auto j = find(b.begin(), b.end(), "3");
	cout << *j << endl;

	system("PAUSE");
	return;
}
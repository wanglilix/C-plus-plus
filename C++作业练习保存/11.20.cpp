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

using namespace std;
using namespace std::placeholders;

void main()
{
	ifstream fil("data.txt");
	istream_iterator<string> ifil(fil);
	istream_iterator<string> eof;
	vector<string> vec;
	copy(ifil, eof, back_inserter(vec));

	map<string, int> word_count;
	string word;
	auto beg = vec.begin();
	while (beg != vec.end())
		++(word_count.insert({ *beg++,0 }).first->second);



	system("PAUSE");
	return;
}
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

shared_ptr<vector<int>> make(void)
{
	return make_shared<vector<int>>();//默认初始化
}
void input(vector<int> &vec)
{
	int n;
	while (cin >> n)
		vec.push_back(n);
}
void output(const vector<int> &vec)
{
	for (auto i : vec)
		cout << i << endl;
}
void main()
{
	shared_ptr<vector<int>> vec = make();
	input(*vec);
	output(*vec);

	system("PAUSE");
	return;
}
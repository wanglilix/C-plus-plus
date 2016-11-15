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

void main()
{
	vector<int> vec;
	int in;
	cout << "请输入数字：" << endl;
	while (cin >> in)
	{
		vec.push_back(in);
	}

	cout << "输入查询的数字:" << endl;

	cin.clear();
	cin >> in;

	in = count(vec.begin(), vec.end(), in);
	cout << "查询值出现了：" << in << "次" << endl;

	system("PAUSE");
	return;
}
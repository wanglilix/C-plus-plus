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
	vector<int> vec{ 1233, 1245, 1555, 4, 5 };
	int sz = 1024;
	auto a = count_if(vec.begin(), vec.end(), [sz](int & i){ return i > sz; });
	cout << a << endl;

	vector<string> vecstr{ "s", "s", "sd", "s", "d" };
	string s = "s";
	auto b = find_if(vecstr.begin(), vecstr.end(), [s](string & i){ return i != s; });
	cout << *b << endl;


	for_each(vec.begin(), vec.end(), [sz](int & i){  i *= sz; });
	for_each(vec.begin(), vec.end(), [](int & i){  cout << i << endl; });

	system("PAUSE");
	return;
}
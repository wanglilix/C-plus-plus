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

class Foo
{
public:
	Foo() = default;
	Foo(const Foo&a) { data = a.data; };
	Foo(const Foo&&a) { data = std::move(a.data); };


	Foo &operator=(const Foo &rhs) & { cout << "左值" << endl; return *this; };
	Foo &operator=(const Foo &rhs) && { cout << "右值" << endl;  return *this; };
private:
	vector<int> data;

};

void main()
{
	Foo a, b;
	a = b;
	std::move(a) = b;

	system("PAUSE");
	return;
}
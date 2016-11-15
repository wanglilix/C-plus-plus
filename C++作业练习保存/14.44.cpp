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


int add(int lhs, int rhs)
{
	return lhs + rhs;

}

auto mod = [](int lhs, int rhs) -> int { return lhs&rhs; };

struct divide
{
	int operator()(int a, int b)
	{
		return  a / b;
	}
};


void main()
{

	function<int(int, int)> f1 = add;
	function<int(int, int)> f2 = divide();
	function<int(int, int)> f3 = mod;

	map<string, function<int(int, int)>> binops = {

		{ "+", add },
		{ "/", divide() },
		{ "%", mod },
		{ "*", multiplies<int>() },
		{ "-", minus<int>() }
	};

	binops["+"](10, 5);

	system("PAUSE");
	return;
}
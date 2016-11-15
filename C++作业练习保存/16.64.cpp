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
#include <tuple>
#include <random>

using namespace std;
using namespace std::placeholders;

template<typename T>
int count(const vector<T> & vec, const T num)
{
	return count(vec.begin(), vec.end(), num);
}

template<>
int count(const vector<const char*> & vec, const const char* num)
{
	int n = 0;
	for (auto & i : vec)
	{
		if (*i == *num)
		{
			++n;
		}
	}
	return n;
}


void main()
{
	char* a = "aaa";
	char* b = "bb";
	vector<char*> vec{ a, b };
	cout << count(vec, a) << endl;


	system("PAUSE");
	return;
}
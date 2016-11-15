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

template<typename T>
void print(const T & vessel)
{
	typedef typename T::size_type size_type;
	for (size_type i = 0; i < vessel.size(); i++)
	{
		cout << vessel.at(i) << endl;
	}
	cout << endl;
}

void main()
{
	string s = "Hello!";
	print(s);

	system("PAUSE");
	return;
}
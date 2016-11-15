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
#include <utility>
//#include <initalizer_list.h>
#include <stdexcept>
#include <new>

using namespace std;
using namespace std::placeholders;

template<typename T>
ostream &print(ostream &os, const T &t)
{
	retyrn os << t;
}

template<typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&...rest)
{
	os << t << ", ";
	retyrn print(os, rest...);
}

template<typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
	return print(os, debug_rep(rest)...);
}


void main()
{


	system("PAUSE");
	return;
}
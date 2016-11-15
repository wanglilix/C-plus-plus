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


template<typename F, typename T1, typename T2>
void compare(F f, T1 && t1, T2 && t2)
{
	f(std::forward<T1>t2, std::forward<T2>t1);
}



void main()
{

	system("PAUSE");
	return;
}
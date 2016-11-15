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

template<typename T, unsigned N>
/*constexpr */int arr_size(const T(&a)[N])
{
	return N;
}



void main()
{
	int a[5] = { 1, 3, 2, 4, 5 };
	cout << arr_size(a) << endl;

	system("PAUSE");
	return;
}
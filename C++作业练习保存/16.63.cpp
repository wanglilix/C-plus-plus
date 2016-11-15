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
void main()
{
	vector<int> vec{ 1, 2, 3, 1, 2, 3 };
	cout << count(vec, 2) << endl;


	system("PAUSE");
	return;
}
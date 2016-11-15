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


class compar{
public:
	compar(){};
	compar(int a) :n(a){  };
public:
	bool operator() (int m){ return m == n; };

private:
	int n = 2;

};

void main()
{
	vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	compar aa;
	replace_if(vec.begin(), vec.end(), aa, 12);
	for (auto i : vec)
	{
		cout << i << endl;
	}



	system("PAUSE");
	return;
}
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
#include <regex>

using namespace std;
using namespace std::placeholders;

void main()
{
	cout << "输入邮政号码：" << endl;
	string phone = "(\\d{5})(-)?(\\d{4})?";
	regex r(phone);
	smatch results;
	string filename;
	while (cin >> filename)
	{
		if (regex_search(filename, results, r))
		{
			cout << results.str() << endl;
		}
	}

	system("PAUSE");
	return;
}
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
	ifstream infil("data.txt");
	string a, str;
	while (getline(infil, a))
	{
		str += a;
	}
	smatch results;
	regex r2("[[:alpha:]]*[^c]ie[[:alpha:]]*", regex::icase);
	for (sregex_iterator it(str.begin(), str.end(), r2), end_it; it != end_it; ++it)
	{
		cout << it->str() << endl;
	}


	regex r(".*[^c]ie.*", regex::icase);
	for (sregex_iterator it(str.begin(), str.end(), r), end_it; it != end_it; ++it)
	{
		cout << it->str() << endl;
	}

	system("PAUSE");
	return;
}
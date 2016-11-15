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
	//ifstream infil("data.txt");
	//string a, str;
	//while (getline(infil, a))
	//{
	//	str += a;
	//}
	string pattern("[^c]ei");
	regex r("[[:alpha:]]*" + pattern + "[[:alpha:]]*");
	regex r2("([[:alpha:]]*)+[^c]ei+[[:alpha:]]*");
	regex r3("([[:alpha:]]*)+[^c]ei+([[:alpha:]]*)");//3个都可以
	smatch results;
	string filename;
	while (cin >> filename)
	{
		if (regex_search(filename, results, r2))
		{
			cout << results.str() << endl;
		}
	}



	system("PAUSE");
	return;
}
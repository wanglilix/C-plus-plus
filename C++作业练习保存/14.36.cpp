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


class printstr{
public:
	string operator()()
	{
		string str;
		if (getline(in, str))
		{
			return str;
		}
		else
		{
			return "";
		}
	};
private:
	istream & in = cin;

};

void main()
{
	printstr tmp;
	vector<string> vec;
	while (1)
	{
		auto str = tmp();
		if (!str.size())
		{
			break;
		}
		vec.push_back(str);
	}



	system("PAUSE");

	return;
}
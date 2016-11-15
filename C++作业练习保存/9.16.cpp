// test.cpp : 定义控制台应用程序的入口点。
//
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

using namespace std;
using namespace std::placeholders;

int main()
{
	vector<int> lis = { 1,2,3,4,5,6,7,8,9 };
	list<int> lis2;
	lis2.assign(lis.begin(), lis.end());
	//lis2.push_back(1);

	auto lisbeg = lis.begin();
	auto lisend = lis.end();
	auto lis2beg = lis2.begin();
	auto lis2end = lis2.end();

	int flag = 0;

	while (lisbeg != lisend&&lis2beg != lis2end)
	{
		if ((*lisbeg) > (*lis2beg))
		{
			cout << "lis" << " is biger" << endl;
			flag = 1;
			break;
		}
		else if ((*lisbeg) < (*lis2beg))
		{
			cout << "lis2" << " is biger" << endl;
			flag = 1;
			break;
		}
		++lisbeg;
		++lis2beg;

		if (lisbeg == lisend&&lis2beg != lis2end)
		{
			cout << "lis2" << " is biger" << endl;
			flag = 1;
			break;
		}

		if (lis2beg == lis2end&&lisbeg != lisend)
		{
			cout << "lis" << " is biger" << endl;
			flag = 1;
			break;
		}
	}

	if (0 == flag)
	{
		cout << "same" << endl;
	}


	system("PAUSE");
	return 0;
}


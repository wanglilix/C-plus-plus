// test.cpp : �������̨Ӧ�ó������ڵ㡣
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
#include <forward_list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using namespace std::placeholders;

void main()
{
	/*ifstream fil("data.txt");
	istream_iterator<string> ifil(fil);
	istream_iterator<string> eof;
	vector<string> vec;
	copy(ifil, eof, back_inserter(vec));*/
	map<string, vector<string>> home;
	string str, name, child;
	cout << "�����������ͥ+����:" << endl;
	while (getline(cin, str))
	{
		istringstream names(str);
		if (names >> name)
		{
			if (home.find(name) == home.end())
				home[name] = vector<string>{ child };

			while (names >> child)
			{
				home[name].push_back(child);
			}
		}
		else
		{
			cout << "�����������ͥ+����:" << endl;
		}

		for (auto i : home)
		{
			cout << i.first << " :";
			for (auto j : i.second)
				cout << j << " ";
		}
		cout << endl;

	}





	system("PAUSE");
	return;
}
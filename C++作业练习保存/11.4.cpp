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
#include <forward_list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using namespace std::placeholders;

void main()
{
	ifstream fil("data.txt");
	istream_iterator<string> ifil(fil);
	istream_iterator<string> eof;

	vector<string> vec;
	//copy(ifil, eof, back_inserter(vec));

	map<string, int> word_count;

	while (ifil != eof)
	{
		string word;
		word = *ifil;
		auto beg = word.begin();
		while (beg != word.end())
		{
			!islower(*beg) ? *beg = tolower(*beg) : *beg = *beg;
			!isalpha(*beg) ? beg = word.erase(beg) : ++beg;
		}

		++word_count[word];
		++ifil;
	}

	for (auto w : word_count)
	{
		cout << w.first << " occurs " << w.second
			<< ((w.second>1) ? " time" : " times") << endl;

	}

	system("PAUSE");
	return;
}
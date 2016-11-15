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

void biggies(vector<string> & words, vector<string>::size_type sz)
{
	stable_sort(words.begin(), words.end(), [](const string& a, const string &b){ return a.size() < b.size(); });
	auto wc = find_if(words.begin(), words.end(), [sz](const string &a){ return a.size() >= sz; });
	auto count = words.end() - wc;
	string str = count>1 ? "words" : "word";
	cout << count << " " << str << " of length  " << sz << " or longer" << endl;
	for_each(wc, words.end(), [](string & str){  cout << str << endl; });
	cout << endl;

}

void main()
{
	vector<string> vec{ "s", "ss", "sss", "ssss", "gjhhgjgjgjgjhgj" };
	biggies(vec, 3);

	system("PAUSE");
	return;
}
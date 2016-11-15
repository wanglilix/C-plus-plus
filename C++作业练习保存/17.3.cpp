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

using namespace std;
using namespace std::placeholders;

//tuple<	string, shared_ptr<set<int>>, shared_ptr<vector<string>>> QueryResult;

class TextQuery
{
public:
	shared_ptr<vector<string>> strptr;
	map<string, shared_ptr<set<int>>> linemap;

public:
	TextQuery() :strptr(nullptr), linemap(map<string, shared_ptr<set<int>>>()) {};
	TextQuery(ifstream &);
	tuple<	string, shared_ptr<set<int>>, shared_ptr<vector<string>>> query(const string&);
};

TextQuery::TextQuery(ifstream &infil)
{
	string line, word;
	int n = 0;
	vector<string> vec;
	while (getline(infil, line))
	{
		vec.push_back(line);
		istringstream linestr(line);
		while (linestr >> word)
		{
			if (linemap.find(word) == linemap.end())
			{
				linemap[word] = make_shared<set<int>>();//必须先分配内存再插入对象
				linemap[word]->insert(n);
			}
			else
			{
				linemap[word]->insert(n);
			}
		}
		++n;//从0开始！
	}
	strptr = make_shared<vector<string>>(std::move(vec));//必须先分配内存再插入对象

}

tuple<string, shared_ptr<set<int>>, shared_ptr<vector<string>>> TextQuery::query(const string& str)
{
	tuple<	string, shared_ptr<set<int>>, shared_ptr<vector<string>>> result;
	get<0>(result) = str;
	if (linemap.find(str) != linemap.end())
	{
		get<2>(result) = strptr;
		get<1>(result) = linemap.find(str)->second;
	}
	return result;
}

void print(tuple<	string, shared_ptr<set<int>>, shared_ptr<vector<string>>> & result)
{
	if (get<2>(result) != nullptr)
	{
		cout << get<0>(result) << " show :" << endl;
		for (auto i : *get<1>(result))
		{
			cout << "(line " << i + 1 << " )  ";
			cout << (*get<2>(result))[i] << endl;
		}
	}
	else
	{
		cout << "No find result!" << endl;
	}
}
void main()
{
	ifstream infil("data.txt");
	TextQuery data(infil);
	auto result = data.query("he");
	print(result);

	system("PAUSE");
	return;
}
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

class StrBlob
{
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	void push_back(const string &t) { data->push_back(t); }
	void pop_back();
	string & front();
	string & front() const;
	string & back();
	string & back()  const;
	shared_ptr<vector<string>> data;
private:

	void check(size_type i, const string &msg) const;
};

StrBlob::StrBlob() :data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
void	 StrBlob::check(size_type i, const string &msg) const
{
	if (i > data->size())
		throw out_of_range(msg);
}
string & StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}
string & StrBlob::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}
string & StrBlob::back()
{
	check(0, " back on empty strblob");
	return data->back();
}
string & StrBlob::back() const
{
	check(0, " back on empty strblob");
	return data->back();
}
void     StrBlob::pop_back()
{
	check(0, " pop_back empty strblob");
	data->pop_back();
}

class QueryResult;
class TextQuery
{
public:
	StrBlob strptr;
	map<string, shared_ptr<set<int>>> linemap;

public:
	TextQuery() :strptr(), linemap(map<string, shared_ptr<set<int>>>()) {};
	TextQuery(ifstream &);
	QueryResult query(const string&);
};

TextQuery::TextQuery(ifstream &infil)
{
	string line, word;
	int n = 0;
	while (getline(infil, line))
	{
		strptr.push_back(line);
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


}


class QueryResult
{
public:
	QueryResult() : word(""), setptr(nullptr), strptr() {};
public:
	string word;
	shared_ptr<set<int>> setptr;
	StrBlob strptr;
};


QueryResult TextQuery::query(const string& str)
{
	QueryResult result;
	result.word = str;
	if (linemap.find(str) != linemap.end())
	{
		result.strptr = strptr;
		result.setptr = linemap.find(str)->second;
	}
	return result;
}

void print(QueryResult & result)
{
	if (result.setptr != nullptr)
	{
		cout << result.word << " show :" << endl;
		for (auto i : *result.setptr)
		{
			cout << "(line " << i + 1 << " )  ";
			cout << (*((result.strptr).data))[i] << endl;
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
	auto result = data.query("go.");
	print(result);

	system("PAUSE");
	return;
}
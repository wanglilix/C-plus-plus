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
class StrBlobPtr;
class StrBlob
{
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	void push_back(const string &t) { data->push_back(t); }
	void push_back(string &&t) { data->push_back(std::move(t)); cout << "调用移动push_back函数！" << endl; };
	void pop_back();
	string & front();
	string & front() const;
	string & back();
	string & back()  const;

	friend class StrBlobPtr;
	StrBlobPtr begin();
	StrBlobPtr end();

private:
	shared_ptr<vector<string>> data;
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


class StrBlobPtr
{
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob &a, int sz = 0) :wptr(a.data), curr(sz) {}
	string & deref() const;
	StrBlobPtr & incr();
private:
	shared_ptr<vector<string>>check(int, const string&) const;
	weak_ptr<vector<string>> wptr;
	int curr;
};
shared_ptr<vector<string>>StrBlobPtr::check(int i, const string&msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw out_of_range(msg);
	return ret;
}
string & StrBlobPtr::deref() const
{
	auto p = check(curr, "derefereance past end");
	return (*p)[curr];
}
StrBlobPtr & StrBlobPtr::incr()
{
	check(curr, "increment past end of strblobptr");
	++curr;
	return *this;
}
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

void main()
{
	StrBlob s;
	s.push_back("d");
	cout << s.front() << endl;


	system("PAUSE");
	return;
}
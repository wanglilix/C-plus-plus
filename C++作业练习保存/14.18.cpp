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
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;

public:
	friend	bool operator==(const StrBlob&, const StrBlob&);//此处与关系运算符不一致: !=成立时应该有一个要 < 另一个 
	friend	bool operator!=(const StrBlob&, const StrBlob&);
	friend	bool operator<(const StrBlob&, const StrBlob&);//不一致，逻辑上只能取其一
	friend	bool operator<=(const StrBlob&, const StrBlob&);
	friend	bool operator>(const StrBlob&, const StrBlob&);
	friend	bool operator>=(const StrBlob&, const StrBlob&);
};

StrBlob::StrBlob() :data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

bool operator==(const StrBlob& lhs, const StrBlob& rhs)
{
	return lhs.data == rhs.data;
}
bool operator!=(const StrBlob& lhs, const StrBlob& rhs)
{
	return !(lhs.data == rhs.data);
}

bool operator<(const StrBlob& lhs, const StrBlob& rhs)
{
	return *lhs.data < *rhs.data;
}
bool operator<=(const StrBlob& lhs, const StrBlob& rhs)
{
	return *lhs.data <= *rhs.data;
}
bool operator>(const StrBlob& lhs, const StrBlob& rhs)
{
	return *lhs.data > *rhs.data;
}
bool operator>=(const StrBlob& lhs, const StrBlob& rhs)
{
	return *lhs.data >= *rhs.data;

}



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

void main()
{
	const StrBlob s{ "yes" }, w{ "yes" };
	cout << boolalpha << (s != w) << endl;
	cout << boolalpha << (s < w) << endl;
	cout << boolalpha << (s > w) << endl;
	cout << boolalpha << (s <= w) << endl;

	system("PAUSE");
	return;
}
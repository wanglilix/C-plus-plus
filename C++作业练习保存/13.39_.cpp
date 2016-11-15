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

#define _SCL_SECURE_NO_WARNINGS 

using namespace std;
using namespace std::placeholders;

class StrVec
{
public:
	StrVec() :
		elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const StrVec &);
	StrVec &operator=(const StrVec &);
	~StrVec();
	void push_back(const string&);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string *begin() const { return elements; }
	string* end()const { return first_free; }
private:
	static std::allocator<string> alloc;//分配元素
	void chk_n_alloc()
	{
		if (size() == capacity())
			reallocate();
	}
	std::pair<string*, string*> alloc_n_copy(const string*, const string*);
	void free();
	void reallocate();
	string * elements;
	string * first_free;
	string * cap;
};
StrVec::StrVec(const StrVec &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
StrVec::~StrVec() { free(); }
StrVec &StrVec::operator=(const StrVec &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}
std::pair<string*, string*> StrVec::alloc_n_copy(const string*a, const string*b)
{
	auto newdata = alloc.allocate(b - a);
	return{ newdata, uninitialized_copy(a, b, newdata) };
}
void StrVec::free()
{
	if (elements)
	{
		for (auto p = first_free; p != elements; )
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}
void StrVec::push_back(const string & s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}
void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);

	auto dest = newdata;
	auto elem = elements;

	for (size_t i = 0; i != size(); ++i)
	{
		alloc.construct(dest++, std::move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}


void main()
{

	system("PAUSE");
	return;
}
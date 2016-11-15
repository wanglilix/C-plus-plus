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


template<typename T>
class BlobPtr;
template<typename T>
class Blob
{
public:
	typedef T value_type;
	typedef typename vector<T>::size_type size_type;
	Blob();
	Blob(initializer_list<T> il);
	template<typename V>
	Blob(const V &, const V &);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	void push_back(const T &t) { data->push_back(t); }
	void push_back(const T && t) { data->push_back(std::move(t)); }
	void pop_back();
	T & front();
	T & front() const;
	T & back();
	T & back()  const;

	friend class BlobPtr<T>;
	BlobPtr<T> begin();
	BlobPtr<T> end();

private:
	shared_ptr<vector<T>> data;
	void check(size_type i, const T &msg) const;
};

template<typename T>
Blob<T>::Blob() :data(make_shared<vector<T>>()) {}
template<typename T>
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {}

template<typename T>
template<typename V>
Blob<T>::Blob(const V & be, const V & en) : data(make_shared(vector<T>(be, en))){}

template<typename T>
void	 Blob<T>::check(size_type i, const T &msg) const
{
	if (i > data->size())
		throw out_of_range(msg);
}
template<typename T>
T & Blob<T>::front()
{
	check(0, "front on empty Blob");
	return data->front();
}
template<typename T>
T & Blob<T>::front() const
{
	check(0, "front on empty Blob");
	return data->front();
}
template<typename T>
T & Blob<T>::back()
{
	check(0, " back on empty Blob");
	return data->back();
}
template<typename T>
T & Blob<T>::back() const
{
	check(0, " back on empty Blob");
	return data->back();
}
template<typename T>
void     Blob<T>::pop_back()
{
	check(0, " pop_back empty Blob");
	data->pop_back();
}

template<typename T>
class BlobPtr
{
public:
	BlobPtr() :curr(0) {}
	BlobPtr(Blob &a, int sz = 0) :wptr(a.data), curr(sz) {}
	T & deref() const;
	BlobPtr & incr();
private:
	shared_ptr<vector<T>>check(int, const T&) const;
	weak_ptr<vector<T>> wptr;
	int curr;
};
template<typename T>
shared_ptr<vector<T>> BlobPtr<T>::check(int i, const T&msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbound BlobPtr");
	if (i >= ret->size())
		throw out_of_range(msg);
	return ret;
}
template<typename T>
T & BlobPtr<T>::deref() const
{
	auto p = check(curr, "derefereance past end");
	return (*p)[curr];
}
template<typename T>
BlobPtr<T> & BlobPtr<T>::incr()
{
	check(curr, "increment past end of Blobptr");
	++curr;
	return *this;
}
template<typename T>
BlobPtr<T> Blob<T>::begin() { return BlobPtr<T>(*this); }
template<typename T>
BlobPtr<T> Blob<T>::end() {
	auto ret = BlobPtr<T>(*this, data->size());
	return ret;
}

void main()
{
	const Blob<string> s{ "yes" };
	cout << s.front() << endl;


	system("PAUSE");
	return;
}
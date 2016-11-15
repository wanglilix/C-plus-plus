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

class HasPtr
{
public:
	HasPtr(const string &s = string()) :ps(make_shared<string>(s)), i(s.size()) {};
	HasPtr(const HasPtr &a) :ps(make_shared<string>(*a.ps)), i(a.i) {};
	HasPtr &operator=(HasPtr &a) { ps = make_shared<string>(*a.ps); i = a.i; return *this; };
	HasPtr &operator=(const string &s) { ps = make_shared<string>(s); i = s.size(); return *this; };
	HasPtr &operator=(const char* s) { ps = make_shared<string>(s); i = strlen(s); return *this; };
	bool operator<(const HasPtr&rhs) const { return *ps < *(rhs.ps); };
	string & HasPtr::operator*() { return *ps; };
	friend void swap(HasPtr &, HasPtr&);
private:
	shared_ptr<string> ps;
	int i;
};
void swap(HasPtr &a, HasPtr&b)
{
	using std::swap;
	swap(a.ps, b.ps);
	swap(a.i, b.i);
	cout << a.i << "  " << b.i << endl;
}

void main()
{
	vector<HasPtr> vec;
	for (int i = 0; i < 9; i++)
	{
		vec.push_back(to_string(9 - i));
	}
	for (auto p : vec)
	{
		cout << *p << endl;
	}
	sort(vec.begin(), vec.end());
	for (auto p : vec)
	{
		cout << *p << endl;
	}
	
	HasPtr a("safdf");
	HasPtr b("e");
	HasPtr c(b);
	swap(a, c);
	system("PAUSE");
	return;
}
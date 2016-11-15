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

class DebugDelete
{
public:
	DebugDelete(ostream &s = cerr) : os(s){}

	template<typename T>void operator()(T*p)const
	{
		os << "deleting unique_ptr" << endl;
		delete p;
	}
private:
	ostream &os;
};

void main()
{
	DebugDelete dele;
	double *p = new double;

	dele(p);

	system("PAUSE");
	return;
}
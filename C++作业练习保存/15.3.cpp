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
using namespace std;
using namespace std::placeholders;

class Quote
{
public:
	Quote() = default;
	Quote(const string &book, double sale_price) :bookNo(book), price(sale_price){};
public:
	string isbn() const{ return bookNo; };
	virtual double net_price(int n) const{ return n*price; };

	virtual ~Quote() = default;
private:
	string bookNo;
protected:
	double price = 0;

};

double print_total(ostream& os, const Quote& item, int n)
{
	double ret = item.net_price(n);
	os << "ISBN" << item.isbn() << "# sold: " << n << " total due: " << ret << endl;
	return ret;
}
void main()
{


	system("PAUSE");
	return;
}
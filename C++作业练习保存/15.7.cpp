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

class Bulk_quote :public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const string& book, double p, int qty, double disc) : Quote(book, p), min_qty(qty), discount(disc){  };

	double net_price(int) const override;
protected:
	int		 min_qty = 0;
	double	 discount = 0.0;

};

double Bulk_quote::net_price(int i) const
{
	if (i >= min_qty)
	{
		return i*(1 - discount)*price;
	}
	else
	{
		return price*i;

	}
}

class Count_quote :public Quote
{
public:
	Count_quote() = default;
	Count_quote(const string& book, double p, int qty, double disc) : Quote(book, p), min_qty(qty), discount(disc){  };

	double net_price(int) const override;
protected:
	int		 min_qty = 0;
	double	 discount = 0.0;

};
double Count_quote::net_price(int n) const
{
	if (n <= min_qty)
	{
		return n*(1 - discount)*price;
	}
	else
	{
		return min_qty*(1 - discount)*price + price*(n - min_qty);

	}
}


double print_total(ostream& os, const Quote& item, int n)
{
	double ret = item.net_price(n);
	os << "ISBN " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}
void main()
{
	Quote a("santi", 20);
	Bulk_quote b("santi", 20, 10, 0.2);
	Count_quote c("santi", 20, 10, 0.2);
	print_total(cout, a, 9);
	print_total(cout, b, 9);
	print_total(cout, b, 13);
	print_total(cout, c, 13);

	system("PAUSE");
	return;
}
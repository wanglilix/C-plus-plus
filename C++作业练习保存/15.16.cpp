// test.cpp : �������̨Ӧ�ó������ڵ㡣
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
	virtual void mdebug(){ cout << bookNo << endl << price << endl; };

	virtual ~Quote() = default;
private:
	string bookNo;
protected:
	double price = 0;

};

class Disc_quote :public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const std::string & book, double price, int qty, double disc) :Quote(book, price), quantity(qty), discount(disc){}
	double net_price(int) const = 0;

protected:
	int quantity = 0;
	double discount = 0.0;
};

class Bulk_quote :public Disc_quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const string& book, double p, int qty, double disc) : Disc_quote(book, p, qty, disc){  };

	double net_price(int) const override;
	virtual void mdebug()
	{
		Quote::mdebug();
		cout << quantity << endl << discount << endl;
	};

};

double Bulk_quote::net_price(int i) const
{
	if (i >= quantity)
	{
		return i*(1 - discount)*price;
	}
	else
	{
		return price*i;

	}
}

class Count_quote :public Disc_quote
{
public:
	Count_quote() = default;
	Count_quote(const string& book, double p, int qty, double disc) : Disc_quote(book, p, qty, disc){  };

	double net_price(int) const override;

};

double Count_quote::net_price(int n) const
{
	if (n <= quantity)
	{
		return n*(1 - discount)*price;
	}
	else
	{
		return quantity*(1 - discount)*price + price*(n - quantity);

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


	system("PAUSE");
	return;
}
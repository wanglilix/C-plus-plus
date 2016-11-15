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
	//Quote(const Quote& a){  };//合成拷贝构造函数
public:
	string isbn() const{ return bookNo; };
	virtual double net_price(int n) const{ return n*price; };
	virtual void mdebug(){ cout << bookNo << endl << price << endl; };

	virtual ~Quote(){ cout << "Quote desstructor is runing!" << endl; };
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
	Disc_quote(const Disc_quote& a) : Quote(a){ quantity = a.quantity; discount = a.discount; cout << "Quote copy construct is runing!" << endl; };
	double net_price(int) const = 0;

protected:
	int quantity = 0;
	double discount = 0.0;
	virtual ~Disc_quote(){ cout << "Disc_quote desstructor is runing!" << endl; };
};

class Bulk_quote :public Disc_quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const string& book, double p, int qty, double disc) : Disc_quote(book, p, qty, disc){  };
	Bulk_quote(const Bulk_quote& a) :Disc_quote(a){ cout << "Bulk_quote copy construct is runing!" << endl; };
	double net_price(int) const override;
	virtual void mdebug()
	{
		Quote::mdebug();
		cout << quantity << endl << discount << endl;
	};
	virtual ~Bulk_quote(){ cout << "Bulk_quote desstructor is runing!" << endl; };
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
	Count_quote(const Count_quote& a) :Disc_quote(a){ cout << "Count_quote copy construct is runing!" << endl; };
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
	Bulk_quote a;
	if (1 == 1)
	{
		Bulk_quote b = a;
	}

	system("PAUSE");
	return;
}
// test.cpp : �������̨Ӧ�ó������ڵ㡣

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
#include <tuple>
#include <random>

using namespace std;
using namespace std::placeholders;

class sale{
public:												//Ĭ��˽��
	sale() = default;
	sale(int i) :a(i){};
	sale(int i, string j) :a(i), b(j){};

private:
	int a = 0;
	string b = "0";

public:
	friend sale operator+(const sale&, const sale&);	//�Գ������������Ƿǳ�Ա����
	friend istream& operator>> (istream &, sale&);		//�����������������Ƿǳ�Ա����
	friend ostream& operator<< (ostream&, sale&);

public:
	sale& operator= (const sale& i){ a = i.a; return *this; };
	sale& operator += (const sale& i){ a += i.a; return *this; };//return this;
	int geta(){ return a; };

	explicit operator int() const { return a; };
	explicit operator string() const { return b; };

};

sale operator+(const sale& i, const sale& j)
{
	sale tmp(i);
	tmp += j;		//+=���βα�����const
	return tmp;
}

istream& operator>>(istream& in, sale& i)
{
	int tmp;
	in >> tmp;
	if (in)//������󣬻ָ�a��Ĭ��ֵ
	{
		i.a = tmp;
	}
	else
		i = sale();
	return in;
}

ostream& operator<<(ostream& out, sale& i)
{
	out << i.a << endl;
	return out;
}

//int operator=(const sale&)  // = �����ǳ�Ա����
//{
//
//}

void main()
{

	sale ai(0, "ddds");

	ai = 3;//
	cout << ai << endl;
	int i = (int)ai;
	cout << i << endl;
	string j = (string)ai;
	cout << j << endl;


	system("PAUSE");
	return;
}
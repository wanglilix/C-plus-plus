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
	int geta() const{ return a; };
	string getb() const{ return b; };			//��const ����  ��������const�Ķ���
	explicit operator int() const { return a; };
	explicit operator string() const { return b; };
};

namespace std{

	template<>
	struct hash<sale>
	{
		typedef size_t result_type;
		typedef sale srgument_type;
		size_t operator()(const sale& s) const;
	};
	size_t hash<sale>::operator()(const sale &s) const
	{
		return	 hash<int>()(s.geta()) ^
			hash<string>()(s.getb());
	}
}

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
void main()
{
	unordered_multiset<sale> saset;


	system("PAUSE");
	return;
}
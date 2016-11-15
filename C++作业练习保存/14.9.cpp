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
#include <tuple>
#include <random>

using namespace std;
using namespace std::placeholders;

class sale{
public://默认私有
	sale() = default;
	sale(int i) :a(i){};

private:
	int a = 0;

public:
	friend sale operator+(const sale&, const sale&);	//对称性运算符最好是非成员函数
	friend istream& operator>> (istream &, sale&);		//输入输出运算符必须是非成员函数
	friend ostream& operator<< (ostream&, sale&);

public:
	sale& operator += (sale& i){ a += i.a; return *this; };//return this;
	int geta(){ return a; };

};

sale operator+(const sale& i, const sale& j)
{
	return sale{ i.a + j.a };
}

istream& operator>>(istream& in, sale& i)
{
	int tmp;
	in >> tmp;
	if (in)//输入错误，恢复a的默认值
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

//int operator=(const sale&)  // = 必须是成员函数
//{
//
//}

void main()
{

	sale ai(0), bi(2);

	ai += bi;
	cout << ai;

	cin >> ai;
	cout << ai;


	system("PAUSE");
	return;
}
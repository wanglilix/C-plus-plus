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


class date
{
public:
	date() = default;//Ĭ��
	date(string str);
public:
	unsigned Y = 0;
	string M = " ";
	unsigned D = 0;

};//��Ķ���

date::date(string str)
{
	unsigned beg = 0, end = 0;
	string tmp;
	//M
	if (beg = str.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZqwertyuiopasdfghjklzxcvbnm"), beg != string::npos)//�ҵ���ĸ
	{
		end = str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZqwertyuiopasdfghjklzxcvbnm");
		tmp.assign(str, beg, end - beg);
		M = tmp;
	}
	else if (beg = str.find_first_of("0123456789"), beg != string::npos)
	{
		end = str.find_first_not_of("0123456789");
		tmp.assign(str, beg, end - beg);
		M = tmp;
	}
	else
	{
		cout << "error" << endl;
	}
	beg = end;
	//D
	if (beg = str.find_first_of("0123456789", beg), beg != string::npos)//�ҵ���ĸ
	{
		end = str.find_first_not_of("0123456789", beg);
		tmp.assign(str, beg, end - beg);
		D = stoi(tmp);
	}
	else
	{
		cout << "error" << endl;
	}
	//Y
	beg = end;
	if (beg = str.find_first_of("0123456789", beg), beg != string::npos)//�ҵ���ĸ
	{
		end = str.find_first_not_of("0123456789", beg);
		tmp.assign(str, beg, end - beg);
		Y = stoi(tmp);
	}
	else
	{
		cout << "error" << endl;
	}

}//���캯��

void main()
{
	date d("january 1 1090");
	cout << d.M << " ";
	cout << d.D << " ";
	cout << d.Y << endl;
	system("PAUSE");
	return;
}
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

void main()
{
	vector<int> vec;
	int in;
	cout << "���������֣�" << endl;
	while (cin >> in)
	{
		vec.push_back(in);
	}

	cout << "�����ѯ������:" << endl;

	cin.clear();
	cin >> in;

	in = count(vec.begin(), vec.end(), in);
	cout << "��ѯֵ�����ˣ�" << in << "��" << endl;

	system("PAUSE");
	return;
}
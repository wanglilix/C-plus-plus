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


void find_longest_word(ifstream & fil);
int main()
{
	string str;
	ifstream fil("fata.txt");

	if (!fil)
	{
		cout << "�޷����ļ���" << endl;
		return 0;
	}
	find_longest_word(fil);

	system("PAUSE");
	return 0;
}
void find_longest_word(ifstream & fil)
{
	string s, longword = "û���ҵ����ʵ��ʣ�";
	int max_length = 0;

	while (fil >> s)
	{
		if (string::npos == s.find_first_of("bdfghjklpqty"))
		{
			if (max_length < s.size())
			{
				max_length = s.size();
				longword = s;
			}
		}
	}
	cout << longword << endl;
}

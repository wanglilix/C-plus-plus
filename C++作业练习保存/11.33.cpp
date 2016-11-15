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

using namespace std;
using namespace std::placeholders;

map<string, string> buildmap(ifstream &fil)		//�����ܸ��ƿ���
{
	map<string, string> transmap;
	string line, wordA, wordB;				//1��,����
	while (getline(fil, line))
	{
		istringstream istrline(line);//string��
		istrline >> wordA;					//��һ������
		if (istrline >> wordB)				//��Ӧ����
		{
			transmap[wordA] = wordB;
		}
		else
		{
			cout << "no rule for " << wordA << endl;
		}
	}
	return transmap;

}

string trans(map<string, string> transmap, string word)
{
	if (transmap.find(word) == transmap.end())
		return word;
	else {
		return transmap.find(word)->second;
	}
}



void main()
{
	ifstream fil("trans.txt");
	auto transmap = buildmap(fil);
	fil.close();
	fil.open("A.txt");
	ofstream outfil("B.txt");
	string str, word;
	while (getline(fil, str))
	{
		string newstr;
		istringstream istr(str);
		while (istr >> word)
		{
			word = trans(transmap, word);
			newstr = newstr + word + " ";
		}
		cout << newstr << endl;
		outfil << newstr << "\n";
	}




	system("PAUSE");
	return;
}
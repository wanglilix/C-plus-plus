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

using namespace std;
using namespace std::placeholders;

map<string, string> buildmap(ifstream &fil)		//流不能复制拷贝
{
	map<string, string> transmap;
	string line, wordA, wordB;				//1行,单词
	while (getline(fil, line))
	{
		istringstream istrline(line);//string流
		istrline >> wordA;					//第一个单词
		if (istrline >> wordB)				//对应单词
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
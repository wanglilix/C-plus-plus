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

using namespace std;
using namespace std::placeholders;

class QueryResult;
class TextQuery
{
public:
	shared_ptr<vector<string>> strptr;
	map<string, shared_ptr<set<int>>> linemap;

public:
	TextQuery() :strptr(nullptr), linemap(map<string, shared_ptr<set<int>>>()) {};
	TextQuery(ifstream &);
	QueryResult query(const string&);
};

TextQuery::TextQuery(ifstream &infil)
{
	string line, word;
	int n = 0;
	vector<string> vec;
	while (getline(infil, line))
	{
		vec.push_back(line);
		istringstream linestr(line);
		while (linestr >> word)
		{
			if (linemap.find(word) == linemap.end())
			{
				linemap[word] = make_shared<set<int>>();//�����ȷ����ڴ��ٲ������
				linemap[word]->insert(n);
			}
			else
			{
				linemap[word]->insert(n);
			}
		}
		++n;//��0��ʼ��
	}
	strptr = make_shared<vector<string>>(std::move(vec));//�����ȷ����ڴ��ٲ������

}


class QueryResult
{
public:
	QueryResult() : word(""), setptr(nullptr), strptr(nullptr) {};
public:
	string word;
	shared_ptr<set<int>> setptr;
	shared_ptr<vector<string>> strptr;
};


QueryResult TextQuery::query(const string& str)
{
	QueryResult result;
	result.word = str;
	if (linemap.find(str) != linemap.end())
	{
		result.strptr = strptr;
		result.setptr = linemap.find(str)->second;
	}
	return result;
}

void print(QueryResult & result)
{
	if (result.strptr != nullptr)
	{
		cout << result.word << " show :" << endl;
		for (auto i : *result.setptr)
		{
			cout << "(line " << i + 1 << " )  ";
			cout << (*result.strptr)[i] << endl;
		}
	}
	else
	{
		cout << "No find result!" << endl;
	}
}
void main()
{
	ifstream infil("data.txt");
	TextQuery data(infil);
	auto result = data.query("go.");
	print(result);

	system("PAUSE");
	return;
}
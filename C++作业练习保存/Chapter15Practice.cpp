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

//����һ���ַ�����ĳ����ĸ���ֵĵ��ʼ���λ�û���û��ĳ����ĸ���ַ�����λ��

class QueryResult;
class Query_base
{
public:
	Query_base(const string & a) :word(a){}
	//friend Query operator~(const Query&);
	friend class Query;
	virtual QueryResult eval(const string &) = 0;
	virtual string      rep() = 0;
	virtual ~Query_base() = default;
protected:
	string word;
};

class QueryResult{
	friend void print(const QueryResult &);
public:
	QueryResult(const map<int, string> & a, const string & b) :wordmap(a), str(b){};//���캯��
private:
	map<int, string> wordmap;	//��ѯ�Ľ��
	string str;					//��ѯ����ĸ
};

void print(const QueryResult & result)
{
	cout << result.str << " show at:" << endl;
	for (auto i : result.wordmap)
	{
		cout << "The " << i.first << " word  " << i.second << endl;
	}
}

//�ӿ���
class Query
{
	friend Query operator~(const Query&);
public:
	Query(const string&);
	QueryResult eval(const string & t)const { return q->eval(t); }
	string rep() const { return q->rep(); }
private:
	shared_ptr<Query_base> q;
	Query(shared_ptr<Query_base> query) : q(query){}     //Query_baseת����ָ���ͣ����ݣ��ĺ���
};

//������WordQuery
class WordQuery :public Query_base
{
public:
	WordQuery(const string & a) :Query_base(a){}
	virtual QueryResult eval(const string &);
	virtual string      rep();
	//virtual ~WordQuery();
};

QueryResult WordQuery::eval(const string&str)
{
	map<int, string> a;
	a[1] = "start";
	string word("s");
	return QueryResult(a, word);
}

string WordQuery::rep()
{
	return word;
}

Query::Query(const string & str)
{
	q = shared_ptr<Query_base>(new WordQuery(str));
}


//������NotQuery
class NotQuery :public Query_base
{
	friend Query operator~(const Query&);
public:
	NotQuery(const string& a) : Query_base(a){}
	virtual QueryResult eval(const string &);
	virtual string      rep();
	//virtual ~NotQuery();
};

Query operator~(const Query& query)
{
	return Query(shared_ptr<Query_base>(new NotQuery(query.q->rep())));
}

QueryResult NotQuery::eval(const string& str)
{
	map<int, string> a;
	a[1] = "shut";
	string word("t");
	return QueryResult(a, word);
}

string NotQuery::rep()
{
	return word;
}

void main()
{
	//����һ���ַ�����ĳ����ĸ���ֵĵ��ʼ���λ�û���û��ĳ����ĸ���ַ�����λ��
	//
	string str("ssds");
	Query a("s");
	print(a.eval(str));
	print((~a).eval(str));

	system("PAUSE");
	return;
}
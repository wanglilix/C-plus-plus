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

using namespace std;
using namespace std::placeholders;

//查找一个字符串中某个字母出现的单词及其位置或者没有某个字母的字符及其位置

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
	QueryResult(const map<int, string> & a, const string & b) :wordmap(a), str(b){};//构造函数
private:
	map<int, string> wordmap;	//查询的结果
	string str;					//查询的字母
};

void print(const QueryResult & result)
{
	cout << result.str << " show at:" << endl;
	for (auto i : result.wordmap)
	{
		cout << "The " << i.first << " word  " << i.second << endl;
	}
}

//接口类
class Query
{
	friend Query operator~(const Query&);
public:
	Query(const string&);
	QueryResult eval(const string & t)const { return q->eval(t); }
	string rep() const { return q->rep(); }
private:
	shared_ptr<Query_base> q;
	Query(shared_ptr<Query_base> query) : q(query){}     //Query_base转变所指类型（内容）的函数
};

//派生类WordQuery
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


//派生类NotQuery
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
	//查找一个字符串中某个字母出现的单词及其位置或者没有某个字母的字符及其位置
	//
	string str("ssds");
	Query a("s");
	print(a.eval(str));
	print((~a).eval(str));

	system("PAUSE");
	return;
}
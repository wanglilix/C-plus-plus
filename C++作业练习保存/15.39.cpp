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

class QueryResult;
class TextQuery
{
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream&);
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<line_no>>> wm;

};

TextQuery::TextQuery(ifstream &is) :file(new vector<string>)
{
	string text;
	while (getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word)
		{
			auto &lines = wm[word];
			if (!lines)
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}

class QueryResult
{
	using line_no = vector<string>::size_type;
	friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) :sought(s), lines(p), file(f){}
private:
	string sought;
	shared_ptr<set<line_no>> lines;
	shared_ptr<vector<string>> file;
public:
	set<line_no>::iterator begin(){ return lines->cbegin(); }
	set<line_no>::iterator end(){ return lines->cend(); }
	shared_ptr<vector<string>> get_file(){ return file; }

};

QueryResult TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}

ostream& print(ostream &os, const QueryResult &qr)
{
	os << qr.sought << "  occurs " << qr.lines->size() << " " << "time " << endl;
	for (auto num : *qr.lines)
	{
		os << "\t(line" << num + 1 << ")" << *(qr.file->begin() + num) << endl;

	}

	return os;
}

class Query_base
{
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual string rep() const = 0;

};

class Query{
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const string&);												   //构造函数1
	QueryResult eval(const TextQuery &t) const { return q->eval(t); }	   //接口函数
	string rep() const { return q->rep(); }                                //接口函数
private:
	Query(shared_ptr<Query_base> query) :q(query) { } //构造函数2
	shared_ptr<Query_base> q;                         //成员：指针
};

class WordQuery :public Query_base
{
	friend class Query;
	WordQuery(const string & s) :query_word(s){ cout << "WordQuery constructor is runing" << endl; }	 //构造函数
	QueryResult eval(const TextQuery &t) const{ return t.query(query_word); } //查询函数
	string rep() const { return query_word; }								  //返回查询字符
	string query_word;
};

inline Query::Query(const string &s) :q(new WordQuery(s)){ cout << "Query     constructor is runing" << endl; }

class NotQuery :public Query_base{
	friend Query operator~(const Query&);
	NotQuery(const Query &q) :query(q){}					
	string rep() const { return "~(" + query.rep() + ")"; } //返回查询字符
	QueryResult eval(const TextQuery&) const;			    //查询函数
	Query query;
};

inline Query operator~(const Query &operand)
{
	return shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
	auto result = query.eval(text);
	auto ret_lines = make_shared<set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();
	for (size_t n = 0; n != sz; ++n)
	{
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg!=end)
		{
			++beg;
		}
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}


class BinaryQuery:public Query_base
{
protected:
	BinaryQuery(const Query &l,const Query &r, std::string s): lhs(l),rhs(r),opSym(s) {  }
	string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;
	string opSym;
};

class AndQuery :public BinaryQuery
{
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query& left,const Query& right):BinaryQuery(left,right, string("&")){}
	QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
	return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}
QueryResult AndQuery::eval(const TextQuery& text) const
{
	auto left = lhs.eval(text), right = rhs.eval(text);
	auto ret_lines = make_shared<set<line_no>>();
	set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), ret_lines, left.get_file());
}

class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query& left, const Query&right) :BinaryQuery(left, right, "|"){}
	QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery & text) const{
	auto right = rhs.eval(text), left = lhs.eval(text);
	auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
	ret_lines->insert(right.begin(), right.end());
	return QueryResult(rep(), ret_lines, left.get_file());

}

void main()
{
	ifstream infil("data.txt");
	TextQuery data(infil);
	auto result = Query("fiery")&Query("bird")| Query("wind");
	print(cout, result.eval(data));
	system("PAUSE");
	return;
}